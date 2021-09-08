#include "../include/mutator.hpp"

Mutator::Mutator(int n){
  switch(n){
    case 0: operatorm = &Mutator::invert;
      break;
    case 1: operatorm = &Mutator::insert;
      break;
    case 2: operatorm = &Mutator::scramble;
      break;
    default: 
        throw std::runtime_error( "Se recibio un numero no soportado= "+std::to_string(n));
      break;
  }
}

void Mutator::mutate(float pmutate, Population *offprings){    
    Utils u;    
    int size = offprings->individual[0].solution.size;
    double r = 0.0;
    int i=0, mutpoint1=0, mutpoint2=0;

    while(i<offprings->size){
      r = u.randd(0,1);
      if(r<pmutate){ 
        /**
         * En este caso, toma dos puntos aleatorios distintos, de el cromosoma de la solucion, y luego llama a mutar.
         * 
         * deberiamos ver si necesitamos tomar dos puntos aleatorios, o tenemos que modificar esta parte
         */
        mutpoint1 = rand() % size;

        do{
            mutpoint2 =  rand() % size;
        }while(mutpoint2 == mutpoint1);

        if(mutpoint1 > mutpoint2){
            int aux = mutpoint2;
            mutpoint2 = mutpoint1;
            mutpoint1 = aux;
        }

        (this->*operatorm)(&(offprings->individual[i].solution.chromosome[mutpoint1]), &(offprings->individual[i].solution.chromosome[mutpoint2]));            

        offprings->individual[i].updated = 0;
      }
      i++;
    }
}
/**
 * Dado dos punteros a enteros pa y pb, se llevara el valor donde apunta originalmente pb
 * al lado del valor donde apunta pa.
 * 
 * ej si el array es [1,2,3,4,5,6,7] pa apunta a 2 y pb apunta a 5, el array quedara:
 * [1,2,5,3,4,6,7]
 * 
 * @param pa
 * @param pb
 */
void Mutator::insert(int *pa, int *pb){
  int *indice;
  indice = pb - 1;
  while (pa != indice){
    interchange(indice, pb);
    pb = indice;
    indice--;
  }
}
/**
 * Implementacion de un swap
 * @param pa
 * @param pb
 */
void Mutator::interchange (int *pa, int *pb){
  int aux = 0;
  aux = *pa;
  *pa = *pb;
  *pb = aux;
}

/**
 * Dado dos punteros a enteros, siendo pa<=pb en direcciones
 * se invertiran sus valores ej: [1,2,3,4,5,6,7] pa apunta a 2, y pb a 5
 * resultado: [1,5,4,3,2,6,7]
 * 
 * @param pa
 * @param pb
 */
void Mutator::invert(int *pa, int *pb){
  while(pa < pb){
    interchange(pa, pb);
    pa++;
    pb--;
  }
}

/**
 * Dado dos punteros pa<=pb, se permutaran aleatoriamente los valores dentro del rango
 * 
 * @param pa
 * @param pb
 */
void Mutator::scramble(int *pa, int *pb){
    int* index=pa;
    int posicion;
    int size= pb-pa;
    while(index<=pb){
        
        posicion = utils.randi(0,size);
        
        interchange(pa, pa+posicion);
        
        index++;
    }
}