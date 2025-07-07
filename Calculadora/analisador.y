%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Protótipos das funções do analisador léxico e de erro.
void yyerror(char *s);
int yylex(void);
extern FILE *yyin; // Ponteiro para o arquivo de entrada, gerenciado pelo Flex/Lex.

// Enum para os tipos de dados suportados pela linguagem.
typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_STRING,
    TIPO_VETOR,     // Um tipo especial para identificar vetores na tabela de símbolos.
    TIPO_NULO       // Representa um valor nulo ou não inicializado.
} Tipo;

// Union para armazenar diferentes tipos de valores em uma única variável.
typedef union {
    int i;
    float f;
    char *s;
    struct Valor *v; // Ponteiro para um array de 'Valor' (usado para vetores).
} ValorUnion;

// Estrutura principal para representar um valor na linguagem (seja int, float, etc.).
typedef struct Valor {
    Tipo tipo;              // O tipo do valor atualmente armazenado.
    ValorUnion val;         // O valor em si, usando a union.
    int tamanho_vetor;      // Se for um vetor, armazena seu tamanho.
} Valor;

// Estrutura para a Tabela de Símbolos (armazena variáveis e vetores).
typedef struct Simbolo {
    char *nome;             // Nome da variável/vetor.
    Tipo tipo_declarado;    // Tipo com o qual foi declarado (TIPO_INT, TIPO_VETOR, etc.).
    Valor valor;            // O valor atual do símbolo.
    struct Simbolo *prox;   // Ponteiro para o próximo símbolo na lista ligada.
} Simbolo;

// Estrutura para um nó da Árvore Sintática Abstrata (AST - Abstract Syntax Tree).
typedef struct AstNode {
    int nodetype;           // Tipo do nó (ex: '+', 'I' para IF, 'K' para constante).
    struct AstNode *l;      // Ponteiro para o filho esquerdo (ou único filho).
    struct AstNode *r;      // Ponteiro para o filho direito.
} AstNode;

// Variável Global: a cabeça da lista ligada que implementa a Tabela de Símbolos.
Simbolo *tabela_simbolos = NULL;

// Protótipos das Funções Auxiliares (implementadas na seção C mais abaixo).
Simbolo* busca_simbolo(char *nome);
Simbolo* insere_simbolo(char *nome, Tipo tipo_dec);
AstNode* novo_no_ast(int nodetype, AstNode *l, AstNode *r);
AstNode* novo_no_num_int(int ival);
AstNode* novo_no_num_float(float fval);
AstNode* novo_no_texto(char *sval);
AstNode* novo_no_id(char *id);
AstNode* novo_no_vetor_acesso(char *id, AstNode *indice);
AstNode* novo_no_atribuicao(char *id, AstNode *valor);
AstNode* novo_no_atribuicao_vetor(char *id, AstNode *indice, AstNode* valor);
AstNode* novo_no_controle(int nodetype, AstNode *cond, AstNode *corpo_verdade, AstNode *corpo_falso);
AstNode* novo_no_comparacao(int cmptype, AstNode *l, AstNode *r);
Valor eval(AstNode *a); // Função principal que interpreta a AST.
char* valor_para_string(Valor v);

%}

/* --- Definições do Bison/Yacc --- */

// A %union define os possíveis tipos de dados que podem ser associados a símbolos
// terminais (tokens) e não-terminais da gramática.
%union {
    int ival;           // Para números inteiros.
    float fval;         // Para números de ponto flutuante.
    char *str;          // Para strings (identificadores e literais de texto).
    int fn;             // Para o tipo de comparação (ex: '>', '<=').
    struct AstNode *a;  // Para ponteiros para nós da AST.
}

// Declaração dos tokens (símbolos terminais).
%token T_INTEIRO T_REAL T_TEXTO
%token <ival> NUM_INT
%token <fval> NUM_FLOAT
%token <str> ID TEXTO
%token INICIO SE SENAO ENQUANTO ESCREVA LEIA VAR FIM
%token <fn> CMP

// Declaração dos tipos dos símbolos não-terminais.
// Associa o não-terminal ao campo 'a' (AstNode*) da %union.
%type <a> exp lista_comandos comando
// Associa o não-terminal ao campo 'ival' (int) da %union.
%type <ival> tipo_var

// Definição de precedência e associatividade dos operadores.
%right '='
%left CMP
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS      // Menos unário.
%nonassoc SENAO_PREC  // Precedência para resolver o conflito 'dangling else'.

%%

programa:
      INICIO lista_comandos FIM   { if($2) eval($2); /* Ao final, avalia a AST construída */ }
    | INICIO FIM                  { /* Programa vazio é válido */ }
    ;

lista_comandos:
      /* Uma lista de comandos pode começar vazia. Retorna um ponteiro nulo. */
      { $$ = NULL; }
    | lista_comandos comando
      {
          // Constrói uma lista de nós da AST.
          if ($1 == NULL) {
              $$ = $2; // Se a lista estava vazia, o primeiro comando é o início da lista.
          } else if ($2 == NULL) {
              $$ = $1; // Se o comando for uma declaração (que retorna NULL), mantém a lista existente.
          } else {
              // Cria um nó 'L' (Lista) para encadear os comandos.
              $$ = novo_no_ast('L', $1, $2);
          }
      }
    ;

comando:
      // Declaração de variável simples.
      VAR tipo_var ID ';'
        { 
            insere_simbolo($3, (Tipo)$2); // Insere na tabela de símbolos.
            $$ = NULL; // Declarações não geram nós executáveis na AST, então retorna NULL.
        }
    // Declaração de vetor.
    | VAR tipo_var ID '[' exp ']' ';'
        {
            // Insere o símbolo como um TIPO_VETOR.
            Simbolo *s = insere_simbolo($3, TIPO_VETOR);
            if (s) { // Se a inserção foi bem-sucedida (sem redeclaração).
                s->valor.tipo = (Tipo)$2; // Armazena o tipo dos *elementos* do vetor.
                Valor v_indice = eval($5); // Avalia a expressão do tamanho na hora.
                if (v_indice.tipo == TIPO_INT) {
                    s->valor.tamanho_vetor = v_indice.val.i;
                    // Aloca memória para o vetor.
                    s->valor.val.v = (Valor*)calloc(v_indice.val.i, sizeof(Valor));
                } else {
                    yyerror("Tamanho do vetor deve ser um inteiro.");
                }
            }
            $$ = NULL; // Também não gera nó executável.
        }
    // Atribuição a uma variável.
    | ID '=' exp ';'
        { $$ = novo_no_atribuicao($1, $3); /* Cria um nó de atribuição. */ }
    // Atribuição a um elemento de vetor.
    | ID '[' exp ']' '=' exp ';'
        { $$ = novo_no_atribuicao_vetor($1, $3, $6); /* Cria um nó de atribuição a vetor. */ }
    // Estrutura 'SE' (IF).
    | SE '(' exp ')' '{' lista_comandos '}'
        { $$ = novo_no_controle('I', $3, $6, NULL); /* Nó de controle 'I' (IF) sem ELSE. */ }
    // Estrutura 'SE-SENAO' (IF-ELSE).
    | SE '(' exp ')' '{' lista_comandos '}' SENAO '{' lista_comandos '}'
        { $$ = novo_no_controle('I', $3, $6, $10); /* Nó de controle 'I' (IF) com ELSE. */ }
    // Estrutura 'ENQUANTO' (WHILE).
    | ENQUANTO '(' exp ')' '{' lista_comandos '}'
        { $$ = novo_no_controle('W', $3, $6, NULL); /* Nó de controle 'W' (WHILE). */ }
    // Comando 'ESCREVA' (Print).
    | ESCREVA '(' exp ')' ';'
        { $$ = novo_no_ast('P', $3, NULL); /* Nó 'P' (Print). */ }
    // Comando 'LEIA' (Read).
    | LEIA '(' ID ')' ';'
        { $$ = novo_no_ast('R', novo_no_id($3), NULL); /* Nó 'R' (Read). */ }
    ;

tipo_var:
      T_INTEIRO { $$ = TIPO_INT; }
    | T_REAL    { $$ = TIPO_FLOAT; }
    | T_TEXTO   { $$ = TIPO_STRING; }
    ;

// Regras para expressões, que formam a base da AST.
exp:
      NUM_INT                 { $$ = (AstNode*)novo_no_num_int($1);    } // Nó de constante inteira.
    | NUM_FLOAT               { $$ = (AstNode*)novo_no_num_float($1);  } // Nó de constante float.
    | TEXTO                   { $$ = (AstNode*)novo_no_texto($1);      } // Nó de constante texto.
    | ID                      { $$ = (AstNode*)novo_no_id($1);         } // Nó de referência a um ID.
    | ID '[' exp ']'          { $$ = novo_no_vetor_acesso($1, $3);     } // Nó de acesso a um vetor.
    | exp '+' exp             { $$ = novo_no_ast('+', $1, $3);         } // Nó de operação binária.
    | exp '-' exp             { $$ = novo_no_ast('-', $1, $3);         }
    | exp '*' exp             { $$ = novo_no_ast('*', $1, $3);         }
    | exp '/' exp             { $$ = novo_no_ast('/', $1, $3);         }
    | exp CMP exp             { $$ = novo_no_comparacao($2, $1, $3);   } // Nó de comparação.
    | '-' exp %prec UMINUS    { $$ = novo_no_ast('M', $2, NULL);        } // Nó de menos unário.
    | '(' exp ')'             { $$ = $2; /* Parênteses apenas agrupam, não criam nós. */ }
    ;

%%

// Procura um símbolo (variável) na tabela de símbolos.
Simbolo* busca_simbolo(char *nome) {
    Simbolo *s;
    // Percorre a lista ligada.
    for (s = tabela_simbolos; s != NULL; s = s->prox) {
        if (strcmp(s->nome, nome) == 0) {
            return s; // Retorna o ponteiro para o símbolo se encontrado.
        }
    }
    return NULL; // Retorna NULL se não encontrar.
}

// Insere um novo símbolo na tabela de símbolos.
Simbolo* insere_simbolo(char *nome, Tipo tipo_dec) {
    if (busca_simbolo(nome) != NULL) {
        yyerror("Variavel ja declarada.");
        return NULL;
    }
    Simbolo *s = (Simbolo*) malloc(sizeof(Simbolo));
    s->nome = strdup(nome); // Duplica a string do nome para evitar problemas de ponteiro.
    s->tipo_declarado = tipo_dec;
    s->valor.tipo = TIPO_NULO; // Variáveis começam com valor nulo.
    s->prox = tabela_simbolos; // Insere no início da lista.
    tabela_simbolos = s;
    return s;
}

// Função genérica para criar um novo nó da AST.
AstNode* novo_no_ast(int nodetype, AstNode *l, AstNode *r) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

// Funções "fábrica" para criar nós de constantes, encapsulando o valor.
AstNode* novo_no_num_int(int ival) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_INT;
    v->val.i = ival;
    return novo_no_ast('K', (AstNode*)v, NULL); // 'K' para constante.
}

AstNode* novo_no_num_float(float fval) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_FLOAT;
    v->val.f = fval;
    return novo_no_ast('K', (AstNode*)v, NULL);
}

AstNode* novo_no_texto(char *sval) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_STRING;
    v->val.s = strdup(sval);
    return novo_no_ast('K', (AstNode*)v, NULL);
}

// Cria um nó que referencia um Identificador (variável/vetor).
AstNode* novo_no_id(char *id) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        char err[100];
        sprintf(err, "Variavel '%s' nao declarada", id);
        yyerror(err);
        exit(1);
    }
    // O nó 'N' (Nome) armazena um ponteiro direto para a entrada na tabela de símbolos.
    return novo_no_ast('N', (AstNode*)s, NULL);
}

// Cria um nó para acesso a um elemento de vetor.
AstNode* novo_no_vetor_acesso(char *id, AstNode *indice) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Vetor nao declarado");
        exit(1);
    }
    // Nó 'A' (Acesso) guarda o símbolo e a AST do índice.
    return novo_no_ast('A', (AstNode*)s, indice);
}

// Cria um nó para atribuição a uma variável.
AstNode* novo_no_atribuicao(char *id, AstNode *valor) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Variavel nao declarada");
        exit(1);
    }
    // Nó '=' guarda o símbolo e a AST do valor a ser atribuído.
    return novo_no_ast('=', (AstNode*)s, valor);
}

// Cria um nó para atribuição a um elemento de vetor.
AstNode* novo_no_atribuicao_vetor(char *id, AstNode *indice, AstNode* valor) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Vetor nao declarado");
        exit(1);
    }
    // Nó 'a' (atribuição a arranjo) é mais complexo.
    // Reutilizamos o nó de atribuição e adicionamos a AST do índice.
    AstNode *temp = novo_no_ast('=', (AstNode*)s, valor);
    return novo_no_ast('a', temp, indice);
}

// Cria um nó para estruturas de controle (IF, WHILE).
AstNode* novo_no_controle(int nodetype, AstNode *cond, AstNode *corpo_v, AstNode *corpo_f) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = nodetype;
    a->l = cond; // Filho esquerdo é a condição.
    a->r = novo_no_ast(0, corpo_v, corpo_f); // Filho direito é um nó auxiliar que guarda os corpos.
    return a;
}

// Cria um nó de comparação.
AstNode* novo_no_comparacao(int cmptype, AstNode *l, AstNode *r) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = 'C'; // 'C' para comparação.
    a->l = novo_no_ast(cmptype, l, r); // Filho esquerdo é um nó auxiliar que guarda o tipo de comparação e os operandos.
    return a;
}

// Verifica se um valor é considerado "verdadeiro" na lógica da linguagem.
int eh_verdadeiro(Valor v) {
    switch (v.tipo) {
        case TIPO_INT:    return v.val.i != 0;
        case TIPO_FLOAT:  return v.val.f != 0.0;
        case TIPO_STRING: return v.val.s[0] != '\0'; // String vazia é falsa.
        default:          return 0; // Nulo e outros tipos são falsos.
    }
}

// Converte qualquer tipo de valor para uma string (para impressão ou concatenação).
char* valor_para_string(Valor v) {
    char buffer[50];
    switch (v.tipo) {
        case TIPO_INT:    sprintf(buffer, "%d", v.val.i); return strdup(buffer);
        case TIPO_FLOAT:  sprintf(buffer, "%g", v.val.f); return strdup(buffer);
        case TIPO_STRING: return strdup(v.val.s);
        case TIPO_NULO:   return strdup("(nulo)");
        default:          return strdup("(tipo desconhecido)");
    }
}

/**
 * @brief Função central do interpretador. Avalia (executa) uma AST recursivamente.
 * * @param a Ponteiro para o nó da AST a ser avaliado.
 * @return Valor O resultado da avaliação do nó.
 */
Valor eval(AstNode *a) {
    Valor v = { .tipo = TIPO_NULO }, v_esq, v_dir, v_indice;
    if (!a) {
        return v; // Se o nó for nulo (ex: comando de declaração), não faz nada.
    }

    Simbolo *s;
    switch (a->nodetype) {
        case 'K': // Constante: o valor já está pronto no nó.
            v = *(Valor*)(a->l);
            break;

        case 'N': // Nome (ID): busca o valor na tabela de símbolos.
            s = (Simbolo*)(a->l);
            v = s->valor;
            break;

        case 'A': // Acesso a Vetor: avalia o índice e pega o valor no vetor.
            s = (Simbolo*)(a->l);
            v_indice = eval(a->r);
            if (s->tipo_declarado != TIPO_VETOR) {
                yyerror("Variavel nao e um vetor");
            } else if (v_indice.tipo != TIPO_INT) {
                yyerror("Indice do vetor deve ser inteiro");
            } else {
                int idx = v_indice.val.i;
                if (idx < 0 || idx >= s->valor.tamanho_vetor) {
                    yyerror("Indice do vetor fora dos limites");
                } else {
                    v = s->valor.val.v[idx]; // Pega o valor na posição correta.
                }
            }
            break;

        case '=': // Atribuição a variável.
            s = (Simbolo*)(a->l);
            v_dir = eval(a->r); // Avalia o lado direito da atribuição.
            // Coerção de tipo: permite atribuir um inteiro a uma variável float.
            if (s->tipo_declarado == TIPO_FLOAT && v_dir.tipo == TIPO_INT) {
                v_dir.tipo = TIPO_FLOAT;
                v_dir.val.f = v_dir.val.i;
            }
            if (s->tipo_declarado != v_dir.tipo) {
                char erro[100];
                sprintf(erro, "Erro de tipo: atribuicao invalida para a variavel '%s'", s->nome);
                yyerror(erro);
            } else {
                s->valor = v_dir; // Atualiza o valor na tabela de símbolos.
            }
            v = s->valor; // O resultado de uma atribuição é o próprio valor atribuído.
            break;

        case 'a': // Atribuição a elemento de vetor.
            s = (Simbolo*)(a->l->l);
            v_dir = eval(a->l->r);
            v_indice = eval(a->r);
            // Validações de tipo e limites.
            if (s->tipo_declarado != TIPO_VETOR) { yyerror("Variavel nao e um vetor"); break; }
            if (v_indice.tipo != TIPO_INT) { yyerror("Indice do vetor deve ser inteiro"); break; }
            // Coerção de tipo.
            if (s->valor.tipo == TIPO_FLOAT && v_dir.tipo == TIPO_INT) {
                v_dir.tipo = TIPO_FLOAT;
                v_dir.val.f = v_dir.val.i;
            }
            if (s->valor.tipo != v_dir.tipo) {
                yyerror("Erro de tipo na atribuicao de valor ao vetor.");
            } else {
                int idx = v_indice.val.i;
                if (idx < 0 || idx >= s->valor.tamanho_vetor) {
                    yyerror("Indice do vetor fora dos limites");
                } else {
                    s->valor.val.v[idx] = v_dir; // Atribui o valor na posição correta.
                    v = v_dir;
                }
            }
            break;

        case '+': // Soma ou Concatenação.
            v_esq = eval(a->l);
            v_dir = eval(a->r);
            // Se um dos operandos for string, faz concatenação.
            if (v_esq.tipo == TIPO_STRING || v_dir.tipo == TIPO_STRING) {
                char *s_esq = valor_para_string(v_esq);
                char *s_dir = valor_para_string(v_dir);
                char *resultado = (char*) malloc(strlen(s_esq) + strlen(s_dir) + 1);
                strcpy(resultado, s_esq);
                strcat(resultado, s_dir);
                v.tipo = TIPO_STRING;
                v.val.s = resultado;
                free(s_esq); free(s_dir);
            // Senão, faz soma numérica.
            } else if ((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) &&
                       (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT)) {
                // Promove para float se necessário.
                if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) {
                    float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
                    float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
                    v.tipo = TIPO_FLOAT;
                    v.val.f = f_esq + f_dir;
                } else {
                    v.tipo = TIPO_INT;
                    v.val.i = v_esq.val.i + v_dir.val.i;
                }
            } else {
                yyerror("Operador '+' invalido para estes tipos.");
            }
            break;

        case '-': case '*': case '/': // Operações aritméticas.
            v_esq = eval(a->l);
            v_dir = eval(a->r);
            if (!((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) &&
                  (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT))) {
                yyerror("Operadores '-', '*' e '/' so podem ser usados com numeros.");
                break;
            }
            // Promove para float se necessário.
            if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) {
                float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
                float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
                v.tipo = TIPO_FLOAT;
                switch(a->nodetype) {
                    case '-': v.val.f = f_esq - f_dir; break;
                    case '*': v.val.f = f_esq * f_dir; break;
                    case '/': v.val.f = f_esq / f_dir; break; // Divisão de float.
                }
            } else {
                v.tipo = TIPO_INT;
                switch(a->nodetype) {
                    case '-': v.val.i = v_esq.val.i - v_dir.val.i; break;
                    case '*': v.val.i = v_esq.val.i * v_dir.val.i; break;
                    case '/': v.val.i = v_esq.val.i / v_dir.val.i; break; // Divisão inteira.
                }
            }
            break;
            
        case 'C': // Comparação.
            v_esq = eval(a->l->l);
            v_dir = eval(a->l->r);
            // Comparações são sempre feitas como floats para simplicidade.
            float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
            float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
            v.tipo = TIPO_INT; // Resultado da comparação é 1 (true) ou 0 (false).
            switch(a->l->nodetype) { // O tipo da comparação está no nó auxiliar.
                case 1: v.val.i = f_esq >  f_dir; break; // >
                case 2: v.val.i = f_esq <  f_dir; break; // <
                case 3: v.val.i = f_esq != f_dir; break; // !=
                case 4: v.val.i = f_esq == f_dir; break; // ==
                case 5: v.val.i = f_esq >= f_dir; break; // >=
                case 6: v.val.i = f_esq <= f_dir; break; // <=
            }
            break;

        case 'M': // Menos unário.
            v = eval(a->l);
            if (v.tipo == TIPO_INT) v.val.i = -v.val.i;
            else if (v.tipo == TIPO_FLOAT) v.val.f = -v.val.f;
            break;

        case 'I': // IF/ELSE.
            if (eh_verdadeiro(eval(a->l))) { // Avalia a condição.
                if(a->r->l) v = eval(a->r->l); // Se verdadeira, executa o corpo IF.
            } else {
                if(a->r->r) v = eval(a->r->r); // Se falsa, executa o corpo ELSE (se existir).
            }
            break;

        case 'W': // WHILE.
            while(eh_verdadeiro(eval(a->l))) { // Avalia a condição a cada iteração.
                v = eval(a->r->l); // Executa o corpo do laço.
            }
            break;

        case 'P': // ESCREVA (Print).
            v = eval(a->l);
            switch (v.tipo) {
                case TIPO_INT:    printf("%d\n", v.val.i);    break;
                case TIPO_FLOAT:  printf("%g\n", v.val.f);    break;
                case TIPO_STRING: printf("%s\n", v.val.s);    break;
                case TIPO_NULO:   printf("(nulo)\n");         break;
                default:          printf("Tipo nao imprimivel\n");
            }
            break;

        case 'R': // LEIA (Read).
            s = (Simbolo*)(a->l->l);
            char buffer[256];
            if(fgets(buffer, 255, stdin)) {
                buffer[strcspn(buffer, "\n")] = 0; // Remove a quebra de linha do final.
                // Converte a string lida para o tipo declarado da variável.
                if (s->tipo_declarado == TIPO_STRING) {
                    s->valor.tipo = TIPO_STRING;
                    s->valor.val.s = strdup(buffer);
                } else if (s->tipo_declarado == TIPO_INT) {
                    s->valor.tipo = TIPO_INT;
                    s->valor.val.i = atoi(buffer);
                } else if (s->tipo_declarado == TIPO_FLOAT) {
                    s->valor.tipo = TIPO_FLOAT;
                    s->valor.val.f = atof(buffer);
                } else {
                    yyerror("Nao e possivel ler valor para este tipo de variavel.");
                }
                v = s->valor;
            }
            break;

        case 'L': // Lista de comandos: executa um após o outro.
            if(a->l) eval(a->l);
            if(a->r) v = eval(a->r);
            break;

        default:
            printf("Erro interno: no desconhecido %c\n", a->nodetype);
    }
    return v;
}

// Função de erro padrão do Yacc/Bison.
void yyerror(char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

// Função principal do programa.
int main(int argc, char **argv) {
    // Permite que o nome do arquivo de entrada seja passado como argumento.
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        // Se nenhum arquivo for passado, tenta abrir um arquivo padrão "entradas.txt".
        yyin = fopen("entradas.txt", "r");
        if (!yyin) {
            perror("Nao foi possivel abrir 'entradas.txt'");
            return 1;
        }
    }
    
    yyparse(); // Inicia o processo de análise sintática.
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
}