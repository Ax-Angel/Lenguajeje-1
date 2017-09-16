#include <locale>
#include <string>

#include "lexer.hpp"
#include "token.hpp"

Lexer::Lexer(std::istream &entrada) : entrada(entrada) {
  leerCaracter();
}

void Lexer::leerCaracter() {
  if (ultimoCaracter == '\n') {
    lineaActual++;
    columnaActual = 0;
  }
  
  posicionActual++;
  columnaActual++;
  ultimoCaracter = entrada.get();
}

void Lexer::saltarEspacioBlanco() {
  while (isspace(ultimoCaracter)) leerCaracter();

  // Si se encuentra '$$', denota un comentario de línea única.
  // Leer hasta que termine la línea en la que se encuentra.
  if (ultimoCaracter == '$') {
    leerCaracter();
    if (ultimoCaracter == '$') {
      while (ultimoCaracter != '\n') {
	leerCaracter();
      }
      
      saltarEspacioBlanco();
    }
  }
}

ApuntadorAToken Lexer::leerNumero() {
  std::string num = "";
  
  while (isdigit(ultimoCaracter)) {
    std::string ultimoCaracterStr(1, ultimoCaracter);
    num += ultimoCaracterStr;
    leerCaracter();
  }

  if (isspace(ultimoCaracter) || ultimoCaracter == -1) {
    return std::make_shared<TokenConstanteEntero>(posicionActual, lineaActual, columnaActual, std::stoi(num));
  }
  
  if (ultimoCaracter == '.') {
    num += ".";
    leerCaracter();
    while (isdigit(ultimoCaracter)) {
      std::string ultimoCaracterStr(1, ultimoCaracter);
      num += ultimoCaracterStr;
      leerCaracter();
    }
  }
  
  if (!isspace(ultimoCaracter) || ultimoCaracter == -1) {
    std::string ultimoCaracterStr(1, ultimoCaracter);
    std::string mensajeError = "Símbolo no esperado: '";
    mensajeError += ultimoCaracterStr + "', "
      + std::to_string(posicionActual) + ", "
      + std::to_string(lineaActual) + ", "
      + std::to_string(columnaActual) + ".";
    leerCaracter();
    return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
  }

  return std::make_shared<TokenConstanteReal>(posicionActual, lineaActual, columnaActual, std::stod(num));
}

ApuntadorAToken Lexer::leerCadena() {
  
}

ApuntadorAToken Lexer::leerSimboloEspecial() {
  
}

ApuntadorAToken Lexer::obtenerTokenActual() const {
  return tokenActual;
}

void Lexer::descartarToken() {
  obtenerSiguienteToken();
}

ApuntadorAToken Lexer::obtenerSiguienteToken() {
  saltarEspacioBlanco();

  if (entrada.eof()) {
  }

  // El lexema inicia con un número, así, leer como tal
  // y determinar si corresponde a un entero o un real.
  // Puede corresponder a alguna de las siguientes calses:
  //
  // CONSTANTES_ENTERAS_B10
  // CONSTANTES_REALES
  //
  
  if (isdigit(ultimoCaracter)) {
    return tokenActual = leerNumero();
  }

  // El lexema inicia con un caracter, así, leer como tal
  // y determinar si es un identificador, palabra reservada,
  // o una constante de cadena.
  // Puede corresponder a alguna de las siguientes clases:
  //
  // IDENTIFICADOR
  // PALABRA_RESERVADA
  // OPERADOR_ARITMETICO
  //
  
  if (ultimoCaracter == '\"') {
    return tokenActual = leerCadena();
  }

  // El lexema inicia con un símbolo de puntuación de C, así
  // puede corresponder a alguna de las siguientes clases:
  //
  // OPERADOR_ASIGNACION
  // OPERADOR_RELACIONAL
  // SIMBOLO_ESPECIAL
  // CONSTANTE_CADENA
  //
  
  if (ispunct(ultimoCaracter)) {
    return tokenActual = leerSimboloEspecial();
  }

  // El símbolo no corresponde a ninguno especificado por nuestro
  // lenguaje, así, es un error.

  std::string ultimoCaracterStr(1, ultimoCaracter);
  std::string mensajeError = "Símbolo no esperado: '";
  mensajeError += ultimoCaracterStr + "', "
    + std::to_string(posicionActual) + ", "
    + std::to_string(lineaActual) + ", "
    + std::to_string(columnaActual) + ".";
  leerCaracter();
  return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
}
