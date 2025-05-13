%{
    #include <stdio.h>
%}

%{
	char aux[30];
%}

NUM [0-9]+\.?[0-9]*
VARS [a-z]
PRINTF "ESCREVA"
INI "INICIO"
FIM "FIM"
SCANF "LEIA"


%%
{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}
	
{VARS} {
	yylval.inte = *yytext - 'a';
	return VARS;
	}
	
"ESCREVA" {
	return PRINTF;
}

"LEIA" {
	return SCANF;
}
[-+()=/*^] {
	return *yytext;
	}
	
{INI} {
	return INI;
	}			
	
{FIM} {
	return FIM;
	}		

[ \t\r\n]+   ;

. {printf("(%s) Ingnorado\n",yytext); return 0;}
%%

int yywrap() { return 1; }