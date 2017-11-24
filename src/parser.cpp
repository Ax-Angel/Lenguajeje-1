#include "parser.hpp"
#include <iostream>

const std::map<std::pair<Termino, Termino>, std::vector<Termino>> Parser::reglasDeProduccion = {
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
  { std::pair<Termino, Termino>({ "LF", false }, { "^", true }),
    { { "3", true } }
  },
  
  // <LF> -> <FUN><LF>
  // { 't', 'r', 'a' }
  { std::pair<Termino, Termino>({ "LF", false }, { "t", true }),
    { { "FUN", false }, { "LF", false } }
  },
  { std::pair<Termino, Termino>({ "LF", false }, { "r", true }),
    { { "FUN", false }, { "LF", false } }
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
    { { "3", true } }
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
  },

  // <PC> -> [<BP>]
  // {'['}
  { std::pair<Termino, Termino>({ "PC", false }, { "[", true }),
    { {"[", true}, { "BP", false }, {"]", true} }
  },

  // A -> a=E
  // {'a'}
  { std::pair<Termino, Termino>({ "A", false }, { "a", true }),
    { { "a", true }, {"=", true}, {"E", false}, {";", true } }
  },

  // W -> wW'
  // {'w'}
  { std::pair<Termino, Termino>({ "W", false }, { "w", true }),
    { { "w", true }, {"W'", false} }
  },

  //W' -> aW''
  // {"a"}
  { std::pair<Termino, Termino>({ "W'", false }, { "a", true }),
    { { "a", true }, {"W''", false} }
  },

  //W' -> cW''
  // {"c"}
  { std::pair<Termino, Termino>({ "W'", false }, { "c", true }),
    { { "c", true }, {"W''", false} }
  },

  //W' -> nW''
  //{"n"}
  { std::pair<Termino, Termino>({ "W'", false }, { "n", true }),
    { { "n", true }, {"W''", false} }
  },

  //W' -> sW''
  //{"s"}
  { std::pair<Termino, Termino>({ "W'", false }, { "s", true }),
    { { "s", true }, {"W''", false} }
  },

  //W'' -> ,W'
  //{","}
  { std::pair<Termino, Termino>({ "W''", false }, { ",", true }),
    { { ",", true }, {"W'", false} }
  },

  //W'' -> ;
  //{";"}
  { std::pair<Termino, Termino>({ "W''", false }, { ";", true }),
    { { ";", true } }
  },

  //R -> laR'
  //{"l"}
  { std::pair<Termino, Termino>({ "R", false }, { "l", false }),
    { { "l", true }, {"a", true}, {"R'", false} }
  },

  //R' -> ,aR'
  //{","}
  { std::pair<Termino, Termino>({ "R'", false }, { ",", true }),
    { { ",", true }, {"a", true}, {"R'", false} }
  },

  //R' -> ;
  //{";"}
  { std::pair<Termino, Termino>({ "R'", false }, { ";", true }),
    { { ";", true } }
  },

  //H -> h[<BP>]m(<REL>);
  //{"h"}
  { std::pair<Termino, Termino>({ "H", false }, { "h", true }),
    { { "h", true }, {"[", true }, {"BP", false}, { "]", true }, {"m", true}, {"(", true}, {"REL", false}, {")", true}, { ";", true } }
  },

  //M -> m(<REL>)<PR>;
  //{"m"}
  { std::pair<Termino, Termino>({ "M", false }, { "m", true }),
    { { "m", true }, {"(", true}, {"REL", false}, {")", true}, {"PR", false}, { ";", true } }
  },
  
  // I -> i(<REL>)<PR>e<PR>
  //{"i"}
  { std::pair<Termino, Termino>({ "I", false }, { "i", true }),
    { { "i", true }, {"(", true }, { "REL", false}, { ")", true }, { "PR", false}, { "e", true }, { "PR", false } }
  },
  /*
  { std::pair<Termino, Termino>({ "I", false }, { "e", true }),
    { { "e", true }, { "(", true }, { "REL", false}, { ")", true }, { "PR", false} }
  },
  { std::pair<Termino, Termino>({ "I", false }, { "]", true }),
    { { "3", true } }
    },*/
  

  //<REL> -> E<OR>E
  //{"(", "a", "n", "c", "@"}
  { std::pair<Termino, Termino>({ "REL", false }, { "(", true }),
    { { "E", false }, {"OR", false}, {"E", false} }
  },
  { std::pair<Termino, Termino>({ "REL", false }, { "a", true }),
    { { "E", false }, {"OR", false}, {"E", false} }
  },
  { std::pair<Termino, Termino>({ "REL", false }, { "n", true }),
    { { "E", false }, {"OR", false}, {"E", false} }
  },
  { std::pair<Termino, Termino>({ "REL", false }, { "c", true }),
    { { "E", false }, {"OR", false}, {"E", false} }
  },
  { std::pair<Termino, Termino>({ "REL", false }, { "@", true }),
    { { "E", false }, {"OR", false}, {"E", false} }
  },

  //<OR> -> >
  //{">"}
  { std::pair<Termino, Termino>({ "OR", false }, { ">", true }),
    { { ">", true } }
  },

  //<OR> -> g
  //{"g"}
  { std::pair<Termino, Termino>({ "OR", false }, { "g", true }),
    { { "g", true } }
  },

  //<OR> -> <
  //{"<"}
  { std::pair<Termino, Termino>({ "OR", false }, { "<", true }),
    { { "<", true } }
  },

  //<OR> -> p
  //{"p"}
  { std::pair<Termino, Termino>({ "OR", false }, { "p", true }),
    { { "p", true } }
  },

  //<OR> -> q
  //{"q"}
  { std::pair<Termino, Termino>({ "OR", false }, { "q", true }),
    { { "q", true } }
  },

  //<OR> -> !
  //{"!"}
  { std::pair<Termino, Termino>({ "OR", false }, { "!", true }),
    { { "!", true } }
  },

  //<LP> -> E<LPA>
  //{"(", "a", "n", "c", "@"}
  { std::pair<Termino, Termino>({ "LP", false }, { "(", true }),
    { { "E", true }, {"LPA", false} }
  },
  { std::pair<Termino, Termino>({ "LP", false }, { "a", true }),
    { { "E", true }, {"LPA", false} }
  },
  { std::pair<Termino, Termino>({ "LP", false }, { "n", true }),
    { { "E", true }, {"LPA", false} }
  },
  { std::pair<Termino, Termino>({ "LP", false }, { "c", true }),
    { { "E", true }, {"LPA", false} }
  },
  { std::pair<Termino, Termino>({ "LP", false }, { "@", true }),
    { { "E", true }, {"LPA", false} }
  },

  //<LP> -> 3
  //{")"}
  { std::pair<Termino, Termino>({ "LP", false }, { ")", true }),
    { { "3", true } }
  },

  //<LPA> -> 3
  //{")"}
  { std::pair<Termino, Termino>({ "LPA", false }, { ")", true }),
    { { "3", true } }
  },

  //<LPA> -> ,E<LPA>
  //{","}
  { std::pair<Termino, Termino>({ "LPA", false }, { ",", true }),
    { {",", true}, { "E", false }, {"LPA", false} }
  },

  //E -> TE'
  //{"(", "a", "n", "c", "@"}
  { std::pair<Termino, Termino>({ "E", false }, { "(", true }),
    { { "T", false }, {"E'", false} }
  },
  { std::pair<Termino, Termino>({ "E", false }, { "a", true }),
    { { "T", false }, {"E'", false} }
  },
  { std::pair<Termino, Termino>({ "E", false }, { "n", true }),
    { { "T", false }, {"E'", false} }
  },
  { std::pair<Termino, Termino>({ "E", false }, { "c", true }),
    { { "T", false }, {"E'", false} }
  },
  { std::pair<Termino, Termino>({ "E", false }, { "@", true }),
    { { "T", false }, {"E'", false} }
  },

  //E' -> +TE'
  //{"+"}
  { std::pair<Termino, Termino>({ "E'", false }, { "+", true }),
    { { "+", true }, {"T", false}, { "E'", false } }
  },

  //E' -> -TE'
  //{"-"}
  { std::pair<Termino, Termino>({ "E'", false }, { "-", true }),
    { { "-", true }, {"T", false}, { "E'", false } }
  },

  //E' -> 3
  //{",", ")", ";", ">", "g", "<", "P", "q", "!"}
  { std::pair<Termino, Termino>({ "E'", false }, { ",", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { ")", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { ";", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { ">", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { "g", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { "<", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { "p", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { "q", true }),
    { {"3", true} }
  },
  { std::pair<Termino, Termino>({ "E'", false }, { "!", true }),
    { {"3", true} }
  },

  //T -> FT'
  //{"(", "a", "n", "c", "@"}
  { std::pair<Termino, Termino>({ "T", false }, { "(", true }),
    { { "F", false }, {"T'", false} }
  },
  { std::pair<Termino, Termino>({ "T", false }, { "a", true }),
    { { "F", false }, {"T'", false} }
  },
  { std::pair<Termino, Termino>({ "T", false }, { "n", true }),
    { { "F", false }, {"T'", false} }
  },
  { std::pair<Termino, Termino>({ "T", false }, { "c", true }),
    { { "F", false }, {"T'", false} }
  },
  { std::pair<Termino, Termino>({ "T", false }, { "@", true }),
    { { "F", false }, {"T'", false} }
  },

  //E' -> *FT'
  //{"*"}
  { std::pair<Termino, Termino>({ "E'", false }, { "*", true }),
    { {"*", true}, { "F", false }, {"T'", false} }
  },

  //E' -> /FT'
  //{"/"}
  { std::pair<Termino, Termino>({ "E'", false }, { "/", true }),
    { {"/", true}, { "F", false }, {"T'", false} }
  },

  //T' -> 3
  //{",", "-", "+", ")", ";", ">", "g", "<", "p", "q", "!"}
  { std::pair<Termino, Termino>({ "T'", false }, { ",", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "-", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "+", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { ")", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { ";", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { ">", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "g", true }),
    { {"3", true  } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "<", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "p", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "q", true }),
    { {"3", true } }
  },
  { std::pair<Termino, Termino>({ "T'", false }, { "!", true }),
    { {"3", true } }
  },

  //F -> (E)
  //{"("}
  { std::pair<Termino, Termino>({ "F", false }, { "(", true }),
    { {"(", true }, {"E", false}, {")", true} }
  },

  //F -> a
  //{"a"}
  { std::pair<Termino, Termino>({ "F", false }, { "a", true }),
    { {"a", true } }
  },

  //F -> n
  //{"n"}
  { std::pair<Termino, Termino>({ "F", false }, { "n", true }),
    { {"n", true } }
  },


  //F -> c
  //{"c"}
  { std::pair<Termino, Termino>({ "F", false }, { "c", true }),
    { {"c", true } }
  },

  //F -> @a(<LP>)
  //{"@"}
  { std::pair<Termino, Termino>({ "F", false }, { "@", true }),
    { {"@", true }, {"a", true}, {"(", true}, {"LP", false}, {")", true} }
  },

  // a , a
  { std::pair<Termino, Termino>({ "a", true }, { "a", true }),
    { { "a", true } }
  },

  // e , e
  { std::pair<Termino, Termino>({ "e", true }, { "e", true }),
    { { "e", true } }
  },

  // m , m
  { std::pair<Termino, Termino>({ "m", true }, { "m", true }),
    { { "m", true } }
  },

  // ( , (
  { std::pair<Termino, Termino>({ "(", true }, { "(", true }),
    { { "(", true } }
  },

  // ) , )
  { std::pair<Termino, Termino>({ ")", true }, { ")", true }),
    { { ")", true } }
  },

  // [ , [
  { std::pair<Termino, Termino>({ "[", true }, { "[", true }),
    { { "[", true } }
  },

  // ] , ]
  { std::pair<Termino, Termino>({ "]", true }, { "]", true }),
    { { "]", true } }
  },

  // ; , ;
  { std::pair<Termino, Termino>({ ";", true }, { ";", true }),
    { { ";", true } }
  },

  // = , =
  { std::pair<Termino, Termino>({ "=", true }, { "=", true }),
    { { "=", true } }
  }
    
};

Parser::Parser(std::vector<Termino> &cadenaDeAtomos) : cadenaDeAtomos(cadenaDeAtomos) {
  this -> consumir.push({ "&", true });
  this -> consumir.push({ "P", false });
  cadenaDeAtomos.push_back(Termino({ "^", true }));
}

bool Parser::consumirAtomos(bool verbose) {
  while (true) {
    Termino consumirStack = this -> consumir.top();
    Termino consumirCadena = this -> cadenaDeAtomos.front();

    if (verbose) {
      std::getchar();
      std::cout << "\nStack = ";
      std::stack<Termino> A;
      while (!consumir.empty()) {
	std::cout << consumir.top().identificador << " ";
	Termino t = consumir.top(); consumir.pop(); A.push(t);
      } std::cout << "\n";

      while (!A.empty()) { consumir.push(A.top()); A.pop(); }
    }
    
    if (consumirStack == Termino({ "&", true }) && consumirCadena == Termino({ "^", true }))
      return true;

    auto itProducir = this -> reglasDeProduccion.find(std::make_pair(consumirStack, consumirCadena));
    if (itProducir == reglasDeProduccion.end()) {
      // Error
      std::cout << ">ERROR: El átomo a consumir '" << consumirCadena.identificador << "' no se encontró en ninguna producción del "
		<< "último elemento del stack: '" << consumirStack.identificador << "'.\n";
      
      return false;
    }
    std::vector<Termino> producir = itProducir -> second;

    if (verbose) { for (auto a : cadenaDeAtomos) std::cout << a.identificador << " "; std::cout<<"\n"; }
    
    if (producir.front() == Termino({ "3", true })) { // Pop y retén
      if (verbose) std::cout << "POP Y RETEN\n";
      consumir.pop();
    }
    else if (producir.front().terminal && (int)producir.size() == 1) { // Pop y avanza
      if (verbose) std::cout << "POP Y AVANZA\n";
      consumir.pop();
      cadenaDeAtomos.erase(cadenaDeAtomos.begin());
      continue;
    }
    else if (producir.front().terminal) { // Reemplazo y avanza
      if (verbose) std::cout << "REEMPLAZO Y AVANZA\n";
      consumir.pop();
      for (int i = (int)producir.size() - 1; i > 0; i--)
	consumir.push(producir[i]);
      cadenaDeAtomos.erase(cadenaDeAtomos.begin());
    }
    else if (!producir.front().terminal) { // Reemplazo y retén
      if (verbose) std::cout << "REEMPLAZO Y RETEN\n";
      consumir.pop();
      for (int i = (int)producir.size() - 1; i >= 0; i--)
	consumir.push(producir[i]);
    }
  }
}
