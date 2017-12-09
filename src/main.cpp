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
  //int contCadena = 0;
  
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

    std::string funcionActual;
    bool agregarIdFuncion = true;
    int __func = 0;
    
    while (true) {
      auto &t = *L -> obtenerSiguienteToken();
      
      if(E.peek() == EOF){
	     break;
      }

      auto atomo = atomos.front(); atomos.pop();
      
      if (atomo == "t" || atomo == "r") {
	     programaC += (atomo == "t") ? "int" : "float";
	
      	while (true) {
      	  t = *L -> obtenerSiguienteToken();
      	  auto _atomo = atomos.front(); atomos.pop();

      	 if (_atomo == ";") {
      	    programaC += _atomo + "\n";
      	    break;
      	  }

          if ( _atomo == "(" ){
            programaC += _atomo + " ";
            break;
          }
      	  
      	  if (_atomo == ",") {
      	    programaC += ",";
      	    continue;
      	  }

      	  std::string S = L -> id;
      	  tabla -> agregarTipo(S, atomo);
      	  programaC += " " + S;

	  if (agregarIdFuncion) {
	    funcionActual = S;
	    agregarIdFuncion = false;
	  }

	  tabla -> agregarFuncionAsociada(S, funcionActual);
	}
      }
      else if (atomo == "n") {
	programaC += " " + std::to_string((int)t.obtenerValor());
      }
      else if (atomo == "c") {
	programaC += std::to_string(t.obtenerValor()) + "f";
      }
      else if (atomo == "a") {
      	std::string S = L -> id;
      	programaC += " " + S;

	if (agregarIdFuncion) {
	  funcionActual = S;
	  agregarIdFuncion = false;
	}

	tabla -> agregarFuncionAsociada(S, funcionActual);
      }
      else if (atomo == "s") { 
        std::string S = L -> id;
        programaC += S;
      }
      else if (atomo == "[") {
	programaC += "{\n";
	__func++;
      }
      else if (atomo == "]") {
	programaC += "\n}";
	__func--;

	if (__func == 0) {
	  agregarIdFuncion = true;
	}
      }
      else if (atomo == "w") {
        programaC += "printf(";

        while(true){
        t = *L -> obtenerSiguienteToken();
        auto _atomo = atomos.front(); atomos.pop();
        
        if (_atomo == "s") {
            std::string S = L -> id;
            programaC += S;
            continue;
          }

        if (_atomo == "n") {
          programaC += " " + std::to_string((int)t.obtenerValor());
          continue;
        }

        if (_atomo == "c") {
          programaC += std::to_string(t.obtenerValor()) + "f";
          continue;
        }

        if (_atomo == "a") {
          std::string S = L -> id;
          programaC += S;
          continue;
        }

        if (_atomo == ",") {
            programaC += ", ";
            continue;
          }

        if (_atomo == ";") {
            programaC += ");\n";
            break;
          }
        }
       }

      else if (atomo == "l") { 

        programaC += "scanf(\"";
        std::string ident = "";

        while(true){
          t = *L -> obtenerSiguienteToken();
          auto _atomo = atomos.front(); atomos.pop();

          if (_atomo == "a") {
            std::string S = L -> id;
            ident += ", &" + S;
            programaC += "\%d "; 
            continue;
          }

          if (_atomo == ";") {
              programaC += "\"" + ident + ");\n";
              break;
            }

        }
      }
      else if (atomo == "h") { programaC += "do\n"; }
      else if (atomo == "m") { programaC += "while"; }
      else if (atomo == "i") { programaC += "if"; }
      else if (atomo == "e") { programaC += "else\n"; }
      else if (atomo == ";") { programaC += ";\n"; }
      else if (atomo == ",") { programaC += ", "; }
      else if (atomo == "=") { programaC += " ="; }
      else if (atomo == ">") { programaC += " >"; }
      else if (atomo == "<") { programaC += " <"; }
      else if (atomo == "g") { programaC += " >="; }
      else if (atomo == "p") { programaC += " <="; }
      else if (atomo == "q") { programaC += " =="; }
      else if (atomo == "!") { programaC += " !="; }
      else if (atomo == ",") { programaC += " ,"; }
      else if (atomo == "(") { programaC += "("; }
      else if (atomo == ")") { programaC += ")"; }
      else if (atomo == "+") { programaC += " +"; }
      else if (atomo == "-") { programaC += " -"; }
      else if (atomo == "*") { programaC += " *"; }
      else if (atomo == "/") { programaC += " /"; }
      else if (atomo == "@") { }
    }
  }
  
  tabla -> imprimeIdentificador();
  //tabla -> imprimeCadenaConstante();
  //tabla -> imprimeTablaTokens(); solo necesitamos mostrar la tabla de simbolos
  outputCFile(programaC);
  
  return 0;
}
