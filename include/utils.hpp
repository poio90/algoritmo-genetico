/*
  Esta clase contiene las funciones auxiliares a fin de simplificar el código de las clases principales

  summario:
    permute(Solucion, int) -> realiza una permutación sobre la solucion s aplicando N veces el operador de intercambio.
    invert(int*, int*) -> invierte los valores entre el primer y segundo parámetro
    insert(int*, int*) -> inserta el primer parámetro en la posición del segundo, desplazando este una posición hacia adelante.
    interchange(int*, int*) -> intercambia las posiciones de los parametros.
    int generate_point(int, int) -> genera un indice de forma aleatoria.
    randd -> genera un double de forma aleatoria
    randi -> genera un int de forma aleatoria
    copy_population -> copia la población completa a un nuevo objeto
    copy_indiviual -> copia un individuo completo a un nuevo objeto
    copy_solution -> copia la solución completa a un nuevo objeto
*/
#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "individual.hpp"


using namespace std;

class Utils{
private:
public:
  void permute(Solution);
  int generate_point(int, int);
  int randi(int, int);
  double randd(int, int);
  void insert(int*, int*);
  void interchange(int*, int*);
  void invert(int*, int*);
  void copy_population(Population*,Population*);
  void copy_individual(Individual*, Individual*);
  void copy_solution(Solution*, Solution*);
  bool check_population(Population*);
  bool check_individual(Individual*);
  void print_individual(Individual);
  void print_fitness(double);
  void print_solution(Solution);
  void print_population(Population*);
  void print_individual_to_file(Individual);
  void print_solution_to_file(Solution);
};

#endif
