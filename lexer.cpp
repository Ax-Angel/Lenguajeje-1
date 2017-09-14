#include <locale>
#include <string>

#include "lexer.hpp"
#include "token.hpp"

Lexer::Lexer(std::istream &entrada) : entrada(entrada) {
  leerCaracter();
  obtenerSiguienteToken();
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
    // Implementar token EOF.
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
  
  if (ischar(ultimoCaracter)) {
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

  std::string mensajeError = "Símbolo no esperado: '";
  mensaje += ultimoCaracter + "', "
    + posicionActual + ", "
    + lineaActual + ", "
    + columnaActual ".";
  leerCaracter();
  return std::make_shared<
}
