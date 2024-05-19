a.out :inputbuf.o lexer.o
	 g++ -o a.out inputbuf.o lexer.o

inputbuf.o	:inputbuf.cc inputbuf.h
	 g++ -c inputbuf.cc

lexer.o	:lexer.cc lexer.h
	 g++ -c lexer.cc

clean	:
	rm *.o a.out