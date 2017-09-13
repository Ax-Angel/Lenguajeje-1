#include "token.hpp"

Token::Token(int pos, int linea, int col, Clase clase) : pos(pos), linea(linea), col(col), clase(clase) {}

Token::~Token() {}

int Token::obtenerPosicion() const { return pos; }

int Token::obtenerLinea() const { return linea; }

int Token::obtenerColumna() const { return col; }

TokenIdentificador::TokenIdentificador(const std::string &identificador, int pos, int linea, int col, Clase clase) :
  Token(pos, linea, col, clase), identificador(identificador) {}

const std::string &TokenIdentificador::obtenerIdentificador() const {
  return identificador;
}

int TokenIdentificador::obtenerValor() const {
  return 0; // IMPLEMENTAR
}

void TokenIdentificador::aceptar(VisitaToken &t) { t.visita(*this); }

TokenPalabraReservada::TokenPalabraReservada(TipoPalabraReservada palabraReservada, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), palabraReservada(palabraReservada) {}

TipoPalabraReservada TokenPalabraReservada::obtenerPalabraReservada() const {
  return palabraReservada;
}

void TokenPalabraReservada::aceptar(VisitaToken &t) { t.visita(*this); }

TokenAsignacion::TokenAsignacion(int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase) {}

void TokenAsignacion::aceptar(VisitaToken &t) { t.visita(*this); }

TokenOpRelacional::TokenOpRelacional(OperadorRelacional operadorRelacional, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), operadorRelacional(operadorRelacional) {}

OperadorRelacional TokenOpRelacional::obtenerOperadorRelacional() const {
  return operadorRelacional;
}

void TokenOpRelacional::aceptar(VisitaToken &t) { t.visita(*this); }

TokenOpAritmetico::TokenOpAritmetico(OperadorAritmetico operadorAritmetico, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), operadorAritmetico(operadorAritmetico) {}

OperadorAritmetico TokenOpAritmetico::obtenerOperadorAritmetico() const {
  return operadorAritmetico;
}

void TokenOpAritmetico::aceptar(VisitaToken &t) { t.visita(*this); }

TokenSimboloEspecial::TokenSimboloEspecial(int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase) {}

int TokenSimboloEspecial::obtenerValor() const {
  return 0; // IMPLEMENTAR
}

void TokenSimboloEspecial::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteEntero::TokenConstanteEntero(int valorConstanteEntero, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), valorConstanteEntero(valorConstanteEntero) {}

int TokenConstanteEntero::obtenerValor() const {
  return 0; // IMPLEMENTAR
}

int TokenConstanteEntero::obtenerValorConstanteEntero() const {
  return valorConstanteEntero;
}

void TokenConstanteEntero::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteReal::TokenConstanteReal(double valorConstanteReal, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), valorConstanteReal(valorConstanteReal) {}

int TokenConstanteReal::obtenerValor() const {
  return 0; // IMPLEMENTAR
}

double TokenConstanteReal::obtenerValorConstanteReal() const {
  return valorConstanteReal;
}

void TokenConstanteReal::aceptar(VisitaToken &t) { t.visita(*this); }

TokenConstanteCadena::TokenConstanteCadena(std::string cadenaConstante, int pos, int linea, int col, Clase clase) : Token(pos, linea, col, clase), cadenaConstante(cadenaConstante) {}

std::string TokenConstanteCadena::obtenerCadenaConstante() const {
  return cadenaConstante;
}

int TokenConstanteCadena::obtenerValor() const {
  return 0; // IMPLEMENTAR
}

void TokenConstanteCadena::aceptar(VisitaToken &t) { t.visita(*this); }
