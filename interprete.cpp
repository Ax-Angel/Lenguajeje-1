#include "interprete.hpp"
#include "lexer.hpp"

Interprete::Interprete(std::istream &entrada) : entrada(entrada), lexer(std::make_shared<Lexer>(entrada)) {}

void Interprete::cicloDeLectura() {
  
}
