%{
    #include <stdio.h>
    #include <stdlib.h>
%}

/*expressões regulares*/
INT [0-9]+
LETRA [A-Za-z]+
OP [-+*/]
ATRIB [=]
DELIM [ \n\t]+
ID {LETRA} ({LETRA}|{INT})*
FLOAT [0-9]+\.[0-9]+
FUNC (printf|scanf|Switch|System|return|include|main)
LOGIC [!=|<|>|<=|>=|&|==|&&|\'||\"]
SIMB [\;\?\!\%\.\_\:\{\}\[\]\(\)\\]
CONDI (if|else|elif)
REPET (for|do|while)
COMMENT (#.*)

/* token */
%%
"FIM" {printf("Fim do programa\n");}
{INT} {printf("NÚMERO: %s\n",yytext);}
{FLOAT} {printf("NÚMERO REAL: %s\n",yytext);}
{OP} {printf("OPERAÇÃO: %s\n",yytext);}
{ATRIB} {printf("ATRIBUIÇÃO: %s\n",yytext);}
{FUNC} {printf("FUNÇÃO: %s\n",yytext);}
{LETRA} {printf("STRING: %s\n",yytext);}
{DELIM} {printf("CARACTER IGNORADO\n");}
{SIMB} {printf("SIMBOLOS: %s\n",yytext);}
{LOGIC} {printf("LOGICA: %s\n",yytext);}
{REPET} {printf("REPETIÇÃO: %s\n",yytext);}
{CONDI} {printf("CCONDIÇÃO: %s\n",yytext);}
{COMMENT} {printf("COMENTARIO: %s\n",yytext);}
%%
/*definições*/
int main(){
    yyin=fopen("entrada.lulu","r");
    yylex();
    fclose(yyin);
return 0;
}