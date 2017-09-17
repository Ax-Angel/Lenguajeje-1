#ifndef TABLAS_H
#define TABLAS_H

#include <map>
#include <memory>
#include <vector>

#include "token.hpp"

using ApuntadorAToken = std::shared_ptr<Token>;
using _Token = std::pair<Clase, int>;

class Tabla {
private:
  static Tabla* instancia;
  Tabla();

  int ultimaPosicionCadenaConstante = 0;
  int ultimaPosicionIdentificador = 0;

  std::vector<_Token> tablaTokens;
  std::map<std::string, int> tablaCadenasConstantes;
  std::map<std::string, int> tablaIdentificadores;
  
public:
  static Tabla* obtenerInstancia();

  int agregarCadenaConstante(std::string cadenaConstante);
  int agregarIdentificador(std::string identificador);
  void agregarToken(Token& token);
};

#endif
