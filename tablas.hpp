#pragma once

#include <map>
#include <vector>

#include "token.hpp"

enum Tipo {
};

class Tabla {
  std::map<TokenIdentificador, bool> tablaSimbolos;
  std::vector<Token> tablaTokens;
  std::vector<TokenCadena> tablaCadenas;
  
public:
  void agregarSimbolo();
  void agregarToken();
  void agregarCadena();
};
