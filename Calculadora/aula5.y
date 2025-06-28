%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    // ... (toda a seção de protótipos e structs permanece a mesma)
    void yyerror(char *s);
    int yylex(void);
    extern FILE *yyin;
    typedef enum { TIPO_INT, TIPO_FLOAT, TIPO_STRING, TIPO_VETOR, TIPO_NULO } Tipo;
    typedef union { int i; float f; char *s; struct Valor *v; } ValorUnion;
    typedef struct Valor { Tipo tipo; ValorUnion val; int tamanho_vetor; } Valor;
    typedef struct Simbolo { char *nome; Tipo tipo_declarado; Valor valor; struct Simbolo *prox; } Simbolo;
    typedef struct AstNode { int nodetype; struct AstNode *l; struct AstNode *r; } AstNode;
    Simbolo *tabela_simbolos = NULL;
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
    Valor eval(AstNode *a);
    char* valor_para_string(Valor v);
%}

%union { int ival; float fval; char *str; int fn; struct AstNode *a; }
%token T_INTEIRO T_REAL T_TEXTO
%token <ival> NUM_INT
%token <fval> NUM_FLOAT
%token <str> ID TEXTO
%token INICIO SE SENAO ENQUANTO ESCREVA LEIA VAR FIM
%token <fn> CMP
%type <a> exp lista_comandos comando
%type <ival> tipo_var
%right '='
%left CMP
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%nonassoc SENAO_PREC

%%

programa:
      INICIO lista_comandos FIM { if($2) eval($2); }
    | INICIO FIM { /* Programa vazio */ }
    ;

lista_comandos:
      /* Lista pode ser vazia */
      { $$ = NULL; } 
    | lista_comandos comando
      { 
          if ($1 == NULL) { $$ = $2; } 
          else if ($2 == NULL) { $$ = $1; } // Ignora comandos nulos (declarações)
          else { $$ = novo_no_ast('L', $1, $2); }
      }
    ;

/* --- GRAMÁTICA CORRIGIDA --- */
comando:
      VAR tipo_var ID ';' 
        { insere_simbolo($3, (Tipo)$2); $$ = NULL; } // <<< CORREÇÃO: Retorna NULL
    | VAR tipo_var ID '[' exp ']' ';'
        {
            Simbolo *s = insere_simbolo($3, TIPO_VETOR);
            s->valor.tipo = (Tipo)$2;
            Valor v_indice = eval($5);
            if (v_indice.tipo == TIPO_INT) {
                s->valor.tamanho_vetor = v_indice.val.i;
                s->valor.val.v = (Valor*)calloc(v_indice.val.i, sizeof(Valor));
            } else {
                yyerror("Tamanho do vetor deve ser um inteiro.");
            }
            $$ = NULL; // <<< CORREÇÃO: Retorna NULL
        }
    | ID '=' exp ';' 
        { $$ = novo_no_atribuicao($1, $3); }
    | ID '[' exp ']' '=' exp ';' 
        { $$ = novo_no_atribuicao_vetor($1, $3, $6); }
    | SE '(' exp ')' '{' lista_comandos '}' 
        { $$ = novo_no_controle('I', $3, $6, NULL); }
    | SE '(' exp ')' '{' lista_comandos '}' SENAO '{' lista_comandos '}' 
        { $$ = novo_no_controle('I', $3, $6, $10); }
    | ENQUANTO '(' exp ')' '{' lista_comandos '}' 
        { $$ = novo_no_controle('W', $3, $6, NULL); }
    | ESCREVA '(' exp ')' ';' 
        { $$ = novo_no_ast('P', $3, NULL); }
    | LEIA '(' ID ')' ';' 
        { $$ = novo_no_ast('R', novo_no_id($3), NULL); }
    ;

tipo_var:
      T_INTEIRO { $$ = TIPO_INT; }
    | T_REAL    { $$ = TIPO_FLOAT; }
    | T_TEXTO   { $$ = TIPO_STRING; }
    ;

exp:
    NUM_INT { $$ = (AstNode*)novo_no_num_int($1); }
    | NUM_FLOAT { $$ = (AstNode*)novo_no_num_float($1); }
    | TEXTO { $$ = (AstNode*)novo_no_texto($1); }
    | ID { $$ = (AstNode*)novo_no_id($1); }
    | ID '[' exp ']' { $$ = novo_no_vetor_acesso($1, $3); }
    | exp '+' exp { $$ = novo_no_ast('+', $1, $3); }
    | exp '-' exp { $$ = novo_no_ast('-', $1, $3); }
    | exp '*' exp { $$ = novo_no_ast('*', $1, $3); }
    | exp '/' exp { $$ = novo_no_ast('/', $1, $3); }
    | exp CMP exp { $$ = novo_no_comparacao($2, $1, $3); }
    | '-' exp %prec UMINUS{ $$ = novo_no_ast('M', $2, NULL); }
    | '(' exp ')' { $$ = $2; }
    ;

%%

/* --- SEÇÃO DE CÓDIGO C --- */
/* Esta seção deve conter a implementação COMPLETA de todas as suas funções. */

// (Cole aqui o código C completo da resposta anterior, começando com busca_simbolo e terminando com main)
Simbolo* busca_simbolo(char *nome) { Simbolo *s; for (s = tabela_simbolos; s != NULL; s = s->prox) { if (strcmp(s->nome, nome) == 0) return s; } return NULL; }
Simbolo* insere_simbolo(char *nome, Tipo tipo_dec) { if (busca_simbolo(nome) != NULL) { yyerror("Variavel ja declarada."); return NULL; } Simbolo *s = (Simbolo*) malloc(sizeof(Simbolo)); s->nome = strdup(nome); s->tipo_declarado = tipo_dec; s->valor.tipo = TIPO_NULO; s->prox = tabela_simbolos; tabela_simbolos = s; return s; }
AstNode* novo_no_ast(int nodetype, AstNode *l, AstNode *r) { AstNode *a = (AstNode*)malloc(sizeof(AstNode)); a->nodetype = nodetype; a->l = l; a->r = r; return a; }
AstNode* novo_no_num_int(int ival) { Valor *v = (Valor*)malloc(sizeof(Valor)); v->tipo = TIPO_INT; v->val.i = ival; return novo_no_ast('K', (AstNode*)v, NULL); }
AstNode* novo_no_num_float(float fval) { Valor *v = (Valor*)malloc(sizeof(Valor)); v->tipo = TIPO_FLOAT; v->val.f = fval; return novo_no_ast('K', (AstNode*)v, NULL); }
AstNode* novo_no_texto(char *sval) { Valor *v = (Valor*)malloc(sizeof(Valor)); v->tipo = TIPO_STRING; v->val.s = strdup(sval); return novo_no_ast('K', (AstNode*)v, NULL); }
AstNode* novo_no_id(char *id) { Simbolo *s = busca_simbolo(id); if (s == NULL) { char err[100]; sprintf(err, "Variavel '%s' nao declarada", id); yyerror(err); exit(1); } return novo_no_ast('N', (AstNode*)s, NULL); }
AstNode* novo_no_vetor_acesso(char *id, AstNode *indice) { Simbolo *s = busca_simbolo(id); if (s == NULL) { yyerror("Vetor nao declarado"); exit(1); } return novo_no_ast('A', (AstNode*)s, indice); }
AstNode* novo_no_atribuicao(char *id, AstNode *valor) { Simbolo *s = busca_simbolo(id); if (s == NULL) { yyerror("Variavel nao declarada"); exit(1); } return novo_no_ast('=', (AstNode*)s, valor); }
AstNode* novo_no_atribuicao_vetor(char *id, AstNode *indice, AstNode* valor) { Simbolo *s = busca_simbolo(id); if (s == NULL) { yyerror("Vetor nao declarado"); exit(1); } AstNode *temp = novo_no_ast('=', (AstNode*)s, valor); return novo_no_ast('a', temp, indice); }
AstNode* novo_no_controle(int nodetype, AstNode *cond, AstNode *corpo_v, AstNode *corpo_f) { AstNode *a = (AstNode*)malloc(sizeof(AstNode)); a->nodetype = nodetype; a->l = cond; a->r = novo_no_ast(0, corpo_v, corpo_f); return a; }
AstNode* novo_no_comparacao(int cmptype, AstNode *l, AstNode *r) { AstNode *a = (AstNode*)malloc(sizeof(AstNode)); a->nodetype = 'C'; a->l = novo_no_ast(cmptype, l, r); return a; }
int eh_verdadeiro(Valor v) { switch (v.tipo) { case TIPO_INT: return v.val.i != 0; case TIPO_FLOAT: return v.val.f != 0.0; case TIPO_STRING: return v.val.s[0] != '\0'; default: return 0; } }
char* valor_para_string(Valor v) { char buffer[50]; switch (v.tipo) { case TIPO_INT: sprintf(buffer, "%d", v.val.i); return strdup(buffer); case TIPO_FLOAT: sprintf(buffer, "%g", v.val.f); return strdup(buffer); case TIPO_STRING: return strdup(v.val.s); case TIPO_NULO: return strdup("(nulo)"); default: return strdup("(tipo desconhecido)"); } }
Valor eval(AstNode *a) { Valor v = { .tipo = TIPO_NULO }, v_esq, v_dir, v_indice; if (!a) { return v; } Simbolo *s; switch (a->nodetype) { case 'K': v = *(Valor*)(a->l); break; case 'N': s = (Simbolo*)(a->l); v = s->valor; break; case 'A': s = (Simbolo*)(a->l); v_indice = eval(a->r); if (s->tipo_declarado != TIPO_VETOR) { yyerror("Variavel nao e um vetor"); } else if (v_indice.tipo != TIPO_INT) { yyerror("Indice do vetor deve ser inteiro"); } else { int idx = v_indice.val.i; if (idx < 0 || idx >= s->valor.tamanho_vetor) { yyerror("Indice do vetor fora dos limites"); } else { v = s->valor.val.v[idx]; } } break; case '=': s = (Simbolo*)(a->l); v_dir = eval(a->r); if (s->tipo_declarado == TIPO_FLOAT && v_dir.tipo == TIPO_INT) { v_dir.tipo = TIPO_FLOAT; v_dir.val.f = v_dir.val.i; } if (s->tipo_declarado != v_dir.tipo) { char erro[100]; sprintf(erro, "Erro de tipo: atribuicao invalida para a variavel '%s'", s->nome); yyerror(erro); } else { s->valor = v_dir; } v = s->valor; break; case 'a': s = (Simbolo*)(a->l->l); v_dir = eval(a->l->r); v_indice = eval(a->r); if (s->tipo_declarado != TIPO_VETOR) { yyerror("Variavel nao e um vetor"); break; } if (v_indice.tipo != TIPO_INT) { yyerror("Indice do vetor deve ser inteiro"); break; } if (s->valor.tipo == TIPO_FLOAT && v_dir.tipo == TIPO_INT) { v_dir.tipo = TIPO_FLOAT; v_dir.val.f = v_dir.val.i; } if (s->valor.tipo != v_dir.tipo) { yyerror("Erro de tipo na atribuicao de valor ao vetor."); } else { int idx = v_indice.val.i; if (idx < 0 || idx >= s->valor.tamanho_vetor) { yyerror("Indice do vetor fora dos limites"); } else { s->valor.val.v[idx] = v_dir; v = v_dir; } } break; case '+': v_esq = eval(a->l); v_dir = eval(a->r); if (v_esq.tipo == TIPO_STRING || v_dir.tipo == TIPO_STRING) { char *s_esq = valor_para_string(v_esq); char *s_dir = valor_para_string(v_dir); char *resultado = (char*) malloc(strlen(s_esq) + strlen(s_dir) + 1); strcpy(resultado, s_esq); strcat(resultado, s_dir); v.tipo = TIPO_STRING; v.val.s = resultado; free(s_esq); free(s_dir); } else if ((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) && (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT)) { if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) { float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f; float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f; v.tipo = TIPO_FLOAT; v.val.f = f_esq + f_dir; } else { v.tipo = TIPO_INT; v.val.i = v_esq.val.i + v_dir.val.i; } } else { yyerror("Operador '+' invalido para estes tipos."); } break; case '-': case '*': case '/': v_esq = eval(a->l); v_dir = eval(a->r); if (!((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) && (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT))) { yyerror("Operadores '-', '*' e '/' so podem ser usados com numeros."); break; } if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) { float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f; float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f; v.tipo = TIPO_FLOAT; switch(a->nodetype) { case '-': v.val.f = f_esq - f_dir; break; case '*': v.val.f = f_esq * f_dir; break; case '/': v.val.f = f_esq / f_dir; break; } } else { v.tipo = TIPO_INT; switch(a->nodetype) { case '-': v.val.i = v_esq.val.i - v_dir.val.i; break; case '*': v.val.i = v_esq.val.i * v_dir.val.i; break; case '/': v.val.i = v_esq.val.i / v_dir.val.i; break; } } break; case 'C': v_esq = eval(a->l->l); v_dir = eval(a->l->r); float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f; float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f; v.tipo = TIPO_INT; switch(a->l->nodetype) { case 1: v.val.i = f_esq > f_dir; break; case 2: v.val.i = f_esq < f_dir; break; case 3: v.val.i = f_esq != f_dir; break; case 4: v.val.i = f_esq == f_dir; break; case 5: v.val.i = f_esq >= f_dir; break; case 6: v.val.i = f_esq <= f_dir; break; } break;
        case 'M': v = eval(a->l); if (v.tipo == TIPO_INT) v.val.i = -v.val.i; else if (v.tipo == TIPO_FLOAT) v.val.f = -v.val.f; break; case 'I': if (eh_verdadeiro(eval(a->l))) { if(a->r->l) v = eval(a->r->l); } else { if(a->r->r) v = eval(a->r->r); } break; case 'W': while(eh_verdadeiro(eval(a->l))) { v = eval(a->r->l); } break; case 'P': v = eval(a->l); switch (v.tipo) { case TIPO_INT: printf("%d\n", v.val.i); break; case TIPO_FLOAT: printf("%g\n", v.val.f); break; case TIPO_STRING: printf("%s\n", v.val.s); break; case TIPO_NULO: printf("(nulo)\n"); break; default: printf("Tipo nao imprimivel\n"); } break; case 'R': s = (Simbolo*)(a->l->l); char buffer[256]; if(fgets(buffer, 255, stdin)) { buffer[strcspn(buffer, "\n")] = 0; if (s->tipo_declarado == TIPO_STRING) { s->valor.tipo = TIPO_STRING; s->valor.val.s = strdup(buffer); } else if (s->tipo_declarado == TIPO_INT) { s->valor.tipo = TIPO_INT; s->valor.val.i = atoi(buffer); } else if (s->tipo_declarado == TIPO_FLOAT) { s->valor.tipo = TIPO_FLOAT; s->valor.val.f = atof(buffer); } else { yyerror("Nao e possivel ler valor para este tipo de variavel."); } v = s->valor; } break;
        case 'L': if(a->l) eval(a->l); if(a->r) v = eval(a->r); break;
        default: printf("Erro interno: no desconhecido %c\n", a->nodetype);
    }
    return v;
}
void yyerror(char *s) { fprintf(stderr, "Erro: %s\n", s); }
int main(int argc, char **argv) { if (argc > 1) { yyin = fopen(argv[1], "r"); if (!yyin) { perror(argv[1]); return 1; } } else { yyin = fopen("entradas.txt", "r"); if (!yyin) { perror("Nao foi possivel abrir 'entradas.txt'"); return 1; } } yyparse(); if (yyin != stdin) { fclose(yyin); } return 0; }