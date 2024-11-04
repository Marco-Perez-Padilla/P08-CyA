/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 8: Gramáticas en Forma Normal de Chomsky
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 18/10/2024

** Archivo p06_finite_automaton.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las clases Grammar, Production, cadena, símbolo y 
**      alfabeto para aplicar el algoritmo de Forma Normal de Chomsky a una gramatica dada en base a dos
**      ficheros de entrada  y salida .gra que contienen la codificación de la gramática a transformar y
**      el resultado, respectivamente.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      01/11/2024 - Creacion (primera version) del codigo
**      02/11/2024 - Arreglo del constructor
**      03/11/2024 - Creacion de FN Chomsky
**/

#include <iostream>

#include "check_functions.h"
#include "grammar.h"

int main (int argc, char* argv[]) {
  ValidateCommand(argc, argv);
  Grammar grammar(argv[1]);
  std::cout << grammar << std::endl;
  Grammar simplified;
  simplified = grammar.ChomskyNormalForm(grammar);
  Grammar::WriteGrammar(argv[2], simplified);
  return 0;
}