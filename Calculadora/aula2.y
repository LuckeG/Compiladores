%{
#include <stdio.h>
#include <math.h>

float var[26];

int yylex();
void yyerror (char *s){
	printf("%s\n", s);
}

%}

%union{
	float flo;
	int inte;
	char* str;
	}

%token <flo>NUM
%token <inte>VARS
%token PRINTF
%token FIM
%token INI
%token SCANF
%token <str> STRING
%left '+' '-'
%left '*' '/'
%right '^'
%right NEG
%type <flo> exp
%type <flo> valor


%%

prog: INI cod FIM
	;

cod: cod cmdos
	|
	;

cmdos: 
	 PRINTF '(' saidas ')'
	| SCANF '(' VARS ')' {
				scanf("%f", &var[$3]);
				}
	| VARS '=' exp {
					var[$1] = $3;
					}
	;

str: STRING { printf("%s\n", $1); free($1); };

saidas: str "," saidas |
 exp "," saidas { printf("%2.f\n", $1); }
 |	str
 |	exp {printf("Número: %2.f\n", $1); };

exp: exp '+' exp {$$ = $1 + $3;}
	|exp '-' exp {$$ = $1 - $3;}
	|exp '*' exp {$$ = $1 * $3;}
	|exp '/' exp {$$ = $1 / $3;}
	|'(' exp ')' {$$ = $2;}
	|exp '^' exp {$$ = pow($1,$3);}
	|'-' exp %prec NEG {$$ = -$2;}
	|valor {$$ = $1;}
	|VARS {$$ = var[$1];}
	;

valor: NUM {$$ = $1;}
	;

%%

#include "lex.yy.c"

int main(){
	yyin=fopen("entradas.txt","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}