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

** Archivo non_terminal.h: Declaración de la clase de no terminales.
**      Contiene las declaraciones de la clase de no terminales.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**/

#ifndef NON_TERMINAL_H
#define NON_TERMINAL_H

#include <iostream>

#include "chain.h"

class Non_terminal : public Chain {
 private:
  Chain not_terminal_;
 public:
  const Chain& getNotTerminal () {return not_terminal_;}
};
std::istream& operator >>(std::istream& in, Non_terminal& non_terminal);

#endif