/* lex.l - Analisador Léxico para a Linguagem Auge (VERSÃO CORRIGIDA) */
%{
#include <string.h>
#include "y.tab.h" // Inclui definições do Yacc/Bison

// Função para remover as aspas de um literal de string
void remove_quotes(char* str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}
%}

/* Definições de Padrões (Expressões Regulares) */
NUM             [0-9]+\.?[0-9]*
VARS            [a-zA-Z_][a-zA-Z0-9_]*
STRING_LITERAL  \"[^\"\n]*\"
COMMENT         \/\/[^\n]*

/* Palavras-Chave (usando as definições acima) */
FIM     "FIM"
IF      "IF"
ELSE    "ELSE"
WHILE   "WHILE"
PRINT   "PRINT"
PRINTT  "PRINTT"
SCAN    "LER"
SCANS   "LERS"
DECL    "var"

%%

{FIM} { return FIM; }
{IF} { return IF; }
{ELSE} { return ELSE; }
{WHILE} { return WHILE; }
{PRINTT} { return PRINTT; }
{PRINT} { return PRINT; }
{SCAN} { return SCAN; }
{SCANS} { return SCANS; }
{DECL} { return DECL; }

{COMMENT}

{VARS} {
    strcpy(yylval.str, yytext);
    return VARS;
}

{STRING_LITERAL} {
    strcpy(yylval.str, yytext);
    remove_quotes(yylval.str);
    return STRING_LITERAL;
}

{NUM} {
    yylval.flo = atof(yytext);
    return NUM;
}

">" { yylval.fn = 1; return CMP; }
"<" { yylval.fn = 2; return CMP; }
"!=" { yylval.fn = 3; return CMP; }
"==" { yylval.fn = 4; return CMP; }
">=" { yylval.fn = 5; return CMP; }
"<=" { yylval.fn = 6; return CMP; }


[-+()=/*;\[\]{}] { return *yytext; }

[ \n\t\r]+ { ;  }

. { printf("Caractere desconhecido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
