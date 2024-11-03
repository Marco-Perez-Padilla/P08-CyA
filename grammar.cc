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
**      02/11/2024 - Creacion de InsertProduction y ChomskyNormalForm
**/

#include <iostream>
#include <fstream>
#include <sstream>

#include "grammar.h"
#include "check_functions.h"


/**
 * @brief constructor given an input file which will be the argument of ReadGrammar here used
 * @param string name of the input file
 */
Grammar::Grammar (const std::string& input_gra) {
  if (ReadGrammar(input_gra)) {}
  else {
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief Method to read the grammar given by a .gra input file
 * @param string name of the input file
 * @return bool-type. True if it's been correctly read, false otherwise
 */
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

  // Reading productions
  Chain prod_symbol;
  Chain sequence;
  long unsigned iteration {0};
  for (long unsigned int i {0}; i < productions_number; ++i) {
    if (std::getline(input_gra, line)) {
      int space_counter {0};
      for (char chr : line) {
        if (chr == ' ') {
          ++space_counter;
        }
      }
    
      // Checks if there is more than one or no space
      if (space_counter != 1) {
        std::cerr << "Incorrect input format in line " << alphabet_size + non_terminal_size + 4 + i << ": There is no or more than one space. Try \"./Grammar2CNF --help\" for further information" << std::endl;
        return false;
      }

      // Checks for inexistant space
      long unsigned int position = line.find(' ');

      if (position >= line.size()) {
        std::cerr << "Fatal error "<< alphabet_size + non_terminal_size + 4 + i <<": Production cannot be empty. Try \"./Grammar2CNF --help\" for further information" << std::endl;
        return false;
      }

      // Substraction of the non-terminal symbol and the production
      std::string production_symbol = line.substr(0, position);
      std::string production = line.substr(position + 1);

      // Conversion to chain type
      Chain prod_symbol(production_symbol);
      Chain sequence(production);

      // If the production symbol is part of the alphabet (terminal symbol), abort
      for (long unsigned int j {0}; j < prod_symbol.ChainSize(); ++j) {
        if (alphabet.Find(prod_symbol[j])) {
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": A terminal symbol cannot be part of a non terminal symbol." << std::endl;
          return false;
        }
      }

      if (FindNonTerminal(prod_symbol)) {
        // If null production, then:
        if (sequence.ChainSize() == 0 && sequence.getChain()[0].getSymbol() == '&') {
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Production cannot be a null production" << std::endl;
          return false;
        } else if (sequence.Empty()) { // If no production is specified, then
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Production cannot be empty" << std::endl;
          return false;
        } else if (sequence.ChainSize() == 1 && FindNonTerminal(Chain(sequence.getChain()))) {
          std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Production cannot be unitary production" << std::endl;
          return false;
        } else {
          // For each symbol in the production
          for (long unsigned int j {0}; j < sequence.ChainSize(); ++j) {
            Production temp_prod (sequence.getChain()[j]);
            Symbol current_symbol = sequence.getChain()[j];
            // If there is a & in middle/start/end of a production, it'll be skipped
            if (current_symbol == Symbol('&')) {
              continue;
            }
            Chain temp_chain;
            temp_chain.AddBack(current_symbol);
            // Add greater non terminal verification here

            // If symbol is not part of the alphabet, or isn't a non-terminal symbol, then
            if (!alphabet.Find(sequence.getChain()[j]) && !FindNonTerminal(temp_chain)) {
              std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": Error in production " << sequence.getChain() << " symbol " << sequence.getChain()[j] << " does not belong to alphabet and/or isn't an specified non-terminal symbol" << std::endl;
              return false;
            }
          }
          // Add production
          productions_[Chain(prod_symbol)].push_back(Production(sequence));
        }
      } else {
        std::cerr << "Error in line " << alphabet_size + non_terminal_size + 4 + i << ": " << prod_symbol << " hasn't been specified beforehand" << std::endl;
        return false;
      }
      ++iteration;

    }
  }
  if (iteration != productions_number) {
    std::cerr << "Error in productions format: Number of productions (" << productions_number << ") does not much the transitions specified (" << iteration << ")" << std::endl;
    return false;
  }
  input_gra.close();
  return true;
}


/**
 * @brief Finds if a production is part of the non_terminal_symbols of the grammar
 * @param Chain which represents a production
 * @return bool-type. True if found, false otherwise
 */
const bool Grammar::FindNonTerminal (const Chain& production) const {
  Chain production_symbol(production);
  if (non_terminal_symbols_.find(production_symbol) != non_terminal_symbols_.end()) {
    return true;
  }
  return false;
}



const Grammar& Grammar::ChomskyNormalForm (const Grammar& grammar) const {
  Grammar simplifying_grammar = grammar;
  std::map<Symbol, Chain> new_non_terminal;
  
  // Replacing terminal symbols by non-terminal symbols
  for (auto& productions : grammar.getProductions()) {
    const Chain& prod_symbol = productions.first;
    const std::vector<Production>& prod_list = productions.second;
    Chain new_sequence;
    // For each production
    for (const Production& production : prod_list) {
      // If it has at least two elements
      if (production.getSequence().ChainSize() >= 2) {
        Chain sequence = production.getSequence();
        for (long unsigned int i {0}; i < sequence.ChainSize(); ++i) {
          // If the symbol is a terminal symbol
          if (grammar.getTerminalSymbols().Find(sequence[i])) { 
            Symbol terminal_symbol = sequence[i];
            // If it has already been evaluated
            if (new_non_terminal.find(terminal_symbol) != new_non_terminal.end()) {
              new_sequence.AddBack(new_non_terminal[terminal_symbol]);
            } else {
              Chain new_name;
              new_name.AddBack(terminal_symbol);
              new_name.AddBack(Symbol('_'));
              Chain new_non_terminal_chain(new_name);
              new_non_terminal[terminal_symbol] = new_non_terminal_chain;
              Production new_prod (new_non_terminal_chain, Chain({terminal_symbol}));
              simplifying_grammar.InsertProduction(new_non_terminal_chain, new_prod);
              new_sequence.AddBack(new_non_terminal_chain);
            }
          } else {
            new_sequence.AddBack(sequence[i]);
          }
        }
        Production new_production(prod_symbol, new_sequence);
        simplifying_grammar.InsertProduction(prod_symbol, new_production);
      }
    }
    for (auto& productions : simplifying_grammar.getProductions()) {
      const Chain& prod_symbol = productions.first;
      const std::vector<Production>& prod_list = productions.second;
      for (const Production& production : prod_list) {
        Chain sequence = production.getSequence();
        if (sequence.ChainSize() >= 3) {
          Chain new_sequence;
          for (long unsigned int i {0}; i < sequence.ChainSize() - 2; ++i) {
            Chain new_non_terminal_chain;
            new_non_terminal_chain.AddBack(sequence[i]);
            new_non_terminal_chain.AddBack(Symbol('_'));
            new_non_terminal_chain.AddBack(sequence[i+1]);
            
          }
        }
      }
    }
  }
  return simplifying_grammar;
} 


void Grammar::InsertProduction(const Chain& non_terminal, const Production& production) {
  productions_[non_terminal].push_back(production);
}
