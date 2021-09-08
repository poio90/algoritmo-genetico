#include "../include/estadistica.hpp"

Estadistica::Estadistica() {
    


    this->population_size = 0;
    this->lower_bound = 0.0;
    this->upper_bound = 0.0;

    //estadisticas de fitness
    this->avg_fit = 0.0;
    this->avg_init_fit = 0.0;
    this->best_init = __DBL_MAX__;
    this->best_fit = __DBL_MAX__;
    this->total_fit = 0.0;
    this->_gap = 0.0;
    this->_agap = 0.0;

    //estadisticas de iteraciones
    this->best_i = 0;
    this->total_i = 0;
    this->pos_best_sol = 0;


    //estaditicas de evaluaciones
    this->total_eval = 0;
    this->best_eval = 0;


}

void Estadistica::set_avg_fit() {
    avg_fit = total_fit / total_eval;
}

void Estadistica::set_avg_init_fit() {
    avg_init_fit = total_fit / population_size;
}

void Estadistica::set_best_init(double fitness) {
    if (fitness < best_init) {
        best_init = fitness;
    }
}

void Estadistica::set_total_fit(double fitness) {
    total_fit += fitness;
}

void Estadistica::set_best_values(Individual *i, int j) {
    if (i->fitness < best_fit) {
        best_fit = i->fitness;
        best_i = total_i;
        this->set_final_time();
        best_time = get_time();
        pos_best_sol = j;
        best_eval = total_eval;
    }
    set_total_fit(i->fitness);
    set_avg_fit();
}

void Estadistica::increment_total_i() {
    total_i++;
}

void Estadistica::increment_total_eval() {
    total_eval++;
}

void Estadistica::set_population_size(int psize) {
    population_size = psize;
}

void Estadistica::set_upper_bound(double fitness) {
    upper_bound = fitness;
}

void Estadistica::set_lower_bound(double fitness) {
    lower_bound = fitness;
}

void Estadistica::set_start_time() {
    this->start_time = chrono::system_clock::now();
}

void Estadistica::set_final_time() {
    this->final_time = std::chrono::system_clock::now();
}

float Estadistica::get_time() {
    
    std::chrono::duration<float,std::milli> duration = this->final_time - this->start_time;
    return duration.count();
}

void Estadistica::gap() {
    _gap = (best_fit - upper_bound) / upper_bound;
}

void Estadistica::agap() {
    _agap = (avg_fit - upper_bound) / upper_bound;
}

int Estadistica::get_total_i() {
    return total_i;
}

int Estadistica::get_total_eval() {
    return total_eval;
}

double Estadistica::get_avg_fit() {
    return avg_fit;
}

double Estadistica::get_total_fit() {
    return total_fit;
}

void Estadistica::setNombreArchivo(string nombre){
    this->nombreArchivo = nombre;
}

void Estadistica::partial_sumarize() {
    ofstream info("DatosCSV/"+this->nombreArchivo);
    info << "# tamaño poblacion;#iteraciones;#evaluaciones;#;fitness promedio;mejor fitness;tiempo transcurrido" << endl;
    info << population_size << ";" << total_i << ";" << total_eval << ";" << avg_fit << ";" << best_fit << ";" << get_time() << endl;
    info.close();
}

void Estadistica::sumarize(int ID_HILO) {
    ofstream info("DatosCSV/"+this->nombreArchivo, ios::app);
    gap();
    agap();
    info <<ID_HILO<<","<< population_size << "," << total_i <<"," <<total_eval << "," << avg_fit << "," << best_fit << "," << _gap << "," << _agap << "," << best_i << "," << best_time << "," << get_time() << endl;
    info.close();
}

void Estadistica::header(int ID_HILO){
    
    fstream file;
    file.open("DatosCSV/"+this->nombreArchivo, ios_base::out | ios_base::in);
    
    if(file.is_open()){
       //el archivo existe 
        file.close();
    }else{
        file.close();
        ofstream infops("DatosCSV/"+this->nombreArchivo, ios::app);
        infops << "#ID,#population_size,#total_iteraciones,#total_evaluaciones,#average_fit,best_fit,gap,average gap,#iteracion_mejor_solucion,#tiempo_mejor_solucion(ms),tiempo transcurrido" << endl;
        infops.close();
    }
    
    
}
