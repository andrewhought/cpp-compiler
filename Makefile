a.out :main.o inputbuf.o lexer.o parser.o
	g++ -o compiler main.o inputbuf.o lexer.o parser.o

main.o :main.cc
	g++ -c main.cc

inputbuf.o :inputbuf.cc inputbuf.h
	g++ -c inputbuf.cc

lexer.o :lexer.cc lexer.h
	g++ -c lexer.cc

parser.o :parser.cc parser.h
	g++ -c parser.cc

clean :
	rm *.o compiler