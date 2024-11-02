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
**/

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "alphabet.h"
#include "non_terminal.h"
#include "production.h"

class Grammar {
 private:
  Alphabet terminal_symbols_;
  std::set<Chain> non_terminal_symbols_;
  std::map<Chain, std::vector<Production>> productions_;
  bool ReadGrammar (const std::string&);
 public:
  Grammar () = default;
  Grammar (const std::string&);
  const Alphabet& getTerminalSymbols () {return terminal_symbols_;}
  const std::set<Chain>& getNonTerminalSymbols () {return non_terminal_symbols_;}
  const std::map<Chain, std::vector<Production>>& getProductions () const {return productions_;}
  const bool FindNonTerminal (const Chain&);
  const Production& FindProduction (const Production&);
};

#endif