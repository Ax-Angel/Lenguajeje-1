#include "tablas.hpp"

Tabla* Tabla::instancia = NULL;

Tabla* Tabla::obtenerInstancia() {
  if (instancia == NULL) {
    instancia = new Tabla();
  }

  return instancia;
}

Tabla::Tabla() {}

int Tabla::agregarCadenaConstante(std::string cadenaConstante) {
  auto it = Tabla::tablaCadenasConstantes.find(cadenaConstante);

  if (it != Tabla::tablaCadenasConstantes.end()) {
    return it -> second;
  }

  Tabla::tablaCadenasConstantes[cadenaConstante] = ultimaPosicionCadenaConstante++;
  return tablaCadenasConstantes[cadenaConstante];
}

int Tabla::agregarIdentificador(std::string identificador) {
  auto it = Tabla::tablaIdentificadores.find(identificador);

  if (it != Tabla::tablaIdentificadores.end()) {
    return it -> second;
  }

  Tabla::tablaIdentificadores[identificador] = ultimaPosicionIdentificador++;
  return tablaIdentificadores[identificador];
}


void Tabla::agregarToken(Token& token) {
  tablaTokens.push_back(std::make_pair(token.obtenerClase(), token.obtenerValor()));
}
