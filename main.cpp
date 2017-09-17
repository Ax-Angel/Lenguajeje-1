#include <fstream>
#include <iostream>
#include <memory>

#include "lexer.hpp"

Tabla* tabla = Tabla::obtenerInstancia();

int main (int argc, char* argv[]) {
  std::ifstream file(argv[1]);
  std::istream &entrada(file);

  std::shared_ptr<Lexer> lexer(std::make_shared<Lexer>(entrada));
  
  while (!entrada.eof()) {
    auto &t = *lexer -> obtenerSiguienteToken();
    tabla -> agregarToken(t);
    std::cout << t.obtenerPosicion() << " " << t.obtenerLinea() << " " << t.obtenerColumna() << " " << t.obtenerClase() << " " << t.obtenerValor() << std::endl;
  }

  return 0;
}
