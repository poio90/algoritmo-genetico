#include "../include/replacer.hpp"

Replacer::Replacer(int a, int b){
    switch(a){
        case 0: operatorr = &Replacer::generational; 
                break;
        case 1: operatorr = &Replacer::mupluslambda;                
                break;
        default: break;
    }

    switch(b){
        case 0: operators = &Replacer::b_tournament;
                break;
        case 1: operators = &Replacer::roulette;
                break;
        default: break;
    }
}

void Replacer::replace(Population *parents, Population *offprings, Problem *p){
    (this->*operatorr)(parents, offprings, p);
}

void Replacer::select(Population *parents, Individual *offpring){
    (this->*operators)(parents, offpring);
}

void Replacer::generational(Population *parents, Population *offprings, Problem *p){
    Utils u;
    u.copy_individual(p->get_best(), &(parents->individual[0]));
    for(int i=1; i<parents->size; i++){
        select(offprings, &(parents->individual[i]));
    }    
}

void Replacer::mupluslambda(Population *parents, Population *offprings, Problem *p){
    Utils u;
    int size = parents->size;   
    int r = 0;
    Population *aux_pop = (Population*) malloc(sizeof(Population));

    p->initialize_population(size, aux_pop);  
    //asignar probabilidades
    u.copy_individual(p->get_best(), &(parents->individual[0]));
    for(int i=1; i<size; i++){
        r = rand() % (parents->size + offprings->size);
        if(r<size){
            select(parents, &(aux_pop->individual[i]));
        }
        else{
            select(offprings, &(aux_pop->individual[i]));
        }
    }
    u.copy_population(aux_pop,parents);

    for(int i=0; i<aux_pop->size; i++){
        free(aux_pop->individual[i].solution.chromosome);
    }
    free(aux_pop->individual);
    free(aux_pop);
}

double* Replacer::asign_probability(Population *population){
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

void Replacer::b_tournament(Population *poblation, Individual *individual){
    Utils u;
    int r1 = 0;
    int r2 = 0;
    r1 = rand() % poblation->size;
    do{
        r2 = rand() % poblation->size;
    }while(r1 == r2);

    if(poblation->individual[r1].fitness < poblation->individual[r2].fitness){
        u.copy_individual(&(poblation->individual[r1]), individual);
    }
    else{
        u.copy_individual(&(poblation->individual[r2]), individual);
    }
}

void Replacer::roulette(Population *poblation, Individual *individual){
    Utils u;
    double r = 0.0;
	int i = 0;
    double *relative_fitness;
    relative_fitness = asign_probability(poblation);

    r = u.randd(0, 1);
    while (r > relative_fitness[++i]);
    //tomo i-1 porque al salir del bucle i queda pasado 1 unidad
    u.copy_individual(&(poblation->individual[i-1]), individual);
    i=0;
    
    free(relative_fitness);
}
