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

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      18/10/2024 - Creación de funciones de validación de formatos y de ValidateNumber
**      19/10/2024 - Adición de aclaración en Help. & como símbolo reservado a cadena vacía
**      30/10/2024 - Eliminacion de validaciones usadas para los .fa
**/

#include <regex>
#include <iostream>
#include "check_functions.h"

/**
 * @brief Validates the extension of the input text file
 * @param string  
 * @return bool-type. True if the file is accepted. False otherwise
 */
bool ValidateFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(gra)$)");
  return std::regex_match(name, pattern);
}

/**
 * @brief Checks if a given string is made out of (only) numbers or not
 * @param string
 * @return bool
 */
bool ValidateNumber (const std::string& line) {
  if (!line.empty()) {
    for (char chr : line) {
      if (!std::isdigit(chr)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Uses ValidateFile function. Acts in consequence of the returned type
 * @param string  
 */
void CheckFileError (const std::string& name) {
  if (ValidateFile(name)) return;
  std::cerr << "Error in file" << name << ": Wrong extension. Please, try \"./Grammar2CNF --help\" for further information" << std::endl;
  exit(EXIT_FAILURE);
}


/**
 * @brief Validates the line of commands and uses Help, Usage and CheckFileError functions
 * @param int argc  
 * @param char* argv[]
 */
void ValidateCommand(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    Help();
    exit(EXIT_SUCCESS);
  }
  if (argc != 3) {
    Usage();
    exit(EXIT_FAILURE);
  }
  if (argc == 3) {
    CheckFileError(std::string(argv[1]));
    CheckFileError(std::string(argv[2]));
    return;
  }
  exit(EXIT_FAILURE);
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./Grammar2CNF -- Grammar conversor to Chomsky normal form\n"
              << "Usage:          ./Grammar2CNF input.gra output.gra\n"
              << "\n"
              << "input.fa:        Input file with extension gra. Codificates the information of the input grammar such as:\n"
              << "                       Line 1: N number of symbols of the alphabet.\n"
              << "                                      - For the following N lines, there will be specified a symbol of the alphabet each line.\n"
              << "                                      - '&' cannot be part of alphabet. Reserved symbol for empty string.\n"
              << "                       Line N+1: V number of non-terminal symbols.\n"
              << "                                      - For the following V lines, there will be specified an alpha-numeric chain without spaces.\n"
              << "                                      - The chain must be formed with the symbols of the alphabet.\n"
              << "                                      - The first line will be the Start Production.\n"
              << "                       Line N+M+2: P number of productions of the grammar.\n"
              << "                                      - For the following P lines, there will be specified each production of the grammar with format: A alpha.\n"
              << "                                      - A is a production.\n"
              << "                                      - alpha is a sequence (chain) of terminal and non-terminal symbols.\n"
              << "output.gra:       Input file with extension gra. It has same format as input.fa.\n"
              << "\n";
}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./Grammar2CNF input.gra output.gra\n"
            << "Try './Grammar2CNF --help' for further information\n";
}