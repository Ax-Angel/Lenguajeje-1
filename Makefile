SOURCE=src/token.hpp src/token.cpp src/lexer.hpp src/lexer.cpp src/tablas.hpp src/tablas.cpp src/main.cpp
MYPROGRAM=anaLex

CC=g++

FLAGS=-std=c++11

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(FLAGS) $(SOURCE) -o $(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)
