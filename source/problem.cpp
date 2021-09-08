#include "../include/problem.hpp"

Problem::Problem(Estadistica &e){
    this->estadistica = &e;
}

void Problem::load(string filename){
    ifstream file(filename);

    cout << "loading instance....." << endl << endl;
    if(file.is_open()){
        cout << filename << endl;
        file >> jsize;
        cout << "jsize: " << jsize << endl; //cantidad cromosomas = tamaño solucion = cantidad tareas
        file >> msize;
        cout << "msize: " << msize << endl; //cantidad maquina
        file >> upperBound;
        cout << "upperbound: " << upperBound << endl;//peor solucion encontrada hasta ahora (caso minimizacion)
        file >> lowerBound;
        cout << "lowerbound: " << lowerBound << endl;//mejor solucion encontrada hasta ahora (caso minimizacion)
        jobsTimes= new int*[msize];

        this->estadistica->set_upper_bound(upperBound);
        this->estadistica->set_lower_bound(lowerBound);

        best = (Individual*) malloc(sizeof(Individual));
        best->fitness = __DBL_MAX__;
        best->updated = 0;
        best->solution.size = jsize;
        best->solution.chromosome = (int*) calloc(jsize, sizeof(int));

        for(int i=0; i<msize; i++)
        {
            jobsTimes[i] = new int[jsize];
            for(int j=0; j<jsize; j++)
            {
                file >> jobsTimes[i][j];
                cout << jobsTimes[i][j] << "-";
            }
            cout << endl;
        }
        file.close();
        cout << endl;
        cout << ".....instance loaded" << endl;
    }
    else{
        cout<<"Instance File not found"<<filename<<endl;
    }
}

void Problem::initialize_parents(int psize, Population *population){
    Generator g;
    // Utils u;
    population->size = psize;
    population->individual = (Individual*)malloc(sizeof(Individual)*population->size);

    for(int i=0; i<population->size; i++){
        population->individual[i].updated = 0;
        population->individual[i].solution.size = jsize;
        population->individual[i].solution.chromosome = (int*)malloc(sizeof(int)*jsize);
        g.random(population->individual[i].solution);
        evaluate(&population->individual[i]);
        this->estadistica->set_best_init(population->individual[i].fitness);
        // u.print_individual(population->individual[i]);
    }
}

void Problem::initialize_population(int psize, Population *population){
    // Utils u;
    population->size = psize;
    this->estadistica->set_population_size(population->size);
    population->individual = (Individual*)malloc(sizeof(Individual)*population->size);
    population->individual->fitness = 0.0;

    for(int i=0; i<population->size; i++){
        population->individual[i].updated = 0;
        population->individual[i].solution.size = jsize;
        population->individual[i].solution.chromosome = (int*)calloc(jsize, sizeof(int));
        // u.print_individual_to_file(population->individual[i]);
    }
}

void Problem::delete_population(Population *population){
    for(int i=0; i<population->size; i++){
        free(population->individual[i].solution.chromosome);
    }
    free(population->individual);
}


void Problem::evaluate(Individual *individual){
    int i, j, k=0;
    int **tiempo = (int**) malloc(jsize*sizeof(int*));
    int **schedule = (int**) malloc(jsize*sizeof(int*));

	for(j=0; j<jsize; j++){
		tiempo[j] = (int*) calloc(msize, sizeof(int));
		schedule[j] = (int*) calloc(msize, sizeof(int));
	}
	for(i=0; i<msize; i++){
		for(j=0; j<jsize ; j++){
            k = individual->solution.chromosome[j];
    		schedule[j][i] = jobsTimes[i][k];

    		if(j==0 && i==0){
                tiempo[j][i] = schedule[j][i];
            }
    		else{
    			if(j>0 && i==0){
                    tiempo[j][i] = tiempo[j-1][i] + schedule[j][i];
                }
    			if(j>0 && i>0){
                    if(tiempo[j-1][i]>tiempo[j][i-1]){
                        tiempo[j][i] = tiempo[j-1][i] + schedule[j][i];
                    }
                    else{
                    tiempo[j][i] = tiempo[j][i-1] + schedule[j][i];
                    }
                }
    			if(j==0 && i>0){
                    tiempo[j][i] = tiempo[j][i-1] + schedule[j][i];
                }
    		}
		}
	}
	individual->fitness = tiempo[jsize -1][msize-1];
    individual->updated = 1;

    for(j=0; j<jsize; j++){
        free(schedule[j]);
		free(tiempo[j]);
	}
	free(tiempo);
	free(schedule);
}

void Problem::evaluate_population(Population *population){
    // Utils u;
    for(int i=0; i<population->size; i++){
        if(population->individual[i].updated == 0){            
            evaluate(&(population->individual[i]));
            this->estadistica->increment_total_eval();
            this->estadistica->set_best_values(&population->individual[i], i);
        }
        set_best_individual(&(population->individual[i]));
        // u.print_individual_to_file (population->individual[i]);
    }
}

void Problem::set_best_individual(Individual *individual){
    Utils u;
    //cout << "best->fitness: " << best->fitness << endl;
    if(individual->fitness < best->fitness){
        //cout << "individual->fitness: " << individual->fitness << endl;
        //cout << "best->fitness: " << best->fitness << endl;
        u.copy_individual(individual, best);        
    }
}

Individual* Problem::get_best(){
    return best;
}