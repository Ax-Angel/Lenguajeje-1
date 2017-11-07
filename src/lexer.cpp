#include <locale>
#include <string>

#include "lexer.hpp"
#include "tablas.hpp"
#include "token.hpp"

Lexer::Lexer(std::istream &entrada) : entrada(entrada) {
  leerCaracter();
}

//Esta función lee caracter por caracter. Ese caracter se guarda en la variable ultimoCaracter

void Lexer::leerCaracter() {
  if (ultimoCaracter == '\n') {
    lineaActual++;
    columnaActual = 0;
  }
  
  posicionActual++;
  columnaActual++;
  ultimoCaracter = entrada.get();
}

void Lexer::saltarEspacioBlanco() {
  while (isspace(ultimoCaracter)) leerCaracter();

  // Si se encuentra '$$', denota un comentario de línea única.
  // Leer hasta que termine la línea en la que se encuentra.
  if (ultimoCaracter == '$') {
    leerCaracter();
    if (ultimoCaracter == '$') {
      while (ultimoCaracter != '\n') {
	leerCaracter();
      }
      
      saltarEspacioBlanco();
    }
  }
}

ApuntadorAToken Lexer::leerNumero() {
  std::string num = "";
  //Se verifica caracter por caracter que se trate de un digito.
  while (isdigit(ultimoCaracter)) {
    std::string ultimoCaracterStr(1, ultimoCaracter);
    num += ultimoCaracterStr;
    leerCaracter();
  }

  //En caso de que a el digito tenga como sucesor un espacio en blanco, se reconoce como un entero. 
  if (isspace(ultimoCaracter) || ultimoCaracter == -1) {
    return std::make_shared<TokenConstanteEntero>(posicionActual, lineaActual, columnaActual, std::stoi(num));
  }


  //Si reconoce un punto entre los digitos, se reconoce como un real
  if (ultimoCaracter == '.') {
    num += ".";
    leerCaracter();
    while (isdigit(ultimoCaracter)) {
      std::string ultimoCaracterStr(1, ultimoCaracter);
      num += ultimoCaracterStr;
      leerCaracter();
    }
  }

  return std::make_shared<TokenConstanteReal>(posicionActual, lineaActual, columnaActual, std::stod(num));
}

ApuntadorAToken Lexer::leerCadena() {
  std::string cadena = "\"";
  //La función guarda todos los caracteres hasta que se encuentre con '"' 
  leerCaracter();
  
  while (ultimoCaracter != '"') {
    cadena += ultimoCaracter;
    leerCaracter();
  }

  cadena += '"';
  leerCaracter();

  return std::make_shared<TokenConstanteCadena>(cadena, posicionActual, lineaActual, columnaActual, tabla->agregarCadenaConstante(cadena));
}

const std::map<std::string, OperadorRelacional> Lexer::operadorRelacional = {
  { ">", OPERADORRELACIONAL_MAYORQUE },
  { ">=", OPERADORRELACIONAL_MAYORQUEIGUAL },
  { "<", OPERADORRELACIONAL_MENORQUE },
  { "<=", OPERADORRELACIONAL_MENORQUEIGUAL },
  { "==", OPERADORRELACIONAL_ESIGUAL },
  { "!=", OPERADORRELACIONAL_ESDISTINTO }
};

const std::map<std::string, int> Lexer::simboloEspecial = {
  { ",", int(',') },
  { ";", int(';') },
  { "[", int('[') },
  { "]", int(']') },
  { "(", int('(') },
  { ")", int(')') }
};

ApuntadorAToken Lexer::leerSimboloEspecial() {
  std::string simbolo(1, ultimoCaracter);
  leerCaracter();
  auto itSimboloEspecial = Lexer::simboloEspecial.find(simbolo);
  auto itOperadorRelacional = Lexer::operadorRelacional.find(simbolo);
  
  //
  // El componente léxico encontrado es un símbolo especial:
  // , ; [ ] ( )
  //

  if (itSimboloEspecial != Lexer::simboloEspecial.end()) {
    return std::make_shared<TokenSimboloEspecial>(posicionActual, lineaActual, columnaActual, itSimboloEspecial->second);
  }
  
  //
  // El componente léxico encontrado es uno de los siguientes:
  // < > =
  // seguido de un caracter no correspondiente a un símbolo de puntuación
  //
  
  if (!ispunct(ultimoCaracter)) {

    //
    // Asignación
    //
    
    if (simbolo == "=") {
      return std::make_shared<TokenAsignacion>(posicionActual, lineaActual, columnaActual);
    }

    //
    // Operador relacional de un único caracter
    //
    
    if (itOperadorRelacional != Lexer::operadorRelacional.end()) {
      return std::make_shared<TokenOpRelacional>(itOperadorRelacional->second, posicionActual, lineaActual, columnaActual);
    }
    
    std::string mensajeError = "Error en operador o símbolo especial: '";
    mensajeError += simbolo + "', "
      + std::to_string(posicionActual) + ", "
      + std::to_string(lineaActual) + ", "
      + std::to_string(columnaActual) + ". El operador o símbolo especial no se encontró.\n";
    
    return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
  }
  
  simbolo += ultimoCaracter;

  //
  // El componente léxico está compuesto por dos símbolos de
  // puntuación continuos, se aceptarán inmediatamente:
  // >=, <=, ==, !=
  //
  
  auto itOperadorRelacionalDos = Lexer::operadorRelacional.find(simbolo);
  if (itOperadorRelacionalDos != Lexer::operadorRelacional.end()) {
    leerCaracter();
    return std::make_shared<TokenOpRelacional>(itOperadorRelacionalDos->second, posicionActual, lineaActual, columnaActual);
  }

  //
  // El componente léxico está compuesto por un operador relacional de
  // caracter único, seguido por un símbolo especial:
  // =, =; =[ =] =( =) >, >; >[ >] >( >) <, <; <[ <] <( <)
  // Agregar el operador relacional a las tablas.

  if (itOperadorRelacional != Lexer::operadorRelacional.end()) {
    return std::make_shared<TokenOpRelacional>(itOperadorRelacional->second, posicionActual, lineaActual, columnaActual);
  }
  else if (simbolo[0] == '=') {
    return std::make_shared<TokenAsignacion>(posicionActual, lineaActual, columnaActual);
  }

  // El operador o símbolo especial no se encontró. Regresar error.
  
  std::string mensajeError = "Error en operador o símbolo especial: '";
  mensajeError += simbolo[0] + "', "
    + std::to_string(posicionActual) + ", "
    + std::to_string(lineaActual) + ", "
    + std::to_string(columnaActual) + ". El operador o símbolo especial no se encontró.\n";

  return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
}

ApuntadorAToken Lexer::leerIdentificador() {
  std::string identificador = "";

  while (islower(ultimoCaracter)) {
    identificador += ultimoCaracter;
    leerCaracter();
  }
  
  return std::make_shared<TokenIdentificador>(identificador, posicionActual, lineaActual, columnaActual, tabla->agregarIdentificador(identificador));
}

const std::map<std::string, OperadorAritmetico> Lexer::operadorAritmetico = {
  { "DIVIDE", OPERADORARITMETICO_DIVISION },
  { "MAS", OPERADORARITMETICO_SUMA },
  { "MENOS", OPERADORARITMETICO_RESTA },
  { "MULTIPLICA", OPERADORARITMETICO_MULTIPLICACION }
};

const std::map<std::string, PalabraReservada> Lexer::palabraReservada = {
  { "ENT", PALABRARESERVADA_ENT },
  { "ESCRIBE", PALABRARESERVADA_ESCRIBE },
  { "HAZ", PALABRARESERVADA_HAZ },
  { "LEE", PALABRARESERVADA_LEE },
  { "MIENTRAS", PALABRARESERVADA_MIENTRAS },
  { "REAL", PALABRARESERVADA_REAL },
  { "SI", PALABRARESERVADA_SI },
  { "SINO", PALABRARESERVADA_SINO }
};

ApuntadorAToken Lexer::leerPalabraReservada() {
  std::string palabra = "";

  //El lexema se reconoce cuando el ultimo caracter es una letra mayuscula.
  //Cuando se termina de leer la palabra, se compara si pertenece a las palabras reservadas
  //o  los operadores aritméticos. Si no coincide con ninguna de las dos clases, se genera un error

  while (isupper(ultimoCaracter)) {
    palabra += ultimoCaracter;
    leerCaracter();
  }

  auto itOperadorAritmetico = Lexer::operadorAritmetico.find(palabra);
  auto itPalabraReservada = Lexer::palabraReservada.find(palabra);
  
  if (itOperadorAritmetico != Lexer::operadorAritmetico.end()) {
    return std::make_shared<TokenOpAritmetico>(itOperadorAritmetico->second, posicionActual, lineaActual, columnaActual);
  }
  
  if (itPalabraReservada != Lexer::palabraReservada.end()) {
    return std::make_shared<TokenPalabraReservada>(itPalabraReservada->second, posicionActual, lineaActual, columnaActual);
  }

  std::string ultimoCaracterStr(1, ultimoCaracter);
  std::string mensajeError = "La siguiente palabra reservada u operación no se encontró: '";
  mensajeError += palabra + "', "
    + std::to_string(posicionActual) + ", "
    + std::to_string(lineaActual) + ", "
    + std::to_string(columnaActual) + "."
    + "\n";
  leerCaracter();
  return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
}

ApuntadorAToken Lexer::obtenerTokenActual() const {
  return tokenActual;
}

void Lexer::descartarToken() {
  obtenerSiguienteToken();
}

ApuntadorAToken Lexer::obtenerSiguienteToken() {
  saltarEspacioBlanco();

  if (entrada.eof()) {
    return 0;
  }

  // El lexema inicia con un número, así, leer como tal
  // y determinar si corresponde a un entero o un real.
  // Puede corresponder a alguna de las siguientes calses:
  //
  // CONSTANTES_ENTERAS_B10
  // CONSTANTES_REALES
  //
  
  if (isdigit(ultimoCaracter)) {
    return tokenActual = leerNumero();
  }

  // El lexema inicia con un '"', así, leer como
  // constante de tipo cadena.
  // Puede corresponder a alguna de las siguientes clases:
  //
  // CONSTANTE_CADENA
  //
  
  if (ultimoCaracter == '"') {
    return tokenActual = leerCadena();
  }

  // El lexema inicia con un símbolo de puntuación de C, así
  // puede corresponder a alguna de las siguientes clases:
  //
  // OPERADOR_ASIGNACION
  // OPERADOR_RELACIONAL
  // SIMBOLO_ESPECIAL
  //
  
  if (ispunct(ultimoCaracter)) {
    return tokenActual = leerSimboloEspecial();
  }

  if (islower(ultimoCaracter)) {
    return tokenActual = leerIdentificador();
  }
  
  if (isupper(ultimoCaracter)) {
    return tokenActual = leerPalabraReservada();
  }
  
  // El símbolo no corresponde a ninguno especificado por nuestro
  // lenguaje, así, es un error.

  std::string ultimoCaracterStr(1, ultimoCaracter);
  std::string mensajeError = "Símbolo no esperado: '";
  mensajeError += ultimoCaracterStr + "', "
    + std::to_string(posicionActual) + ", "
    + std::to_string(lineaActual) + ", "
    + std::to_string(columnaActual) + ".";
  leerCaracter();
  return std::make_shared<TokenError>(mensajeError, posicionActual, lineaActual, columnaActual);
}
