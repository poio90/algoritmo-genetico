/*
    Esta clase contiene rodas las funciones relacionados con la selección de la problación

    sumario:
      b_tournament -> selecciona  el mejor entre dos oponentes
      roulette -> selecciona un individuo en función de un número aleatorio
      sus -> selecciona todos los individuos necesarios en función de un número aleatorio
      best_individuals -> inserta el elemento de una posición en otra, ambas seleccionada aleatorimente
      select -> implementa un selector (ruleta o torneo binario) para seleccionar a los individuos de la nueva problación
*/

#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <stdlib.h>
#include <fstream>
#include "utils.hpp"
#include "config.hpp"


using namespace std;
class Selector{
private:
    void b_tournament(Population*, Population*);
    double* asign_probability(Population*);
    void roulette(Population*, Population*);
    void sus(Population*, Population*);
    void best_individuals(Population*, Population*);
    void (Selector::*operadors)(Population*, Population*);
public:
    Selector(int);
    void select(Population*, Population*);
};

#endif
