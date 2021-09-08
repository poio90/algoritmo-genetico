/*
    Esta clase contiene todas las variable y funciones relacionada con el problema FSSP

    sumario:
      load -> genera una población de forma pseudoaleatoria
      initializa_parents -> genera una problación seleccionando los individuos de acuerdo a una probabilidad
      initializa_population -> genera una población seleccionando los individuos de tal forma de lograr la mejor solución inicial
      delete_population -> elimina la poblacion
      evaluate -> funcion de evaluacion del individuo
      evaluate_population -> función de evaluación de la población
*/

#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <fstream>
#include <iostream>
#include "utils.hpp"
#include "generator.hpp"
#include "estadistica.hpp"

using namespace std;

class Problem{
private:
    int msize;
    int jsize;
    int upperBound;
    int lowerBound;
    int **jobsTimes;
    Individual *best;
    Estadistica *estadistica;
public:
    Problem(Estadistica &);
    void load(string);
    void initialize_parents(int, Population*);
    void initialize_population(int, Population*);
    void delete_population(Population*);
    void evaluate(Individual*);
    void evaluate_population(Population*);
    void set_best_individual(Individual*);
    Individual* get_best();
};

#endif
