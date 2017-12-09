/*
  Analizador Léxico
  Creado por: Mateo Torres Ruiz y Ángel Rodríguez Mendoza
  Proyecto para la asignatura de Compiladores 2018-1 Grupo 2
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <string>

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

void closeClean (char *file) { }

void outputCFile (std::string s) {
  std::ofstream cFile;
  cFile.open("a.c");
  cFile << s << "\n";
  cFile.close();
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
  std::string programaC; 
  
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
	programaC += (atomo == "t") ? "int " : "float ";
	
	while (true) {
	  t = *L -> obtenerSiguienteToken();
	  auto _atomo = atomos.front(); atomos.pop();

	  if (_atomo == ";" || _atomo == "(") {
	    programaC += _atomo + " ";
	    break;
	  }
	  
	  if (_atomo == ",") {
	    programaC += ", ";
	    continue;
	  }

	  std::string S = L -> id;
	  tabla -> agregarTipo(S, atomo);
	  programaC += S + " ";
	}
      }
      else if (atomo == "n") {
	programaC += std::to_string((int)t.obtenerValor()) + " ";
      }
      else if (atomo == "c") {
	programaC += std::to_string(t.obtenerValor()) + "f ";
      }
      else if (atomo == "a") {
	std::string S = L -> id;
	programaC += S + " ";
      }
      else if (atomo == "s") { }
      else if (atomo == "[") {
	programaC += "{ ";
      }
      else if (atomo == "]") {
	programaC += "} ";
      }
      else if (atomo == "w") { }
      else if (atomo == "l") { }
      else if (atomo == "h") { }
      else if (atomo == "m") { }
      else if (atomo == "i") { }
      else if (atomo == "e") { }
      else if (atomo == ">") { programaC += "> "; }
      else if (atomo == "<") { programaC += "< "; }
      else if (atomo == "g") { programaC += ">= "; }
      else if (atomo == "p") { programaC += "<= "; }
      else if (atomo == "q") { programaC += "== "; }
      else if (atomo == "!") { programaC += "!= "; }
      else if (atomo == ",") { programaC += ", "; }
      else if (atomo == ";") { programaC += "; "; }
      else if (atomo == "(") { programaC += "( "; }
      else if (atomo == ")") { programaC += ") "; }
      else if (atomo == "@") { }
    }
  }
  
  tabla -> imprimeIdentificador();
  tabla -> imprimeCadenaConstante();
  tabla -> imprimeTablaTokens();
  outputCFile(programaC);
  
  return 0;
}
