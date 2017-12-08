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
  //atomos.push(Termino({ "^", true }));
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


const std::map<Clase, Termino> Tabla::atomosTipoA = {
  { IDENTIFICADOR, { "a", true } },
  { OPERADOR_ASIGNACION, { "=", true } },
  { CONSTANTE_ENTERA_B10, { "c", true } },
  { CONSTANTE_REAL, { "n", true } },
  { CONSTANTE_CADENA, { "s", true } }
};

const std::map<_Token, Termino> Tabla::atomosTipoB = {
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_ENT), { "t", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_ESCRIBE), { "w", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_HAZ), { "h", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_LEE), { "l", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_MIENTRAS), { "m", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_REAL), { "r", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_SI), { "i", true } },
  { _Token(PALABRA_RESERVADA, PALABRARESERVADA_SINO), { "e", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MAYORQUE), { ">", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MAYORQUEIGUAL), { "g", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MENORQUE), { "<", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_MENORQUEIGUAL), { "p", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_ESIGUAL), { "q", true } },
  { _Token(OPERADOR_RELACIONAL, OPERADORRELACIONAL_ESDISTINTO), { "!", true } },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_DIVISION), { "/", true } },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_SUMA), { "+", true } },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_RESTA), { "-", true } },
  { _Token(OPERADOR_ARITMETICO, OPERADORARITMETICO_MULTIPLICACION), { "*", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)(',')), { ",", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)(';')), { ";", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)('[')), { "[", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)(']')), { "]", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)('(')), { "(", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)(')')), { ")", true } },
  { _Token(SIMBOLO_ESPECIAL, (int)('@')), { "@", true } },
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
  atomos.push(Termino({ "?", true }));
}

void Tabla::imprimeIdentificador(){
  std::cout << '\n' << "TABLA DE SIMBOLOS\nPosicion\tNombre\tTipo\n";

  for(auto const &i: tablaIdentificadores){
    std::cout << i.second << "\t\t" << i.first << "\t" << (tablaTipos.count(i.first) ? tablaTipos[i.first] : "*") << std::endl;
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

std::vector<Termino> Tabla::obtenerCadenaDeAtomos() {
  std::queue<Termino> q = atomos;
  std::vector<Termino> cadenaDeAtomos;

  
  while (!q.empty()) {
    cadenaDeAtomos.push_back(q.front());
    q.pop();
  }

  return cadenaDeAtomos;
}

void Tabla::agregarTipo(std::string s, std::string t) {
  auto it = Tabla::tablaTipos.find(s);

  if (it == Tabla::tablaTipos.end()) {
    Tabla::tablaTipos[s] = (t == "t" ? "ENT" : "REAL");
  }
}

void Tabla::traducirC() {

}
