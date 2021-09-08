/*
    Esta clase contiene rodas las funciones generadoras de la problación inicial

    sumario:
      random -> genera una población de forma pseudoaleatoria
      probabilistic -> genera una problación seleccionando los individuos de acuerdo a una probabilidad
      greedy -> genera una población seleccionando los individuos de tal forma de lograr la mejor solución inicial
*/

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

//#include "individual.hpp"
#include "utils.hpp"

class Generator{
private:

public:
    //Generator();
    //Generator(int);
    //void (*generate)();
    void random(Solution);
    void probabilistic();
    void greedy();
};

#endif
