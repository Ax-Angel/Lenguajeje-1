#pragma once

#include <iostream>
#include <memory>

class Lexer;

class Interprete {
  std::istream &entrada;
  std::shared_ptr<Lexer> lexer;

public:
  Interprete(std::istream &entrada = std::cin);
  void cicloDeLectura();
};
