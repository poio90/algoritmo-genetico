#include "../include/config.hpp"

void Configuration::read(string filename){
    std::ifstream file(filename);
    if (file.is_open()) {
        string line;
        int count = 0;
        cout << "begin configuration read....." << endl << endl;
        while (getline(file, line)) {
            stringstream sline (line);
            switch(count){
                case 0: sline >> epoch;
                        count++;
                        cout << "epoch: " << epoch << endl;
				        break;
				case 1: sline >> generator;
                        count++;
                        cout << "generator: " << generator << endl;
				        break;
				case 2: sline >> mu;
                        count++;
                        cout << "mu: " << mu << endl;
						break;
				case 3: sline >> lambda;
                        count++;
                        cout << "lambda: " << lambda << endl;
				        break;
				case 4: sline >> pselection;
                        count++;
                        cout << "pselection: " << pselection << endl;
						break;
                case 5: sline >> npreplacement;                        
                        sline >> npselection;
                        count++;
                        cout << "npreplacement: " << npreplacement << endl;        
                        cout << "npselection: " << npselection << endl;
						break;
				case 6: sline >> crossover;
                        sline >> pcrossover;
                        count++;
                        cout << "crossover: " << crossover << endl;
                        cout << "pcrossover: " << pcrossover << endl;
				        break;
				case 7: sline >> mutation;
                        sline >> pmutation;
                        count++;
                        cout << "mutation: " << mutation << endl;
                        cout << "pmutation: " << pmutation << endl;
	                    break;
                case 8: sline >> intervalo_migraciones;
                        count++;
                        cout << "intervalo migraciones: " << intervalo_migraciones << endl;
	                    break;
                case 9: sline >> cantidad_inmigrantes;
                        count++;
                        cout << "cantidad inmigrantes: " << cantidad_inmigrantes << endl;
	                    break;
                case 10: sline >> probabilidad_quedarse_con_imigrante_malo;
                        count++;
                        cout << "probabilidad de quedarse con imigrante malo: " << probabilidad_quedarse_con_imigrante_malo << endl;
	                    break;
                case 11: sline >> FSSP_instance;
                        count++;
                        cout << "FSSP instance:" << FSSP_instance << endl;
	                    break;
			default: break;
            }
        }
        file.close();
        cout << endl;
        cout << ".....finish configuration read" << endl;
    }
    else{
        cout<<"<-----------------------Configuration File not found" << filename <<endl;
    }
}
