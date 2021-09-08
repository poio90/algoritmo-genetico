

#include "../include/Servicio_inmigracion.hpp"

Servicio_inmigracion::Servicio_inmigracion(Problem& p, int size, double probabilidad_quedarse_mal_inmigrante) {

    this->probabilidad_quedarse_con_inmigrante_malo = probabilidad_quedarse_mal_inmigrante;
    this->inmigrantes = (Population*) malloc(sizeof (Population));
    p.initialize_population(size, this->inmigrantes);
}

Servicio_inmigracion::~Servicio_inmigracion() {
    free(this->inmigrantes);
}

void Servicio_inmigracion::copiar_mejores(Population* poblacion_inmigrante) {

    Selector s(0); //el 0 representa la operacion de seleccion por torneo b_tournament
    
    /*copia los mejores de la poblacion_inmigrante en los inmigrantes para despues reemplazarlos 
    por los peores de la poblacion local*/
    s.select(poblacion_inmigrante,this->inmigrantes);

}

/**
 * Dada una poblacion, ira tomando aleatoriamente desde la posicion [1,size](el mejor se excluye)
 * y el que sea peor, se lo comparara con el fitness del inmigrante, si el inmigrante gana, entonces lo remplaza,
 * sino se jugara una probabilidad de que lo remplace igualmente.
 * @param poblacion
 */
void Servicio_inmigracion::eliminar_peores_y_migrar(Population * poblacion) {
    
    int cantidad_descalificados=0;
    
    int intentos=0;
    int indice = 0, r1, r2;
    
    int probabilidad_quedarse_con_malo = this->probabilidad_quedarse_con_inmigrante_malo*RAND_MAX;
    //recorremos toda la lista
    while (indice<this->inmigrantes->size) {
        //tomamos dos puntos aleatorios entre la poblacion, no vale el primero
        r1 = rand() % (poblacion->size-1) + 1;
        do {
            r2 = rand() % (poblacion->size-1) + 1;
        } while (r1 == r2);
        //el peor sera puesto a competir con el inmigrante
        Individual* individuo;
        if (poblacion->individual[r1].fitness > poblacion->individual[r2].fitness) {
            individuo = &(poblacion->individual[r1]);
        } else {
            individuo = &(poblacion->individual[r2]);
            
        }
        //si el inmigrante es mejor que el perdedor, el inmigrante lo remplaza
        if(this->inmigrantes->individual[indice].fitness < individuo->fitness){
            this->utilidad.copy_individual(&(this->inmigrantes->individual[indice]),individuo);
            indice++;
        }else{
            //sino se tira probabilidad, si gana la probabilidad se cambia igual
            if( probabilidad_quedarse_con_malo >= rand()){
                
                this->utilidad.copy_individual(&this->inmigrantes->individual[indice],individuo);
                indice++;
                
            }else{
                intentos++;
            }
            
            //si supera la cantidad de intetos queda descalificado
            if(intentos>=this->cantidad_de_intentos_tolerados){
                cantidad_descalificados++;
                intentos = 0;
                indice++;
            }
        }
    }
    
    
}
