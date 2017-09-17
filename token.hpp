#pragma once

#include <string>

class VisitaToken;

enum Clase {
  IDENTIFICADOR, // 0
  PALABRA_RESERVADA, // 1
  OPERADOR_ASIGNACION, // 2
  OPERADOR_RELACIONAL, // 3
  OPERADOR_ARITMETICO, // 4
  SIMBOLO_ESPECIAL, // 5
  CONSTANTE_ENTERA_B10, // 6
  CONSTANTE_REAL, // 7
  CONSTANTE_CADENA, // 8
  ERROR, // 9
  FIN_DE_ARCHIVO // 10
};

class Token {
  // Posicion en el archivo donde inicia el token.
  int pos;
  // Linea del archivo donde inicia el token.
  int linea;
  // Columna del archivo donde inicia el token.
  int col;
  // Clase a la que pertenece
  Clase clase;
  // Valor
  double valor;
  
public:
  Token (int pos = 0, int linea = 0, int col = 0, Clase clase = ERROR, double valor = 0);
  virtual ~Token();

  int obtenerPosicion() const;
  int obtenerLinea() const;
  int obtenerColumna() const;
  Clase obtenerClase() const;
  double obtenerValor() const;
  virtual void aceptar(VisitaToken &t) = 0;
};

class TokenIdentificador : public Token {
  // El valor para el token de cada identificador es la posición
  // dentro de la tabla de símbolos.
  
  // Nombre del identificador.
  std::string identificador;
  
public:
  TokenIdentificador(const std::string &identificador, int pos = 0, int linea = 0, int col = 0, Clase clase = IDENTIFICADOR);
  const std::string &obtenerIdentificador() const;
  virtual void aceptar(VisitaToken &t);
};


// Palabras reservadas
enum PalabraReservada {
  PALABRARESERVADA_ENT,
  PALABRARESERVADA_ESCRIBE,
  PALABRARESERVADA_HAZ,
  PALABRARESERVADA_LEE,
  PALABRARESERVADA_MIENTRAS,
  PALABRARESERVADA_REAL,
  PALABRARESERVADA_SI,
  PALABRARESERVADA_SINO
};

class TokenPalabraReservada : public Token {
  PalabraReservada palabraReservada;

public:
  TokenPalabraReservada(PalabraReservada palabraReservada, int pos = 0, int linea = 0, int col = 0, Clase clase = PALABRA_RESERVADA);
  PalabraReservada obtenerPalabraReservada() const;
  virtual void aceptar(VisitaToken &t);
};

class TokenAsignacion : public Token {
  // Para esta clase, el valor del token, es el valor del
  // caracter '=' en ASCii.

public:
  TokenAsignacion(int pos = 0, int linea = 0, int col = 0, Clase clase = OPERADOR_ASIGNACION, int valor = '=');
  virtual void aceptar(VisitaToken &t);
};

enum OperadorRelacional {
  OPERADORRELACIONAL_MAYORQUE,
  OPERADORRELACIONAL_MAYORQUEIGUAL,
  OPERADORRELACIONAL_MENORQUE,
  OPERADORRELACIONAL_MENORQUEIGUAL,
  OPERADORRELACIONAL_ESIGUAL,
  OPERADORRELACIONAL_ESDISTINTO
};

class TokenOpRelacional : public Token {
  OperadorRelacional operadorRelacional;

public:
  TokenOpRelacional(OperadorRelacional operadorRelacional, int pos = 0, int linea = 0, int col = 0, Clase clase = OPERADOR_RELACIONAL);
  OperadorRelacional obtenerOperadorRelacional() const;
  virtual void aceptar(VisitaToken &t);
};

enum OperadorAritmetico {
  OPERADORARITMETICO_DIVISION,
  OPERADORARITMETICO_SUMA,
  OPERADORARITMETICO_RESTA,
  OPERADORARITMETICO_MULTIPLICACION
};

class TokenOpAritmetico : public Token {
  OperadorAritmetico operadorAritmetico;

public:
  TokenOpAritmetico(OperadorAritmetico operadorAritmetico, int pos = 0, int linea = 0, int col = 0, Clase clase = OPERADOR_ARITMETICO);
  OperadorAritmetico obtenerOperadorAritmetico() const;
  virtual void aceptar(VisitaToken &t);
};

class TokenSimboloEspecial : public Token {
  // Para esta clase, el valor del token, es el valor del
  // caracter '=' en ASCii.

public:
  TokenSimboloEspecial(int pos = 0, int linea = 0, int col = 0, int valor = 0);
  virtual void aceptar(VisitaToken &t);
};

class TokenConstanteEntero : public Token {
  
public:
  TokenConstanteEntero(int pos = 0, int linea = 0, int col = 0, int valor = 0);
  virtual void aceptar(VisitaToken &t);
};

class TokenConstanteReal : public Token {

public:
  TokenConstanteReal(int pos = 0, int linea = 0, int col = 0, double valor = 0.0);
  virtual void aceptar(VisitaToken &t);
};

class TokenConstanteCadena : public Token {
  std::string cadenaConstante;

public:
  TokenConstanteCadena(std::string cadenaConstante, int pos = 0, int linea = 0, int col = 0, Clase clase = CONSTANTE_CADENA);
  std::string obtenerCadenaConstante() const;
  virtual void aceptar(VisitaToken &t);
};

enum Error {
  SIMBOLO
};

class TokenError : public Token {
  Error tipoDeError;
  std::string mensajeError;
  
  public:
  TokenError(std::string mensajeError, int pos = 0, int linea = 0, int col = 0, Clase clase = ERROR);
  virtual void aceptar(VisitaToken &t);
};

class VisitaToken {
public:
  void visitaToken(Token &t);
  virtual void visita(TokenIdentificador &t) = 0;
  virtual void visita(TokenPalabraReservada &t) = 0;
  virtual void visita(TokenAsignacion &t) = 0;
  virtual void visita(TokenOpRelacional &t) = 0;
  virtual void visita(TokenOpAritmetico &t) = 0;
  virtual void visita(TokenSimboloEspecial &t) = 0;
  virtual void visita(TokenConstanteEntero &t) = 0;
  virtual void visita(TokenConstanteReal &t) = 0;
  virtual void visita(TokenConstanteCadena &t) = 0;
  virtual void visita(TokenError &t) = 0; 
};
