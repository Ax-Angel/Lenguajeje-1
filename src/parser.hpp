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

static const std::map<std::pair<Termino, Termino>, std::vector<Termino>> reglasDeProduccion = {
  // P -> <LF>
  // { '^', 't', 'r', 'a' }
  { std::pair<Termino, Termino>({ "P", false }, { "^", true }),
    { { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "P", false }, { "t", true }),
    { { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "P", false }, { "r", true }),
    { { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "P", false }, { "a", true }),
    { { "LF", false } }
  },

  // LF -> 3
  // { '^' }
  { std::pair<Termino, Termino>({ "LF", false }, { "3", true }),
    { { "^", true } }
  },

  // <LF> -> <FUN><LF>
  // { 't', 'r', 'a' }
  { std::pair<Termino, Termino>({ "LF", false }, { "t", true }),
    { { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "LF", false }, { "r", true }),
    { { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "LF", false }, { "a", true }),
    { { "FUN", false }, { "LF", false } }
  }
};


class Parser {
private:

  std::string &cadenaDeAtomos;
  std::stack<std::string> consumir;
  
public:
  Parser(std::string &cadenaDeAtomos);  
};

#endif
