/*
	Analizador Léxico
	Creado por: Mateo Torres Ruiz y Ángel Rodríguez Mendoza
	Proyecto para la asignatura de Compiladores 2018-1 Grupo 2
 */

#include <fstream>
#include <iostream>
#include <memory>

#include "lexer.hpp"

//Se crea la instancia de las tablas.
Tabla* tabla = Tabla::obtenerInstancia();

void sanitize (char* file) {
  std::ofstream out(file, std::ios::app);

  std::fstream check(file);
  if (check.seekg(-1, std::ios_base::end).get() != '\n') {
    out << "\n\n";
  }

  out.close();
}

int main (int argc, char* argv[]) {
  sanitize(argv[1]);
  std::ifstream file(argv[1]);
  std::istream &entrada(file);
  
  std::shared_ptr<Lexer> lexer(std::make_shared<Lexer>(entrada));
  
  while (true) {
    auto &t = *lexer -> obtenerSiguienteToken();

    if(entrada.peek() == EOF){
      break;
    }

    tabla -> agregarToken(t);
  }
  
  tabla -> imprimeIdentificador();
  tabla -> imprimeCadenaConstante();
  tabla -> imprimeTablaTokens();

  return 0;
}
