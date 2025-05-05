%{

%}

NUM [0-9]+
FIM "FIM"
INICIO "INICIO"
FUNC "escreva" | "leia"
LETRA [a-zA-Z]
%%
{NUM} {
	yylval = atoi(yytext);
	return NUM;
	}
	
{FIM} {return FIM;}
{INICIO} {return INICIO;}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"=" {return '=';}
"(" {return '(';}
")" {return ')';}
[\ \n\t]*	{;}
	
%%