#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>

#include "token.hpp"
#include <memory>

using ApuntadorAToken = std::shared_ptr<Token>;

class Lexer {
  // Stream de entrada.
  std::istream &entrada;

  ApuntadorAToken tokenActual;

  // Ultimo caracter leido.
  char ultimoCaracter;

  // Posicion actual del stream.
  int posicionActual;

  // Linea en la que se encuentra el stream.
  int lineaActual;

  // Columna en la que se encuentra el stream.
  int columnaActual;

  void leerCaracter();

  void saltarEspacioBlanco();

  ApuntadorAToken leerNumero();

  ApuntadorAToken leerCadena();

  ApuntadorAToken leerSimboloEspecial();
  
public:
  Lexer(std::istream &entrada = std::cin);

  ApuntadorAToken obtenerTokenActual() const;

  void descartarToken();

  ApuntadorAToken obtenerSiguienteToken();
};
