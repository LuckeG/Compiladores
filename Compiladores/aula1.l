%{
    #include <stdio.h>
    #include <stdlib.h>
%}

/*expressões regulares*/
INT [0-9]+
LETRA [A-Za-z]+
OP [-+*/]
ATRIB [=]
DELIM [\n\t]
ID {LETRA} ({LETRA}|{INT})*
FLOAT [0-9]+\.[0-9]+
FUNC (printf|scanf|Switch|System|return|include|main)
LOGIC [!=|<|>|<=|>=|&|==|&&]
CONDI (if|else|elif)
REPET (for|do|while)
COMMENT ()

/* token */
%%
"FIM" {printf("Fim do programa\n");}
{INT} {printf("Número: %s\n",yytext);}
{FLOAT} {printf("Número Real: %s\n",yytext);}
{OP} {printf("Operação: %s\n",yytext);}
{ATRIB} {printf("Atribuição: %s\n",yytext);}
{LETRA} {printf("String: %s\n",yytext);}
{DELIM} {printf("Caractere ignorado\n");}
{FUNC} {printf("Função: %s\n",yytext);}
{LOGIC} {printf("Logica: %s\n",yytext);}
{REPET} {printf("Repetição: %s\n",yytext);}
{CONDI} {printf("Condição: %s\n",yytext);}
%%
/*definições*/
int main(){
    yyin=fopen("entrada.lulu","r");
    yylex();
    fclose(yyin);
return 0;
}