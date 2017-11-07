#ifndef TABLAS_H
#define TABLAS_H

#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "token.hpp"
#include "parser.hpp"

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
  // Átomos que provienen de clases que pueden parsearse de una única forma.
  static const std::map<Clase, Termino> atomosTipoA;
  // Átomos que provienen de clases que pueden parsearse de diversas formas.
  static const std::map<_Token, Termino> atomosTipoB;
  std::queue<Termino> atomos;
  
public:
  static Tabla* obtenerInstancia();
  
  int agregarCadenaConstante(std::string cadenaConstante);
  int agregarIdentificador(std::string identificador);
  void agregarToken(Token& token);
  void imprimeIdentificador();
  void imprimeCadenaConstante();
  void imprimeTablaTokens();
  std::vector<Termino> obtenerCadenaDeAtomos();
};

#endif
