all : analisador.l analisador.y
	clear
	flex analisador.l
	bison -d analisador.y
	gcc analisador.tab.c lex.yy.c -o calculadora -lm
	./calculadora 

clean:
	rm -f $(TARGET) analisador.tab.c analisador.tab.h lex.yy.c *.o