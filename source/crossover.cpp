#include "../include/crossover.hpp"

Crossover::Crossover(int n){
    switch(n){
        case 0: operatorc = &Crossover::ox;
            break;
        case 1: operatorc = &Crossover::pmx;
            break;
        case 2: operatorc = &Crossover::cx;
            break;
        default: operatorc = &Crossover::ox;
            break;
        }
}

void Crossover::crossover(float pcrossover, Population *offprings){
    Utils u;
    int size = offprings->individual[0].solution.size;
    double r = 0.0;
    int i=0;

    while(i<offprings->size){
    
        r = u.randd(0,1);

        if(r<pcrossover){
            int crosspoint1 = rand() % size;
            int crosspoint2 = rand() % size;            
            
            do{
                crosspoint2 = rand() % size;
            }while(crosspoint2 == crosspoint1);

            if(crosspoint1 > crosspoint2){
                int aux_crosspoint = crosspoint2;
                crosspoint2 = crosspoint1;
                crosspoint1 = aux_crosspoint;
            }

            (this->*operatorc)(&(offprings->individual[i]), &(offprings->individual[i+1]), crosspoint1, crosspoint2);

        }
        i = i + 2;
    }
}

void Crossover::ox(Individual *individual1, Individual *individual2, int crosspoint1, int crosspoint2){
    Utils u;
    Individual aux_individual;
    int size = individual1->solution.size;
    aux_individual.solution.chromosome = (int*) calloc(size, sizeof(int));
    int m=0, n=0;
    u.copy_individual(individual1, &aux_individual);

    m = crosspoint2;
    n = crosspoint2;

    for(int j=0; j<size; j++){
        reorder(&(individual1->solution), individual2->solution.chromosome[j], crosspoint1, crosspoint2, &m);
    }

    for(int j=0; j<size; j++){
         reorder(&(individual2->solution), aux_individual.solution.chromosome[j], crosspoint1, crosspoint2, &n);
    }

    individual1->updated = 0;
    individual2->updated = 0;   

    free(aux_individual.solution.chromosome);
}

void Crossover::pmx(Individual *individual1, Individual *individual2, int crosspoint1, int crosspoint2){
    int aux = 0;

    mapping(&(individual1->solution), &(individual2->solution), crosspoint1, crosspoint2);
    mapping(&(individual2->solution), &(individual1->solution), crosspoint1, crosspoint2);

    for(int j=crosspoint1; j<crosspoint2; j++){
        aux = individual1->solution.chromosome[j];
        individual1->solution.chromosome[j] = individual2->solution.chromosome[j];
        individual2->solution.chromosome[j] = aux;
    }   

    individual1->updated = 0;
    individual2->updated = 0;   
}

void Crossover::cx(Individual *individual1, Individual *individual2, int crosspoint1, int crosspoint2){
    Utils u;
    int inicio = 0;
    list<int> pos;
    pos.push_back(inicio);

    while(individual2->solution.chromosome[pos.back()] != individual1->solution.chromosome[inicio]){
        for (int i=0; i<individual1->solution.size; i++){
            if(individual1->solution.chromosome[i] == individual2->solution.chromosome[pos.back()]){
                pos.push_back(i);
                break;
            }
        }
    }

    for(int j=0; j<individual2->solution.size; j++){
        if(!exist(pos, j)){
            u.interchange(&(individual1->solution.chromosome[j]), &(individual2->solution.chromosome[j]));
        }
    }

    individual1->updated = 0;
    individual2->updated = 0;   
}

bool Crossover::exist(Solution *s, int a, int p1, int p2){
    bool exist = false;
    for(int i=p1; i<p2; i++){
        if(s->chromosome[i] == a){
            exist = true;
            break;
        }
    }
    return exist;
}

bool Crossover::exist(list<int> l, int a){
    bool exist = false;
    list<int>::iterator it = l.begin();
    while(it != l.end()){
        if(a == *it){
            exist = true;
            break;
        }
        it++;
    }
    return exist;
}

void Crossover::reorder(Solution *solution, int element, int p1, int p2, int *i){
    int m = *i;
    if(!exist(solution, element, p1, p2)){
        if((m<p1 || m>=p2) && m<solution->size){
            solution->chromosome[m] = element;
            m++;
        }
        if(m == solution->size){
            m = 0;
        }
        if(m == p1){
            m = p2;
        }
    }
    *i = m;
}

void Crossover::mapping(Solution *s1, Solution *s2, int p1, int p2){
    int i = 0;
    int j = p1;
    while(i<s1->size){
        if(i<p1 || i>=p2){
            while(j<p2){        
                if(s1->chromosome[i] == s2->chromosome[j]){
                    s1->chromosome[i] = s1->chromosome[j];
                    j = p1;
                }
                else{
                    j++;
                }
            }
            j = p1;
            i++;
        }
        else{
            i = p2;
        }
    }
}
