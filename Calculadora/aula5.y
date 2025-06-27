%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* ================================================================== */
/* ETAPA 1: DEFINIÇÃO DE ESTRUTURAS E TIPOS                           */
/* (Definir tudo antes do uso para evitar erros de tipo)              */
/* ================================================================== */

/* Tipos de Variáveis na Tabela de Símbolos */
// 0 - Indefinido, 1 - Numérico, 2 - String, 3 - Vetor
typedef struct vars {
    int type;
    char name[50];
    double valor;
    char *valors;
    double *vet;
    struct vars *prox;
} VARI;

/* --- Estruturas da Árvore Sintática Abstrata (AST) --- */
typedef struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
} Ast;

typedef struct numval { int nodetype; double number; } Numval;
typedef struct varval { int nodetype; char var[50]; int size; } Varval;
typedef struct textval { int nodetype; char *txt; } Textval;
typedef struct flow { int nodetype; Ast *cond; Ast *tl; Ast *el; } Flow;
typedef struct symasgn { int nodetype; char s[50]; Ast *v; int pos; } Symasgn;

/* ================================================================== */
/* ETAPA 2: PROTÓTIPOS DAS FUNÇÕES                                    */
/* ================================================================== */

int yylex();
void yyerror(char *s);

/* Funções do Interpretador */
double eval(Ast *a);
char* eval_str(Ast *a);

/* Funções de construção da AST (exemplos) */
Ast* newast(int nodetype, Ast *l, Ast *r);
Ast* newnum(double d);
VARI *l1; // Tabela de Símbolos Global

/* ================================================================== */
/* ETAPA 3: IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES                      */
/* ================================================================== */

/* --- Funções da Tabela de Símbolos --- */
VARI* ins(VARI* l, char n[]) {
    VARI* new = (VARI*)malloc(sizeof(VARI));
    strcpy(new->name, n);
    new->type = 0; new->valor = 0.0; new->valors = NULL; new->vet = NULL;
    new->prox = l;
    return new;
}

VARI* ins_a(VARI* l, char n[], int tamanho) {
    VARI* new = (VARI*)malloc(sizeof(VARI));
    strcpy(new->name, n);
    new->vet = (double*)malloc(tamanho * sizeof(double));
    new->prox = l;
    new->type = 3; new->valor = 0.0; new->valors = NULL;
    return new;
}

VARI* srch(VARI* l, char n[]) {
    for(VARI* aux = l; aux != NULL; aux = aux->prox) {
        if(strcmp(n, aux->name) == 0) return aux;
    }
    return NULL;
}

/* --- Funções para Construção da AST (implementação completa) --- */
Ast* newast(int nodetype, Ast *l, Ast *r) {
    Ast *a = (Ast*)malloc(sizeof(Ast));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; a->l = l; a->r = r;
    return a;
}

Ast* newvari(int nodetype, char nome[50]) {
    Varval *a = (Varval*)malloc(sizeof(Varval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; strcpy(a->var, nome);
    return (Ast*)a;
}

Ast* newarray(int nodetype, char nome[50], int tam) {
    Varval *a = (Varval*)malloc(sizeof(Varval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; strcpy(a->var, nome); a->size = tam;
    return (Ast*)a;
}

Ast* newtext(int nodetype, char* txt) {
    Textval *a = (Textval*)malloc(sizeof(Textval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; a->txt = strdup(txt);
    return (Ast*)a;
}

Ast* newnum(double d) {
    Numval *a = (Numval*)malloc(sizeof(Numval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = 'K'; a->number = d;
    return (Ast*)a;
}

Ast* newflow(int nodetype, Ast *cond, Ast *tl, Ast *el) {
    Flow *a = (Flow*)malloc(sizeof(Flow));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; a->cond = cond; a->tl = tl; a->el = el;
    return (Ast *)a;
}

Ast* newcmp(int cmptype, Ast *l, Ast *r) {
    Ast *a = (Ast*)malloc(sizeof(Ast));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = '0' + cmptype; a->l = l; a->r = r;
    return a;
}

Ast* newasgn(int nodetype, char s[50], Ast *v) {
    Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = nodetype; strcpy(a->s, s); a->v = v;
    return (Ast *)a;
}

Ast* newasgn_a(char s[50], Ast *v, int indice) {
    Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = '='; strcpy(a->s, s); a->v = v; a->pos = indice;
    return (Ast *)a;
}

Ast* newValorVal(char s[]) {
    Varval *a = (Varval*)malloc(sizeof(Varval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = 'N'; strcpy(a->var, s);
    return (Ast*)a;
}

Ast* newValorVal_a(char s[], int indice) {
    Varval *a = (Varval*)malloc(sizeof(Varval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = 'n'; strcpy(a->var, s); a->size = indice;
    return (Ast*)a;
}

Ast* newValorValS(char s[50]) {
    Varval *a = (Varval*)malloc(sizeof(Varval));
    if(!a) { yyerror("out of space"); exit(0); }
    a->nodetype = 'Q'; strcpy(a->var, s);
    return (Ast*)a;
}

/* --- Interpretador (Funções eval e eval_str) --- */
char* eval_str(Ast *a) {
    if (!a) { yyerror("internal error, null eval_str"); return NULL; }
    switch(a->nodetype) {
        case 'Q': {
            VARI* aux1 = srch(l1, ((Varval*)a)->var);
            if (!aux1) { yyerror("Variável não declarada"); return ""; }
            if (aux1->type != 2) { yyerror("Incompatibilidade de tipo: esperando string"); return ""; }
            return aux1->valors;
        }
        case 'T': return ((Textval*)a)->txt;
        default: yyerror("Erro interno: nó inválido para string"); return "";
    }
}

double eval(Ast *a) {
    double v = 0.0;
    if(!a) { return 0.0; }

    switch(a->nodetype) {
        case 'K': v = ((Numval *)a)->number; break;
        case 'N': {
            VARI* aux1 = srch(l1, ((Varval*)a)->var);
            if (!aux1) { yyerror("Variável não declarada"); v = 0.0; }
            else if (aux1->type != 1 && aux1->type != 0) { yyerror("Incompatibilidade de tipo: esperando número"); v = 0.0; }
            else v = aux1->valor;
            break;
        }
        case 'n': {
            VARI* aux1 = srch(l1, ((Varval*)a)->var);
            if (!aux1) { yyerror("Vetor não declarado"); v = 0.0; }
            else v = aux1->vet[((Varval*)a)->size];
            break;
        }
        case '+': v = eval(a->l) + eval(a->r); break;
        case '-': v = eval(a->l) - eval(a->r); break;
        case '*': v = eval(a->l) * eval(a->r); break;
        case '/': v = eval(a->l) / eval(a->r); break;
        case 'M': v = -eval(a->l); break;
        case '1': v = (eval(a->l) > eval(a->r))  ? 1 : 0; break;
        case '2': v = (eval(a->l) < eval(a->r))  ? 1 : 0; break;
        case '3': v = (eval(a->l) != eval(a->r)) ? 1 : 0; break;
        case '4': v = (eval(a->l) == eval(a->r)) ? 1 : 0; break;
        case '5': v = (eval(a->l) >= eval(a->r)) ? 1 : 0; break;
        case '6': v = (eval(a->l) <= eval(a->r)) ? 1 : 0; break;
        case '=': {
            v = eval(((Symasgn *)a)->v);
            VARI* aux = srch(l1, ((Symasgn *)a)->s);
            if (!aux) { yyerror("Variável não declarada"); break; }
            if (aux->type == 3) { aux->vet[((Symasgn*)a)->pos] = v; }
            else { aux->valor = v; aux->type = 1; }
            break;
        }
        case '@': {
            char *str_val = eval_str(((Symasgn *)a)->v);
            VARI* aux = srch(l1, ((Symasgn *)a)->s);
            if (!aux) { yyerror("Variável não declarada"); break; }
            free(aux->valors);
            aux->valors = strdup(str_val);
            aux->type = 2;
            break;
        }
        case 'I':
            if (eval(((Flow*)a)->cond) != 0) { if (((Flow*)a)->tl) v = eval(((Flow*)a)->tl); }
            else { if (((Flow*)a)->el) v = eval(((Flow*)a)->el); }
            break;
        case 'W': while(eval(((Flow*)a)->cond) != 0) { v = eval(((Flow*)a)->tl); } break;
        case 'L': eval(a->l); v = eval(a->r); break;
        case 'V': l1 = ins(l1, ((Varval*)a)->var); break;
        /* CORREÇÃO DO ERRO DE SINTAXE AQUI */
        case 'a': l1 = ins_a(l1, ((Varval*)a)->var, ((Varval*)a)->size); break;
        case 'P': printf("%.2f\n", eval(a->l)); break;
        case 'Y': printf("%s\n", eval_str(a->l)); break;
        case 'S': {
            VARI* aux = srch(l1, ((Varval*)a)->var);
            if (!aux) { yyerror("Variável não declarada"); break; }
            printf("> "); scanf("%lf", &aux->valor); aux->type = 1;
            break;
        }
        case 'E': {
            VARI* aux = srch(l1, ((Varval*)a)->var);
            if (!aux) { yyerror("Variável não declarada"); break; }
            char buffer[256];
            printf("> "); scanf("%255s", buffer);
            free(aux->valors); aux->valors = strdup(buffer); aux->type = 2;
            break;
        }
        default: printf("Erro interno: nó inválido %c\n", a->nodetype);
    }
    return v;
}

%}

/* --- Definições de Tokens e Tipos --- */
%union {
    float flo;
    int fn;
    char str[256];
    Ast *a;
}

%token <flo> NUM
%token <str> VARS STRING_LITERAL
%token FIM IF ELSE WHILE PRINT DECL SCAN SCANS PRINTT
%token <fn> CMP

%right '='
%left '+' '-'
%left '*' '/'
%left CMP

/* AQUI, 'prog' foi removido de %type pois não precisa retornar valor */
%type <a> exp list stmt string_exp

%nonassoc IFX
%nonassoc ELSE
%precedence NEG

%%

/* --- Regras da Gramática Corrigidas --- */

/* Regra principal: um programa é uma lista de comandos (list) seguida por FIM */
/* Isso resolve o conflito reduce/reduce */
program: list FIM { printf("\nExecução finalizada.\n"); }
       | FIM      { printf("\nExecução finalizada.\n"); } /* Permite arquivo vazio */
       ;

list:
    | list stmt { if($2) eval($2); }
    ;

stmt: exp ';'                     { $$ = $1; }
    | PRINT '(' exp ')' ';'       { $$ = newast('P', $3, NULL); }
    | PRINTT '(' string_exp ')'';' { $$ = newast('Y', $3, NULL); }
    | SCAN '(' VARS ')' ';'       { $$ = newvari('S', $3); }
    | SCANS '(' VARS ')' ';'      { $$ = newvari('E', $3); }
    | DECL VARS ';'               { $$ = newvari('V', $2); }
    | DECL VARS '[' NUM ']' ';'   { $$ = newarray('a', $2, (int)$4); }
    | VARS '=' exp ';'            { $$ = newasgn('=', $1, $3); }
    | VARS '=' string_exp ';'     { $$ = newasgn('@', $1, $3); }
    | VARS '[' NUM ']' '=' exp ';'{ $$ = newasgn_a($1, $6, (int)$3); }
    | WHILE '(' exp ')' '{' list '}' { $$ = newflow('W', $3, $6, NULL); }
    | IF '(' exp ')' '{' list '}' %prec IFX { $$ = newflow('I', $3, $6, NULL); }
    | IF '(' exp ')' '{' list '}' ELSE '{' list '}' { $$ = newflow('I', $3, $6, $10); }
    | ';'                         { $$ = NULL; }
    ;

exp : NUM                         { $$ = newnum($1); }
    | VARS                        { $$ = newValorVal($1); }
    | VARS '[' NUM ']'            { $$ = newValorVal_a($1, (int)$3); }
    | exp '+' exp                 { $$ = newast('+', $1, $3); }
    | exp '-' exp                 { $$ = newast('-', $1, $3); }
    | exp '*' exp                 { $$ = newast('*', $1, $3); }
    | exp '/' exp                 { $$ = newast('/', $1, $3); }
    | exp CMP exp                 { $$ = newcmp($2, $1, $3); }
    | '-' exp %prec NEG           { $$ = newast('M', $2, NULL); }
    | '(' exp ')'                 { $$ = $2; }
    ;

string_exp: STRING_LITERAL        { $$ = newtext('T', $1); }
          | VARS                  { $$ = newValorValS($1); }
          ;

%%
/* --- Função Principal e de Erro --- */
extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    } else {
        printf("Nenhum arquivo de entrada. Use: ./analisador <arquivo.auge>\n");
        return 1;
    }
    yyparse();
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
