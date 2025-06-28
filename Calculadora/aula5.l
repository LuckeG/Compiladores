%{
#include <string.h>
#include "aula5.tab.h"

void copia_valor_str() {
    yylval.str = strdup(yytext);
}
%}

NUM_FLOAT   [0-9]+\.[0-9]+
NUM_INT     [0-9]+
ID          [a-zA-Z_][a-zA-Z0-9_]*

%%
"//".* { /* Ignora comentários de linha */ }
[ \t\n\r]+        { /* Ignora espaços em branco, tabs, novas linhas e non-breaking spaces */ }

"INTEIRO"           { return T_INTEIRO; }
"REAL"              { return T_REAL; }
"TEXTO"             { return T_TEXTO; }

"SE"                { return SE; }
"SENAO"             { return SENAO; }
"while"             { return ENQUANTO; }
"print"             { return ESCREVA; }
"LEIA"              { return LEIA; }
"VAR"               { return VAR; }
"INICIO"            { return INICIO; }
"FIM"               { return FIM; }

{NUM_FLOAT}         { yylval.fval = atof(yytext); return NUM_FLOAT; }
{NUM_INT}           { yylval.ival = atoi(yytext); return NUM_INT; }

{ID}                { copia_valor_str(); return ID; }

"\""[^"\n"]*"\""    {
                      yytext[yyleng-1] = '\0';
                      yylval.str = strdup(yytext + 1);
                      return TEXTO;
                    }

">"                 { yylval.fn = 1; return CMP; }
"<"                 { yylval.fn = 2; return CMP; }
"!="                { yylval.fn = 3; return CMP; }
"=="                { yylval.fn = 4; return CMP; }
">="                { yylval.fn = 5; return CMP; }
"<="                { yylval.fn = 6; return CMP; }

[-+()=*/;{}[\]]     { return *yytext; }

.                   { printf("Caractere desconhecido: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}