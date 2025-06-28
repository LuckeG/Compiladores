all : aula5.l aula5.y
	clear
	flex aula5.l
	bison -d aula5.y
	gcc aula5.tab.c lex.yy.c -o calculadora -lm
	./calculadora 

clean:
	rm -f $(TARGET) aula5.tab.c aula5.tab.h lex.yy.c *.o