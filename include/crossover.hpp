/*
    Esta clase contiene rodas las funciones relacionadas con el crossover de los individuos

    sumario:
      CX -> cycle crossover
      OX -> order crossover
      PMX -> partial mapped crossover
*/

#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <iostream>
#include <fstream>
#include <list>
#include "config.hpp"
#include "utils.hpp"
#include "problem.hpp"


class Crossover{
private:
  void cx(Individual*, Individual*, int, int);
  void pmx(Individual*, Individual*, int, int);
  void ox(Individual*, Individual*, int, int);
  bool exist(Solution*, int, int, int);
  bool exist(list<int>, int);
  void mapping(Solution*, Solution*, int, int);
  void reorder(Solution*, int, int, int, int*);
  void (Crossover::*operatorc)(Individual*, Individual*, int, int);
public:
  Crossover(int);
  void crossover(float, Population*);
};

#endif
