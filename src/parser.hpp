#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <stack>
#include <vector>

struct Termino {
  std::string identificador;
  bool terminal;

  bool operator==(const Termino &o) const {
    return identificador == o.identificador && terminal == o.terminal;
  }

  bool operator<(const Termino &o) const {
    return identificador < o.identificador;
  }
};

class Parser {
private:
  std::vector<Termino> &cadenaDeAtomos;
  std::stack<Termino> consumir;
  static const std::map<std::pair<Termino, Termino>, std::vector<Termino>> reglasDeProduccion;
  
public:
  Parser(std::vector<Termino> &cadenaDeAtomos);
  bool consumirAtomos();
};

#endif
