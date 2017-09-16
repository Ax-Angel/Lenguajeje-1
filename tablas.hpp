#pragma once

#include <map>
#include <memory>
#include <vector>

#include "token.hpp"

using ApuntadorAToken = std::shared_ptr<Token>;

enum Tipo {
};

class Tabla {
  std::map<TokenIdentificador, bool> tablaSimbolos;
  std::vector<Token> tablaTokens;
  std::vector<TokenConstanteCadena> tablaCadenas;
  
public:
  Tabla ();
  
  void agregarToken(ApuntadorAToken token);
};
