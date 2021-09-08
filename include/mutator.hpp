/*
    Esta clase contiene rodas las funciones relacionados con la mutación de la problación

    sumario:
      invert -> invierte el vector dos posiciones seleccionadas aleatoriamente
      interchange -> intercambia dos posiciones seleccionadas aleatoriamente
      insert -> inserta el elemente de una posición en otra, ambas seleccionada aleatorimente
*/

#ifndef MUTATOR_HPP
#define MUTATOR_HPP

#include <iostream>
#include <fstream>
#include "utils.hpp"

class Mutator{
protected:
    
    Utils utils;
    
    void scramble(int*,int*);
    
  void insert(int*, int*);
  void invert(int*, int*);
  void interchange(int*, int*);
  void (Mutator::*operatorm)(int*, int*);
public:
  Mutator(int);
  void mutate(float, Population*);
};

#endif
