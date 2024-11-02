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
**/

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <iostream>

#include "chain.h"
#include "non_terminal.h"

class Production {
 private:
  Chain sequence_;
  Chain production_symbol_;
 public:
  Production () = default;
  Production (const Chain& production_symbol) : production_symbol_ (production_symbol) {}
  Production (const Symbol& production_symbol) {
    production_symbol_.AddBack(production_symbol);
  }
  const Chain& getSequence () const {return sequence_;}
  const Chain& getProductionSymbol () const {return production_symbol_;}
  const bool Empty ();
  //const bool Unitary ();
  //const bool Useless ();
  friend std::istream& operator >>(std::istream& in, Production& production);

};
bool operator==(const Production&, const Production&);
bool operator<(const Production&, const Production&);

#endif