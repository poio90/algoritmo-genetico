#include "../include/selector.hpp"

Selector::Selector(int n){
    switch(n){
        case 0: operadors = &Selector::b_tournament;
                break;
        case 1: operadors = &Selector::roulette;
                break;
        case 2: operadors = &Selector::sus;
        // case 2: operadors = &Selector::best_individuals;
        //         break;
        default: break;
    }
}

void Selector::select(Population *parents, Population *offprings){
    (this->*operadors)(parents, offprings);
}

void Selector::b_tournament(Population *parents, Population *offprings){
    Utils u;
    int r1 = 0;
    int r2 = 0;
    for(int i=0; i<offprings->size; i++){
        r1 = rand() % parents->size;
        do{
            r2 = rand() % parents->size;
        }while(r1 == r2);

        if(parents->individual[r1].fitness < parents->individual[r2].fitness){
            u.copy_individual(&(parents->individual[r1]), &(offprings->individual[i]));
        }
        else{
            u.copy_individual(&(parents->individual[r2]), &(offprings->individual[i]));
        }
    }
}

double* Selector::asign_probability(Population *population){
    double global_fitness = 0;
    int size = population->size;
    double previous_fitness = 0.0;
    double *relative_fitness = (double*)calloc(size, sizeof(double));

    for (int i=0; i<size;i++){
        if(population->individual[i].fitness != 0){
            relative_fitness[i] += 1 / (double)population->individual[i].fitness;
        }
        global_fitness += relative_fitness[i];
    }

    for (int i=0;i<size;i++)
	{
		relative_fitness[i] = (relative_fitness[i] / global_fitness) + previous_fitness;
		previous_fitness = relative_fitness[i];
	}
    return relative_fitness;
}

void Selector::roulette(Population *parents, Population *offprings){
    Utils u;
    double r = 0.0;
	int i = 0;
    double *relative_fitness;
    relative_fitness = asign_probability(parents);

    for(int j=0; j<offprings->size; j++){
        r = u.randd(0, 1);
        while (r > relative_fitness[++i]);
        //tomo i-1 porque al salir del bucle i queda pasado 1 unidad
        u.copy_individual(&(parents->individual[i-1]), &(offprings->individual[j]));
        i=0;
    }
    free(relative_fitness);
}

void Selector::sus(Population *parents, Population *offprings){
    Utils u;
    double spread = 1.0/parents->size;
    double offset = 0.0;
	int i = 0;
    int j = 0;
    double *relative_fitness;
    relative_fitness = asign_probability(parents);

    offset = u.randd(0, 1);

    while(j<parents->size){
        offset += spread;
        if(offset > 1.0) offset -= 1.0;
        while (offset > relative_fitness[++i]);
        u.copy_individual(&(parents->individual[i-1]), &(offprings->individual[j++]));
        i=0;
    }

    free(relative_fitness);
}


//NO ESTA TESTEADO
void Selector::best_individuals(Population *parents, Population *offprings){
    Utils utils;
    int j=0;

    for(int i=0; i<parents->size; i++){
        if(parents[i].individual->fitness >= parents[i+1].individual->fitness){
            utils.copy_individual(parents[i].individual, offprings[j].individual);
            utils.copy_individual(parents[i+1].individual, parents[i].individual);
            utils.copy_individual(offprings[j].individual, parents[i+1].individual);
        }
        j++;
    }

}
