#include "include/config.hpp"
#include "include/problem.hpp"
#include "include/selector.hpp"
#include "include/crossover.hpp"
#include "include/mutator.hpp"
#include "include/replacer.hpp"
#include "include/Servicio_inmigracion.hpp"
#include "include/estadistica.hpp"
#include "omp.h"
#include <random>
#include <stdio.h>


int main(int argc, char **argv){
    
    int num=1;
    
    if(argc>1){
        char *a = argv[1];
        num = atoi(a);
    }
    
    for(int CONTADOR_MEGA_ITERACION=0;CONTADOR_MEGA_ITERACION<num;CONTADOR_MEGA_ITERACION++){
    printf("\nCORRIENDO ITERACION= %i\n",CONTADOR_MEGA_ITERACION);
    

    Configuration cfg;
    cfg.read("./config/ga.config");
    
    random_device rng;
    srand(rng());
    
    //Creamos estadistica
    Estadistica estadistica;
    
    //inicializamos el problema
    Problem p(estadistica);
    p.load(cfg.FSSP_instance);
    
    //inicializar variables
    Selector s(cfg.pselection);
    Crossover c(cfg.crossover);
    Mutator m(0);//FORZOSAMENTE EN MUTADOR
    Replacer r(cfg.npreplacement, cfg.npselection);
    Population *parents = (Population*) malloc(sizeof (Population));
    Population *offprings = (Population*) malloc(sizeof (Population));
    
    p.initialize_parents(cfg.mu, parents);
    p.initialize_population(cfg.lambda, offprings);
    
    //bucle principal
    estadistica.set_start_time();
    int i = 0;
    do {
        s.select(parents, offprings);
        c.crossover(cfg.pcrossover, offprings);
        m.mutate(cfg.pmutation, offprings);
        p.evaluate_population(offprings);
        r.replace(parents, offprings, &p);
        i++;
        estadistica.increment_total_i();
    } while (i < cfg.epoch);

    estadistica.set_final_time();
    // u.print_population(parents);
    printf("..... process has finished \n");
    estadistica.setNombreArchivo("datosFinalesSecuenciales.csv");
    estadistica.header(0);
    estadistica.sumarize(0);
    
    free(parents);
    free(offprings);    
    //printf("================================================================== \n");
    
    }
}

