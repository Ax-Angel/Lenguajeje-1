/*
  Analizador Léxico
  Creado por: Mateo Torres Ruiz y Ángel Rodríguez Mendoza
  Proyecto para la asignatura de Compiladores 2018-1 Grupo 2
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <queue>

#include "lexer.hpp"
#include "parser.hpp"

//Se crea la instancia de las tablas.
Tabla* tabla = Tabla::obtenerInstancia();

void sanitize (char* file) {
  std::ofstream out(file, std::ios::app);

  std::fstream check(file);
  if (check.seekg(-1, std::ios_base::end).get() != '\n') {
    out << "\n\n";
  }

  out << "\n";
  out.close();
}

void closeClean (char *file) {
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

  std::queue<std::string> atomos;
  std::queue<std::string> programa; 
  
  std::cout << "\nCadena de átomos: ";
  auto v = tabla -> obtenerCadenaDeAtomos();
  for (Termino t : v) {
    std::cout << t.identificador << " ";
    atomos.push(t.identificador);
  }
  std::cout << "\n";
  Parser p(v);
  bool _b = p.consumirAtomos(false);

  if (_b) {
    lexer.reset();

    std::ifstream F(argv[1]);
    std::istream &E(F);
    std::shared_ptr<Lexer> L(std::make_shared<Lexer>(E));
    
    while (true) {
      auto &t = *L -> obtenerSiguienteToken();
      
      if(E.peek() == EOF){
	break;
      }

      auto atomo = atomos.front(); atomos.pop();
      
      if (atomo == "t" || atomo == "r") {

	while (true) {
	  t = *L -> obtenerSiguienteToken();
	  auto _atomo = atomos.front(); atomos.pop();
	  if (_atomo == ";" || _atomo == "(") break;
	  if (_atomo == ",") continue;
	  std::string S = L -> id;
	  tabla -> agregarTipo(S, atomo);
	}
      }
    }
  }
  
  tabla -> imprimeIdentificador();
  tabla -> imprimeCadenaConstante();
  tabla -> imprimeTablaTokens();
  
  return 0;
}
