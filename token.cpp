#include "token.hpp"

Token::Token(int pos, int linea, int col, Clase clase, double valor) : pos(pos), linea(linea), col(col), clase(clase), valor(valor) {}

Token::~Token() {}

int Token::obtenerPosicion() const { return pos; }

int Token::obtenerLinea() const { return linea; }

int Token::obtenerColumna() const { return col; }

Clase Token::obtenerClase() const { return clase; }

double Token::obtenerValor() const { return valor; }

TokenIdentificador::TokenIdentificador(const std::string &identificador, int pos, int linea, int col, Clase clase) :
  Token(pos, linea, col, clase), identificador(identificador) {}

const std::string &TokenIdentificador::obtenerIdentificador() const {
  return identificador;
}

void TokenIdentificador::aceptar(VisitaToken &t) { t.visita(*this); }

TokenPalabraReservada::TokenPalabraReservada(PalabraReservada palabraReservada, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase, (int)palabraReservada), palabraReservada(palabraReservada) {}

PalabraReservada TokenPalabraReservada::obtenerPalabraReservada() const {
  return palabraReservada;
}

void TokenPalabraReservada::aceptar(VisitaToken &t) { t.visita(*this); }

TokenAsignacion::TokenAsignacion(int pos, int linea, int col, Clase clase, int valor) : Token(pos, linea, col, clase, valor) {}

void TokenAsignacion::aceptar(VisitaToken &t) { t.visita(*this); }

TokenOpRelacional::TokenOpRelacional(OperadorRelacional operadorRelacional, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase, (int)operadorRelacional), operadorRelacional(operadorRelacional) {}

OperadorRelacional TokenOpRelacional::obtenerOperadorRelacional() const {
  return operadorRelacional;
}

void TokenOpRelacional::aceptar(VisitaToken &t) { t.visita(*this); }

TokenOpAritmetico::TokenOpAritmetico(OperadorAritmetico operadorAritmetico, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase, (int)operadorAritmetico), operadorAritmetico(operadorAritmetico) {}

OperadorAritmetico TokenOpAritmetico::obtenerOperadorAritmetico() const {
  return operadorAritmetico;
}

void TokenOpAritmetico::aceptar(VisitaToken &t) { t.visita(*this); }

TokenSimboloEspecial::TokenSimboloEspecial(int pos, int linea, int col, int valor) : Token(pos, linea, col, SIMBOLO_ESPECIAL, valor) {}

void TokenSimboloEspecial::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteEntero::TokenConstanteEntero(int pos, int linea, int col, int valor) : Token(pos, linea, col, CONSTANTE_ENTERA_B10, valor) {}

void TokenConstanteEntero::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteReal::TokenConstanteReal(int pos, int linea, int col, double valor) : Token(pos, linea, col, CONSTANTE_REAL, valor) {}

void TokenConstanteReal::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteCadena::TokenConstanteCadena(std::string cadenaConstante, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), cadenaConstante(cadenaConstante) {}

std::string TokenConstanteCadena::obtenerCadenaConstante() const {
  return cadenaConstante;
}

void TokenConstanteCadena::aceptar(VisitaToken &t) { t.visita(*this); }

TokenError::TokenError(std::string mensajeError, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), mensajeError(mensajeError) {} 

void TokenError::aceptar(VisitaToken &t) { t.visita(*this); }
