all: aula2.l aula2.y
	clear
	flex -i aula2.l
	bison aula2.y
	gcc aula2.tab.c -o Calculadora -lfl -lm
	./Calculadora