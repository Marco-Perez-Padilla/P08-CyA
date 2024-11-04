/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 8: Gramáticas en Forma Normal de Chomsky
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 20/09/2024

** Archivo chain.h: Declaración de la clase cadena.
**      Contiene las declaraciones de la clase cadena.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      20/09/2024 - Creacion (primera version) del codigo
**      23/09/2024 - Adición del método empty
**      24/09/2024 - Adición de los métodos prefijos y sufijos 
**      18/10/2024 - Deleción de los métodos prefijos y sufijos para eliminar dependencia de la clase Lenguaje
**      19/10/2024 - Adición de constructor en base a un std::string
**      21/10/2024 - Adición método FindAll
**      21/10/2024 - Adición sobrecarga operador []
**      01/11/2024 - Adicion sobrecarga operador >>
**      01/11/2024 - Adicion constructor sobre un simbolo
**      02/11/2024 - Adicion Addback para una cadena
**      02/11/2024 - Adicion metodos Replace
**      03/11/2024 - Adicion sobrecarga operador <<
**/

#ifndef CHAIN_H
#define CHAIN_H

#include <vector>

#include "symbol.h"

class Chain {
 private:
  std::vector<Symbol> chain_;

 public:
  //Constructors
  Chain() = default;
  Chain(const std::vector<Symbol>& chain) : chain_(chain) {}   
  Chain(const std::string& line);

  //Getter
  const std::vector<Symbol>& getChain () const {return chain_;} 

  //Functions for chain class
  const long unsigned int ChainSize() const;
  const Chain Inverse () const;
  void AddBack (const Symbol& new_symbol);
  void AddBack (const Chain& new_chain);
  bool Empty() const; 
  const long unsigned int FindAll(const Symbol& symbol) const;
  void Replace (long unsigned int, const Symbol&);
  void Replace (long unsigned int, const Chain&);
  //Overload of operators
  bool operator<(const Chain&) const;
  bool operator==(const Chain&) const;

  //Operators
  const Symbol& operator[](long unsigned int index) const;
};

std::istream& operator>>(std::istream& in, Chain&);
std::ostream& operator<<(std::ostream& os, const Chain&);

#endif