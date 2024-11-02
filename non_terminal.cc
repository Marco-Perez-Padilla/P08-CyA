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

** Archivo non_terminal.cc: Implementación de la clase de no terminales.
**      Contiene las implementaciones de la clase de no terminales.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**      01/11/2024 - Sobrecarga operador >>
**      01/11/2024 - Sobrecarga de los operadores de comparacion
**      01/11/2024 - Adicion constructor 
**/

#include <iostream>

#include "non_terminal.h"


/**
 * @brief Overload of >> operator 
 * @param istream 
 * @param Non_terminal
 * @return istream
 */
std::istream& operator>>(std::istream& in, Non_terminal& non_terminal) {
  in >> non_terminal.not_terminal_;
  return in;
}


/**
 * @brief Overload of < operator 
 * @param Non_terminal 
 * @param Non_terminal
 * @return bool
 */
bool operator<(const Non_terminal& nt_1, const Non_terminal& nt_2) {
    // Primero comparamos por tamaño
    if (nt_1.getNotTerminal().ChainSize() != nt_2.getNotTerminal().ChainSize()) {
      return nt_1.getNotTerminal().ChainSize() < nt_2.getNotTerminal().ChainSize();
    }
    // Si tienen el mismo tamaño, comparamos símbolo a símbolo
    for (size_t i = 0; i < nt_1.getNotTerminal().ChainSize(); ++i) {
      if (nt_1.getNotTerminal().getChain()[i].getSymbol() != 
          nt_2.getNotTerminal().getChain()[i].getSymbol()) {
        return nt_1.getNotTerminal().getChain()[i].getSymbol() < 
               nt_2.getNotTerminal().getChain()[i].getSymbol();
      }
    }
    return false;  // Son iguales
  
}


/**
 * @brief Overload of == operator 
 * @param Non_terminal 
 * @param Non_terminal
 * @return bool
 */
bool operator==(const Non_terminal& nt_1, const Non_terminal& nt_2) {
  if (nt_1.getNotTerminal().ChainSize() != nt_2.getNotTerminal().ChainSize()) {
      return false;
    }
    for (size_t i = 0; i < nt_1.getNotTerminal().ChainSize(); ++i) {
      if (nt_1.getNotTerminal().getChain()[i].getSymbol() != 
          nt_2.getNotTerminal().getChain()[i].getSymbol()) {
        return false;
      }
    }
    return true;
}


/**
 * @brief Constructor based on a string
 * @param string
 */
Non_terminal::Non_terminal(const std::string& line) {
  for (long unsigned int i {0}; i < line.size(); ++i) {
    not_terminal_.AddBack(Symbol(line[i]));
  }
}