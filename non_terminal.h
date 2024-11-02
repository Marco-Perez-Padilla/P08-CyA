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
**      01/11/2024 - Sobrecarga operador >>
**      01/11/2024 - Sobrecarga de los operadores de comparacion
**      01/11/2024 - Adicion constructor 
**/

#ifndef NON_TERMINAL_H
#define NON_TERMINAL_H

#include <iostream>

#include "chain.h"

class Non_terminal {
 private:
  Chain not_terminal_;
 public:
  Non_terminal () = default;
  Non_terminal (const std::string& line);
  Non_terminal (const Chain& not_terminal) : not_terminal_ (not_terminal) {}
  const Chain& getNotTerminal () const {return not_terminal_;}
  friend std::istream& operator>>(std::istream& in, Non_terminal& non_terminal);
};
bool operator<(const Non_terminal&, const Non_terminal&);
bool operator==(const Non_terminal&, const Non_terminal&);

#endif