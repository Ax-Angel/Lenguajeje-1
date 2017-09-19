#include "tablas.hpp"
#include <iostream>

Tabla* Tabla::instancia = NULL;

//La función verifica que no existan instancias previas de las tablas.
//En caso de que no las haya, crea una nueva instancia por cada una.

Tabla* Tabla::obtenerInstancia() {
  if (instancia == NULL) {
    instancia = new Tabla();
  }

  return instancia;
}

Tabla::Tabla() {}

//La función primero verifica que la cadena no se encuentre en la tabla de cadenas.
//En caso de que no se encuentre, se agrega
int Tabla::agregarCadenaConstante(std::string cadenaConstante) {
  auto it = Tabla::tablaCadenasConstantes.find(cadenaConstante);

  if (it != Tabla::tablaCadenasConstantes.end()) {
    return it -> second;
  }

  Tabla::tablaCadenasConstantes[cadenaConstante] = ultimaPosicionCadenaConstante++;
  return tablaCadenasConstantes[cadenaConstante];
}

//La función primero verifica que no exista el identificador en la tabla.
//En caso de que no se encuentre, lo agrega.
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

void Tabla::imprimeIdentificador(){
  std::cout << '\n' << "TABLA DE SIMBOLOS\nPosicion\tNombre\tTipo\n";

  for(auto const &i: tablaIdentificadores){
    std::cout << i.second << "\t\t" <<i.first << std::endl;
  }

}

void Tabla::imprimeCadenaConstante(){
  std::cout << '\n' << "TABLA DE CADENAS\nPosicion\tCadena\n";

  for(auto const &i: tablaCadenasConstantes){
    std::cout << i.second << "\t\t" <<i.first << std::endl;
  }


}

void Tabla::imprimeTablaTokens(){
  std::cout << '\n' << "TABLA DE TOKENS\nTOKEN\tVALOR\n";

  for(auto const &i: tablaTokens){
    std::cout << i.first << "\t\t" <<i.second << std::endl;
  }
}