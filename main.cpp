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


const int CANTIDAD_HILOS = 3;
bool revisarEntorno();



int main(int argc, char **argv) {
    int num=1;
    
    if(argc>1){
        char *a = argv[1];
        num = atoi(a);
    }
    printf("\nCANTIDAD ITERACIONES= %i\n",num);
    for(int CONTADOR_MEGA_ITERACION=0;CONTADOR_MEGA_ITERACION<num;CONTADOR_MEGA_ITERACSION++){
        printf("\nCORRIENDO ITERACION= %i\n",CONTADOR_MEGA_ITERACION);
    
    //leemos la configuracion del archivo  ga.config
    Configuration cfg;
    cfg.read("./config/ga.config");
    


    //punteros para referenciar servicio de inmigrante entre hilos
    Servicio_inmigracion *p_servicios[CANTIDAD_HILOS];
    

    omp_set_num_threads(CANTIDAD_HILOS);
    bool check;
    

#pragma omp parallel firstprivate(cfg)
    {
        #pragma omp single
        {
            check = revisarEntorno();
        }
        if (check) {

            const int ID_THREAD = omp_get_thread_num();
            //poner semilla aleatoria para cada thread individualmente
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
            Mutator m(ID_THREAD);
            Replacer r(cfg.npreplacement, cfg.npselection);
            Population *parents = (Population*) malloc(sizeof (Population));
            Population *offprings = (Population*) malloc(sizeof (Population));
            
            
            int servicio_a_usar = (ID_THREAD+1)%CANTIDAD_HILOS;
             
        
            Servicio_inmigracion *servicio;
            //se divide por la cantidad de hilos, asi si la poblacion es 90, y se tienen
            //3 hilos, cada isla tendra 30 de poblacion
            p.initialize_parents((int)(cfg.mu/CANTIDAD_HILOS), parents);
            p.initialize_population((int)(cfg.lambda/CANTIDAD_HILOS), offprings);
            servicio= new Servicio_inmigracion(p, cfg.cantidad_inmigrantes, cfg.probabilidad_quedarse_con_imigrante_malo);
            p_servicios[ID_THREAD]= servicio;
        
            
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
                //es hora de migrar
                if(i%cfg.intervalo_migraciones==0){
                    
                    servicio->copiar_mejores(offprings);
                    #pragma omp barrier
                    p_servicios[servicio_a_usar]->eliminar_peores_y_migrar(offprings);
                }
                estadistica.increment_total_i();
                
            } while (i < cfg.epoch);
            estadistica.set_final_time();
            //guardar en archivo los resultados
        #pragma omp critical
        {
            estadistica.setNombreArchivo("datosFinales.csv");
            estadistica.header(ID_THREAD);
            estadistica.sumarize(ID_THREAD);
        }
            delete servicio;
            free(parents);
            free(offprings);
        }
    }
    
    }


    return EXIT_SUCCESS;
}





bool revisarEntorno() {
    int cantidad = omp_get_num_threads();
    if (cantidad != CANTIDAD_HILOS) {
        std::cerr << "\nLa cantidad de hilos no coincide con lo pedido" << std::endl;
        std::cerr << "cantidad de hilos deseados= " << CANTIDAD_HILOS << std::endl;
        std::cerr << "Cantidad de hilos obtenidos= " << cantidad << std::endl;
        return false;
    }
    return true;
}
