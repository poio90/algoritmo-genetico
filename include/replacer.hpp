/*
    Esta clase contiene rodas las funciones que intervienen en el remplazo generacional

    sumario:
    mu -> reemplaza la población de padres por la población de hijos.
    mupluslambda -> reemplaza la poblacion de 
    asign_probability -> asigna a cada solución la probabilidad de ser seleccionada
    b_tournament -> selecciona  el mejor entre dos oponentes
    roulette -> selecciona un individuo en función de un número aleatorio
    replace -> implementa un método de reemplazo (generaciona o mu + lambda)
    select -> implementa un selector (torneo binario o ruleta)
*/

#ifndef REPLACER_HPP
#define REPLACER_HPP

#include "selector.hpp"
#include "problem.hpp"

class Replacer{
private:
    void generational (Population*, Population*, Problem*);
    void mupluslambda (Population*, Population*, Problem*);
    void (Replacer::*operatorr)(Population*, Population*, Problem*);
    void (Replacer::*operators)(Population*, Individual*);
    double* asign_probability(Population*);
    void b_tournament(Population*, Individual*);
    void roulette(Population*, Individual*);
public:
  Replacer(int, int);
  void replace(Population*, Population*, Problem*);
  void select(Population*, Individual*);
};

#endif
