all: 
	lex rules.lex
	bison -y -d grammer.y
	g++ -std=c++11 lex.yy.c y.tab.c
