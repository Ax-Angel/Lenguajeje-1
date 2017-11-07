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
  },

  // <FUN> -> Va(<LA>)[<LD><BP>]
  // { 't', 'r' }
  { std::pair<Termino, Termino>({ "FUN", false }, { "t", true }),
    { { "V", false }, { "a", true }, { "(", true }, { "LA", false }, { ")", true }, { "[", true }, { "LD", false }, { "BP", false }, { "]", true } }
  },
  { std::pair<Termino, Termino>({ "FUN", false }, { "r", true }),
    { { "V", false }, { "a", true }, { "(", true }, { "LA", false }, { ")", true }, { "[", true }, { "LD", false }, { "BP", false }, { "]", true } }
  },

  // <FUN> -> a(<LA>)[<LD><BP>]
  // { 'a' }
  { std::pair<Termino, Termino>({ "FUN", false }, { "a", true }),
    { { "a", true }, { "(", true }, { "LA", false }, { ")", true }, { "[", true }, { "LD", false }, { "BP", false }, { "]", true } }
  },

  // <LA> -> 3
  // { ')' }
  { std::pair<Termino, Termino>({ "LA", false }, { ")", true }),
    { { ")", true } }
  },

  // <LA> -> Va<LAP>
  { std::pair<Termino, Termino>({ "LA", false }, { "t", true }),
    { { "V", false }, { "a", true }, { "LAP", false } }
  },
  { std::pair<Termino, Termino>({ "LA", false }, { "r", true }),
    { { "V", false }, { "a", true }, { "LAP", false } }
  },

  // <LAP> -> 3
  // { ')' }
  { std::pair<Termino, Termino>({ "LAP", false }, { ")", true }),
    { { "3", true } }
  },

  // <LAP> -> ,Va<LAP>
  // { ',' }
  { std::pair<Termino, Termino>({ "LAP", false }, { ",", true }),
    { { ",", true }, { "V", false }, { "a", true }, { "LAP", false } }
  },

  // <LD> -> 3
  // { ']', '@', 'a', 'w', 'l', 'h', 'm', 'i', '[' }
  { std::pair<Termino, Termino>({ "LD", false }, { "]", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "@", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "a", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "w", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "l", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "h", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "m", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "i", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "[", true }),
    { { "3", true } }
  },
  
  // <LD> -> D<LD>
  // { 't', 'r' }
  { std::pair<Termino, Termino>({ "LD", false }, { "t", true }),
    { { "D", false }, { "LD", false } }
  },
  { std::pair<Termino, Termino>({ "LD", false }, { "r", true }),
    { { "D", false }, { "LD", false } }
  },

  // <D> -> VaCL
  // { 't', 'r' }
  { std::pair<Termino, Termino>({ "D", false }, { "t", true }),
    { { "V", false }, { "a", true }, { "C", false }, { "L", false } }
  },
  { std::pair<Termino, Termino>({ "D", false }, { "r", true }),
    { { "V", false }, { "a", true }, { "C", false }, { "L", false } }
  },

  // V -> t
  // { 't' }
  { std::pair<Termino, Termino>({ "V", false }, { "t", true }),
    { { "t", true } }
  },

  // V -> r
  // { 'r' }
  { std::pair<Termino, Termino>({ "V", false }, { "r", true }),
    { { "r", true } }
  },

  // C -> 3
  // { ',', ';' }
  { std::pair<Termino, Termino>({ "C", false }, { ",", true }),
    { { "3", true } }
  },
  { std::pair<Termino, Termino>({ "C", false }, { ";", true }),
    { { "3", true } }
  },

  // C -> =N
  // { '=' }
  { std::pair<Termino, Termino>({ "C", false }, { "=", true }),
    { { ",", true } }
  },

  // N -> n
  // { 'n' }
  { std::pair<Termino, Termino>({ "N", false }, { "n", true }),
    { { "n", true } }
  },
  
  // N -> c
  // { 'c' }
  { std::pair<Termino, Termino>({ "N", false }, { "c", true }),
    { { "c", true } }
  },

  // L -> ,aCL
  // { ',' }
  { std::pair<Termino, Termino>({ "L", false }, { ",", true }),
    { { ",", true }, { "a", true }, { "C", false }, { "L", false } }
  },

  // L -> ;
  // { ';' }
  { std::pair<Termino, Termino>({ "L", false }, { ";", true }),
    { { ";", true } }
  },

  // <BP> -> 3
  // { ']' }
  { std::pair<Termino, Termino>({ "BP", false }, { "]", true }),
    { { "3", true } }
  },

  // <BP> -> <PR><BP>
  // { '@', 'a', 'w', 'l', 'h', 'm', 'i', '[' }
  { std::pair<Termino, Termino>({ "BP", false }, { "@", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "a", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "w", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "l", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "h", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "m", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "i", true }),
    { { "PR", false }, { "BP", false } }
  },
  { std::pair<Termino, Termino>({ "BP", false }, { "[", true }),
    { { "PR", false }, { "BP", false } }
  },
  
  // <PR> -> S
  // { '@', 'a', 'w', 'l', 'h', 'm', 'i' }
  { std::pair<Termino, Termino>({ "PR", false }, { "@", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "a", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "w", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "l", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "h", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "m", true }),
    { { "S", false } }
  },
  { std::pair<Termino, Termino>({ "PR", false }, { "i", true }),
    { { "S", false } }
  },

  // <PR> -> <PC>
  // { '[' }
  { std::pair<Termino, Termino>({ "PR", false }, { "[", true }),
    { { "PC", false } }
  },

  // S -> A
  // { 'a' }
  { std::pair<Termino, Termino>({ "S", false }, { "a", true }),
    { { "A", false } }
  },

  // S -> W
  // { 'w' }
  { std::pair<Termino, Termino>({ "S", false }, { "w", true }),
    { { "W", false } }
  },

  // S -> R
  // { 'l' }
  { std::pair<Termino, Termino>({ "S", false }, { "l", true }),
    { { "R", false } }
  },

  // S -> H
  // { 'h' }
  { std::pair<Termino, Termino>({ "S", false }, { "h", true }),
    { { "H", false } }
  },

  // S -> M
  // { 'm' }
  { std::pair<Termino, Termino>({ "S", false }, { "m", true }),
    { { "M", false } }
  },

 // S -> I
  // { 'i' }
  { std::pair<Termino, Termino>({ "S", false }, { "i", true }),
    { { "I", false } }
  },

  // S -> @a(<LP>);
  // { '@' }
  { std::pair<Termino, Termino>({ "S", false }, { "@", true }),
    { { "@", true }, { "a", true }, { "(", true }, { "LP", false }, { ")", true } }
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
