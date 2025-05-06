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
	}

%token <flo>NUM
%token <inte>VARS
%token PRINT
%token FIM
%token INI
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

cmdos: PRINT '(' exp ')' {
						printf ("%.2f \n",$3);
						}
	| VARS '=' exp {
					var[$1] = $3;
					}
	;

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
	yyin=fopen("Calculos.txt","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}