/*
  Esta clase contiene las funciones necesarias para cargar la configuracion

  summario:
    read() -> lee los parámetros de configuración en el archivo /config/ga.config e inicializa las variables
*/
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Configuration{
private:
public:
    int epoch;
    int mu; //cantidad de padres (iguales en nuestro caso)
    int lambda;//cantidad de hijos (iguales en nuestro caso)
    int generator;
    int pselection;
    int npreplacement;
    int npselection;
    int mutation;
    float pmutation;
    int crossover;
    float pcrossover;
    //NUEVOS PARAMETROS
    int intervalo_migraciones;
    int cantidad_inmigrantes;
    double probabilidad_quedarse_con_imigrante_malo;
    string FSSP_instance;
    void read(string);
};

#endif
