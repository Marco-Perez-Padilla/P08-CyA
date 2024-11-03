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

** Archivo production.h: Declaración de la clase producciones.
**      Contiene las declaraciones de la clase producciones.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**      01/11/2024 - Creacion de operadores para la utilizacion de set
**      02/11/2024 - Creacion de constructor dados tanto una secuencia como un simbolo no terminal
**      03/11/2024 - Adicion operador <<
**/

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <iostream>

#include "chain.h"
class Production {
 private:
  Chain sequence_;           // Sequence that specifies the production rule
  Chain production_symbol_;  // Non terminal symbol of each production
 public:
  // Constructors
  Production () = default;
  Production (const Chain& production_symbol) : production_symbol_ (production_symbol) {}
  Production (const Chain& sequence, const Chain& production_symbol) : sequence_(sequence), production_symbol_ (production_symbol) {}
  Production (const Symbol& production_symbol) {
    production_symbol_.AddBack(production_symbol);
  }
  // Getters
  const Chain& getSequence () const {return sequence_;}
  const Chain& getProductionSymbol () const {return production_symbol_;}
  // Operator
  friend std::istream& operator >>(std::istream& in, Production& production);
};
// Operators
bool operator==(const Production&, const Production&);
bool operator<(const Production&, const Production&);
std::ostream& operator<<(std::ostream& os, const Production& production);

#endif