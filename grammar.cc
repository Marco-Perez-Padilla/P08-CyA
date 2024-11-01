/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 8: Gramáticas en Forma Normal de Chomsky
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 01/11/2024

** Archivo grammar.cc: Implementación de la clase gramatica.
**      Contiene las implementaciones de la clase gramatica.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**/

#include <iostream>
#include <fstream>

#include "grammar.h"
#include "check_functions.h"

Grammar::Grammar (const std::string& input_gra) {
  if (ReadGrammar(input_gra)) {}
  else {
    exit(EXIT_FAILURE);
  }
}


bool Grammar::ReadGrammar (const std::string& file_gra) {
  std::ifstream input_gra(file_gra);
  if (!input_gra.is_open()) {
    std::cerr << "Error: File couldn't be opened " << file_gra << ". Try \"./Grammar2CNF --help\" for further information " << std::endl;
    return false;
  }

  std::string line;

  long unsigned int alphabet_size {0};
  Alphabet alphabet;
  long unsigned int non_terminal_size {0};

  //Reading alphabet size
  if (std::getline(input_gra, line)) {
    if (!ValidateNumber(line)) {
      std::cerr << "Incorrect input format in line 1: Number of symbols of alphabet must be provided. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
    alphabet_size = std::stoi(line);
    if (alphabet_size == 0) {
      std::cerr << "Incorrect input format in line 1: Number of symbols of alphabet must be different than 0. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
  }

  //Reading alphabet
  for (long unsigned int i {0}; i < alphabet_size; ++i) {
    if (std::getline(input_gra, line)) {
      for (char chr : line) {
        if (chr != ' ' && chr != '&' ) {
          alphabet.AddSymbol(Symbol(chr));
        }
      }
    }
  }

  //Reading number of non-terminal symbols
  if (std::getline(input_gra, line)) {
    if (!ValidateNumber(line)) {
      std::cerr << "Incorrect input format in line " << alphabet_size + 2 << ": Number of non-terminal symbols must be provided. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
    non_terminal_size = std::stoi(line);
    if (non_terminal_size == 0) {
      std::cerr << "Incorrect input format in line " << alphabet_size + 2 << ": Number of non-terminal symbols must be different than 0. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
  }

  //Reading non-terminal symbols
  for (long unsigned int i {0}; i < non_terminal_size; ++i) {
    if (std::getline(input_gra, line)) {
      for (char chr : line) {
        if (chr != ' ' && chr != '&' ) {
          alphabet.AddSymbol(Symbol(chr));
        }
      }
    }
  }
}


const bool Grammar::FindProduction (const Production& production) {
  for (int i {0}; i < getProductions().size(); ++i) {
    if (production == getProductions()[i]) {
      return true;
    }
  }
  return false;
}


const Production& Grammar::FindEquivalentProduction (const Production& production) {
  for (int i {0}; i < getProductions().size(); ++i) {
    if (production == getProductions()[i]) {
      return getProductions()[i];
    }
  }
}
