all : aula5.l aula5.y
	clear
	flex -i aula5.l
	bison aula5.y
	gcc aula5.tab.c -o analisador -lfl -lm
	./analisador

clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(TARGET) aula5.tab.c aula5.tab.h lex.yy.c *.o
