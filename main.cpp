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

int main (int argc, char* argv[]) {
  std::ifstream file(argv[1]);
  std::istream &entrada(file);

  std::shared_ptr<Lexer> lexer(std::make_shared<Lexer>(entrada));
  
  while (!entrada.eof()) {

    auto &t = *lexer -> obtenerSiguienteToken();

    if(entrada.eof()){
      break;
    }

    tabla -> agregarToken(t);

  }

  tabla -> imprimeIdentificador();
  tabla -> imprimeCadenaConstante();
  tabla -> imprimeTablaTokens();

  return 0;
}
