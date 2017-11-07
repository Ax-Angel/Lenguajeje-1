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

Tabla::Tabla() {
  // Fin de cadena de átomos.
  atomos.push('^');
}

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


const std::map<Clase, char> Tabla::atomosTipoA = {
  { IDENTIFICADOR, 'a' },
  { OPERADOR_ASIGNACION, '=' },
  { CONSTANTE_ENTERA_B10, 'c' },
  { CONSTANTE_REAL, 'n' },
  { CONSTANTE_CADENA, 's' }
};

const std::map<_Token, char> Tabla::atomosTipoB = {
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_ENT), 't' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_ESCRIBE), 'w' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_HAZ), 'h' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_LEE), 'l' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_MIENTRAS), 'm' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_REAL), 'r' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_SI), 'i' },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_SINO), 'e' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MAYORQUE), '>' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MAYORQUEIGUAL), 'g' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MENORQUE), '<' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MENORQUEIGUAL), 'p' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_ESIGUAL), 'q' },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_ESDISTINTO), '!' },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_DIVISION), '/' },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_SUMA), '+' },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_RESTA), '-' },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_MULTIPLICACION), '*' },
  { _Token(SIMBOLO_ESPECIAL, (int)(',')), ',' },
  { _Token(SIMBOLO_ESPECIAL, (int)(';')), ';' },
  { _Token(SIMBOLO_ESPECIAL, (int)('[')), '[' },
  { _Token(SIMBOLO_ESPECIAL, (int)(']')), ']' },
  { _Token(SIMBOLO_ESPECIAL, (int)('(')), '(' },
  { _Token(SIMBOLO_ESPECIAL, (int)(')')), ')' },
  { _Token(SIMBOLO_ESPECIAL, (int)('@')), '@' },
};
  
void Tabla::agregarToken(Token& token) {
  _Token t = std::make_pair(token.obtenerClase(), token.obtenerValor());
  tablaTokens.push_back(t);

  auto itAtomoA = atomosTipoA.find(t.first);
  auto itAtomoB = atomosTipoB.find(t);
  
  if (itAtomoA != atomosTipoA.end()) {
    atomos.push(itAtomoA->second);
    return;
  }

  if (itAtomoB != atomosTipoB.end()) {
    atomos.push(itAtomoB->second);
    return;
  }

  // Caracterización del error.
  atomos.push('?');
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

std::string Tabla::obtenerCadenaDeAtomos() {
  std::queue<char> q = atomos;
  std::string cadenaDeAtomos;

  while (!q.empty()) {
    cadenaDeAtomos += q.front();
    q.pop();
  }

  return cadenaDeAtomos;
}
