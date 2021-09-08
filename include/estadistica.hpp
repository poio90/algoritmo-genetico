/*
    Esta clase contiene rodas las funciones relacionadas con los cálculos estadísticos del algoritmo

    sumario:
      set_avg_fit -> setea el fitness promedio
      set_avg_fit_init -> setea el fitness promedio de la inicialización de la población
      set_best_init -> setea la mejor solición al inicializar la población
      set_total_fit -> setea el fitness total de la población
      increment_total_i -> incrementa la cantidad de iteraciones
      increment_total_eval -> incrementa la cantidad de evaluaciones
      get_start_time -> setea y devuelve un timestamp al inicio
      get_final_time -> setea y devuelve un timestamp final
      set_population_size -> setea el tamaño de la población
      set_upper_bouns -> setea el limite optimo superior
      set_lower_bouns -> setea el limite optimo inferior
      set_best_value -> guarda la mejor solucion
      gap -> devuelve el porcentaje de error respecto al óptimo
      agap -> devuelve el porcentaje de error promedio respecto al óptimo
      get_total_i -> devuelve el total de iteraciones
      get_total_eval -> devuelve el total de evaluaciones
      get_avg_fit -> devuelve el fitness promedio
      get_total_fit -> devuelve el fitness total
      get_time -> devuelve el tiempo transcurrido entre inicio y fin
      sumarize -> guarda en un archivo los resultados finales de la ejecución
      partial_sumarize -> guarda en un archivo los resultados finales de cada iteracion
      header -> escribe el encabezado al comienzo del archivo
*/

#ifndef ESTADISTICA_HPP
#define ESTADISTICA_HPP

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "utils.hpp"
#include <chrono>

using namespace std; 

class Estadistica{
private:
    //estadistica de la población
    int population_size;
    double lower_bound;
    double upper_bound;

    //estadisticas de fitness
    double avg_fit;
    double avg_init_fit;
    double best_init;
    double best_fit;
    double total_fit;
    float _gap;
    float _agap;

    //estadisticas de iteraciones
    int best_i;
    int total_i;
    int pos_best_sol;

    //estadisticas de tiempo
    float best_time;//milliseconds
    chrono::system_clock::time_point start_time;
    chrono::system_clock::time_point final_time;
    
    //estaditicas de evaluaciones
    int total_eval;
    int best_eval;
    
    string nombreArchivo;
    
    
public:
    
    Estadistica();
    
    void set_avg_fit();
    void set_avg_init_fit();
    void set_best_init(double);
    void set_total_fit(double);
    void increment_total_i();
    void set_final_time();
    void set_start_time();
    void increment_total_eval();
    void set_population_size(int);
    void set_upper_bound(double);
    void set_lower_bound(double);
    void set_best_values(Individual*, int);
    void gap();
    void agap();
    int get_total_i();
    int get_total_eval();
    double get_avg_fit();
    double get_total_fit();
    float get_time();
    void partial_sumarize();
    void sumarize(int);
    void header(int);
    void setNombreArchivo(string);
};

#endif
