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

** Archivo production.cc: Implementación de la clase producciones.
**      Contiene las implementaciones de la clase producciones.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**      01/11/2024 - Creacion de operadores para la utilizacion de set
**      03/11/2024 - Adicion operador <<
**/

#include <iostream>

#include "production.h"


/**
 * @brief Overload of >> operator 
 * @param istream 
 * @param Production
 * @return istream
 */
std::istream& operator>>(std::istream& in, Production& production) {
  in >> production.production_symbol_;
  in >> production.sequence_;
  return in;
}


/**
 * @brief Overload of == operator 
 * @param Production 
 * @param Production
 * @return bool-type. True if both productions are equal. False otherwise
 */
bool operator==(const Production& prod_1, const Production& prod_2) {
  if (prod_1.getProductionSymbol() == prod_2.getProductionSymbol()) {
    return true;
  }
  return false;
}


/**
 * @brief Overload of < operator 
 * @param Production 
 * @param Production
 * @return bool-type. True if the first production is minor than the second one. False otherwise
 */
bool operator<(const Production& prod_1, const Production& prod_2) {
  return prod_1.getSequence().ChainSize() < prod_2.getSequence().ChainSize();
}


/**
 * @brief Overload of << operator for Production class
 * @param ostream
 * @param Production
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const Production& production) {
  os << production.getProductionSymbol().getChain() << " " << production.getSequence().getChain();
  return os;
}