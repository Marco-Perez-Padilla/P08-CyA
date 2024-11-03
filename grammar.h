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

** Archivo grammar.h: Declaración de la clase gramatica.
**      Contiene las declaraciones de la clase gramatica.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**      01/11/2024 - Creacion de metodos para leer el archivo .gra
**      02/11/2024 - Creacion de InsertProduction y ChomskyNormalForm
**      03/11/2024 - Adicion segunda parte ChomskyNormalForm
**      03/11/2024 - Adicion sobrecarga operador <<
**      03/11/2024 - Adicion WriteGrammar
**/

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "alphabet.h"
#include "production.h"

class Grammar {
 private:
  Alphabet terminal_symbols_;                              // Stores the terminal symbols
  std::set<Chain> non_terminal_symbols_;                   // Stores the non terminal symbols
  std::map<Chain, std::vector<Production>> productions_;   // Stores the productions as a whole
  bool ReadGrammar (const std::string&);                   // Reads the grammar and is used in the constructor
 public:
  // Constructors
  Grammar () = default;
  Grammar (const std::string&);
  // Default destructor
  ~Grammar () = default;
  // Getters
  const Alphabet& getTerminalSymbols () const {return terminal_symbols_;}
  const std::set<Chain>& getNonTerminalSymbols () const {return non_terminal_symbols_;}
  const std::map<Chain, std::vector<Production>>& getProductions () const {return productions_;}
  // Non-terminals methods
  const bool FindNonTerminal (const Chain&) const;
  // Grammar methods
  const Grammar& ChomskyNormalForm (const Grammar&) const; 
  void InsertProduction(const Chain& non_terminal, const Production& production);
  static void WriteGrammar (const std::string&, const Grammar&);
};
// Operators
std::ostream& operator<<(std::ostream& os, const Grammar&);

#endif