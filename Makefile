SOURCE=token.hpp token.cpp lexer.hpp lexer.cpp tablas.hpp tablas.cpp main.cpp
MYPROGRAM=anaLex

CC=g++

FLAGS=-std=c++11

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(FLAGS) $(SOURCE) -o $(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)
