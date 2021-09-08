#include "../include/utils.hpp"

int Utils::generate_point(int start, int end){
  int x = start + rand() % end;
  return x;
}

void Utils::interchange(int *pa, int *pb){
  int aux = 0;
  aux = *pa;
  *pa = *pb;
  *pb = aux;
}

void Utils::permute(Solution s){
  for(int i=0; i<s.size; i++){
    int j = generate_point(0, s.size);
    int k = generate_point(0, s.size);
    interchange(&s.chromosome[j], &s.chromosome[k]);
  }
}

void Utils::invert(int *pa, int *pb){
  while(pa < pb){
    interchange(pa, pb);
    pa++;
    pb--;
  }
}


void Utils::insert(int *pa, int *pb){
  int *indice;
  if(pa < pb){
    indice = pb - 1;
    while (pa != indice){
      interchange(indice, pb);
      pb = indice;
      indice--;
    }
  }
  else{
    indice = pb + 1;
    while (pa != pb){
      interchange(indice, pb);
      pb = indice;
      indice++;
    }
  }
}

int Utils::randi(int min, int max)
{
	double r = (double)rand()/double(RAND_MAX);

	r = r*(max-min) + min;

	return (int) r;
}

double Utils::randd(int min, int max)
{
	double r = (double)rand()/double(RAND_MAX);

	r = r*(max-min) + min;

	return r;
}

void Utils::copy_solution(Solution *s1, Solution *s2){
    //copia la solución s1 a la solución s2
    // if(!s2->chromosome){
    //     s2->chromosome = (int*)malloc(sizeof(int)*s1->size);
    // }
    for(int i=0; i<s1->size; i++){
        // cout << "s2->chromosome: " << s2->chromosome[i] << endl;
        // cout << "s1->chromosome: " << s1->chromosome[i] << endl;
        s2->chromosome[i] = s1->chromosome[i];        
    }
    //posible perdida de memoria, de suerte es tamaño fijo
    s2->size = s1->size;
}

void Utils::copy_individual(Individual *a, Individual *b){
    //copia el individuo a al individuo b.
    b->fitness = a->fitness;
    b->updated = a->updated;
    copy_solution(&(a->solution), &(b->solution));
}

void Utils::copy_population(Population *p1,Population *p2){
    //copia la población p1 a la población p2
    if(!p2->individual){
        p2->individual = (Individual*)malloc(sizeof(Individual)*p1->size);
    }
    for(int i=0; i<p1->size; i++){
        copy_individual(&(p1->individual[i]), &(p2->individual[i]));
    }
}

bool Utils::check_population(Population *p){
    bool check;
    for(int i=0; i<p->size; i++){
      check = check_individual(&(p->individual[i]));
    }
    return check;
}

bool Utils::check_individual(Individual *individual){
    bool check = true;
    int e;
    for(int i=0; i<individual->solution.size; i++){
        e = individual->solution.chromosome[i];
        for(int j=0; j<individual->solution.size; j++){
            if(e==individual->solution.chromosome[j] && i!=j){
                check = false;
            }
        }      
    }
    return check;
}

void Utils::print_population(Population *population){
    for(int i=0; i<population->size; i++){
        printf("<====================== printing individual (%d) ======================>", i);
        print_individual(population->individual[i]);
    }
}

void Utils::print_individual(Individual individual){
    printf("\n");
    printf("fitness: %f", individual.fitness);
    printf("\n");
    printf("updated: %d", individual.updated);
    printf("\n");
    printf("solution:\n");
    print_solution(individual.solution);
    printf("\n");
}

void Utils::print_fitness(double fitness){
    printf("fitness: %f", fitness);
}

void Utils::print_solution(Solution s){
    printf("<----------------------- printing solution ----------------------->");
    printf("\n");
    for(int i=0; i<s.size; i++){
        printf("%d-", s.chromosome[i]);
    }
    printf("\n");
    printf("<----------------------- ---------------- ----------------------->");
}

void Utils::print_individual_to_file(Individual individual){
    ofstream file;
    file.open("logs/log.txt", ios::app);

    file << "<====================== printing individual ======================> \n";
    file << "fitness: " << individual.fitness << "\n";
    file << "solution: \n";
    file.close();
    print_solution_to_file(individual.solution);
}

void Utils::print_solution_to_file(Solution s){
    ofstream file;
    file.open("logs/log.txt", ios::app);
    file << "<----------------------- printing solution ----------------------->\n";
    for(int i=0; i<s.size; i++){
        file << s.chromosome[i] << "-";;
    }
    file << "\n";
    file << "<----------------------- ---------------- -----------------------> \n";
    file.close();
}
