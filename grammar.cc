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
**      01/11/2024 - Creacion de metodos para leer el archivo .gra
**      02/11/2024 - Correcion de bugs en el metodo ReadGrammar
**/

#include <iostream>
#include <fstream>
#include <sstream>

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
  long unsigned int productions_number {0};

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
      if (line.empty()) {
        std::cerr << "Error in line " << alphabet_size + 3 + i << ": Non-terminal symbol cannot be non-existent" << std::endl;
        return false;
      }
      Chain new_non_terminal (line);

      // Verificar si el no terminal ya existe
      if (non_terminal_symbols_.find(new_non_terminal) != non_terminal_symbols_.end()) {
        std::cerr << "Error in line " << alphabet_size + 3 + i << ": Duplicate non-terminal symbol" << std::endl;
        return false;
      }

      non_terminal_symbols_.insert(new_non_terminal);
    } else {
      std::cerr << "Error in line " << alphabet_size + 3 + i << ": Unkown error reading the line" << std::endl;
    }
  }

  //Reading number of productions
  if (std::getline(input_gra, line)) {
    if (!ValidateNumber(line)) {
      std::cerr << "Incorrect input format in line " << alphabet_size + non_terminal_size + 3 << ": Number of productions must be provided. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
    productions_number = std::stoi(line);
    if (productions_number == 0) {
      std::cerr << "Incorrect input format in line " << alphabet_size + non_terminal_size + 3 << ": Number of productions must be different than 0. Try \"./Grammar2CNF --help\" for further information" << std::endl;
      return false;
    }
  }

  //Reading productions
  Chain prod_symbol;
  Chain sequence;
  for (long unsigned int i {0}; i < productions_number; ++i) {
    if (std::getline(input_gra, line)) {
      int space_counter {0};
      for (char chr : line) {
        if (chr == ' ') {
          ++space_counter;
        }
      }
    
      //Checks if there is more than one or no space
      if (space_counter != 1) {
        std::cerr << "Incorrect input format in line " << alphabet_size + non_terminal_size + 4 + i << ": There is no or more than one space. Try \"./Grammar2CNF --help\" for further information" << std::endl;
        return false;
      }
      //Checks for inexistant space
      long unsigned int position = line.find(' ');

      if (position >= line.size()) {
        std::cerr << "Fatal error "<< alphabet_size + non_terminal_size + 4 + i <<": Production cannot be empty. Try \"./Grammar2CNF --help\" for further information" << std::endl;
        return false;
      }

      //Substraction of the non-terminal symbol and the production
      std::string production_symbol = line.substr(0, position);
      std::string production = line.substr(position + 1);

      Chain prod_symbol(production_symbol);
      Chain sequence(production);

      for (long unsigned int j {0}; j < prod_symbol.ChainSize(); ++j) {
        if (alphabet.Find(prod_symbol[j])) {
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": A terminal symbol cannot be part of a non terminal symbol." << std::endl;
          return false;
        }
      }

      if (FindNonTerminal(prod_symbol)) {
        if (sequence.ChainSize() == 0 && sequence.getChain()[0].getSymbol() == '&') {
          productions_[Chain(prod_symbol)].push_back(Production(sequence));
        } else if (sequence.Empty()) {
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Production cannot be empty" << std::endl;
          return false;
        } else {
          for (long unsigned int j {0}; j < sequence.ChainSize(); ++j) {
            Production temp_prod (sequence.getChain()[j]);
            Symbol current_symbol = sequence.getChain()[j];
            Chain temp_chain;
            temp_chain.AddBack(current_symbol);
            // Add greater non terminal verification here
            if (!alphabet.Find(sequence.getChain()[j]) && !FindNonTerminal(temp_chain)) {
              std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Error in production " << sequence.getChain() << " symbol " << sequence.getChain()[j] << " does not belong to alphabet and/or isn't an specified non-terminal symbol" << std::endl;
              return false;
            }
          }
          productions_[Chain(prod_symbol)].push_back(Production(sequence));
        }
      } else {
        std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": " << prod_symbol << " hasn't been specified beforehand" << std::endl;
        return false;
      }
    }
  }
  return true;
}



const bool Grammar::FindNonTerminal (const Chain& production) {
  Chain production_symbol(production);
  if (non_terminal_symbols_.find(production_symbol) != non_terminal_symbols_.end()) {
    return true;
  }
  return false;
}


/*
const Production& Grammar::FindProduction (const Production& production) {
  for (int i {0}; i < getProductions().size(); ++i) {
    if (production == getProductions()[i]) {
      return getProductions()[i];
    }
  }
}
*/