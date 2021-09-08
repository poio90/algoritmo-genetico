
#include "../include/Servicio_inmigracion.hpp"
#include "../include/utils.hpp"

class Servicio_inmigracionTest {
public:

    //atributos para pruebas
    Problem p;
    Population *parents;
    



    //declaramos el constructor, porque requiere obligatoriamente que le pase un entero el original

    Servicio_inmigracionTest() {
        //inicializar atributos para pruebas
        

        this->p.load("./FSSPinstances/tai_20_5_1.txt");

        this->parents = (Population*) malloc(sizeof (Population));
        //se incializa con valores aleatorios, y se tendran 10 indivuos
        p.initialize_parents(10, this->parents);

        
        //llamar al metodo para testear
        this->eliminar_peores_y_migrar_Test();
    }

    void eliminar_peores_y_migrar_Test() {
        
        Utils u;


        int cant_inmigrantes=3;
        
        /**Instanciamos el servicio de inmigracion, con probabilidad de 50% de ser 
         * elegido el inmigante si es peor.
         * al ser cargado el inmigrante vacio, tendra todo 0 y su fitnes es de 0.
         * por lo que se deberia remplazar a todos. 
         * 
         */
        Servicio_inmigracion servicio(p, cant_inmigrantes, 0.5);
        
        //cambiar fitness
        this->cambiarFitness(servicio.get_lista_inmigrantes(),0.0);
        

       //al regresar parents tendra que tener un remplazo de this->size 
        //soluciones con fitness 0
        servicio.eliminar_peores_y_migrar(this->parents);
        
        
        //imprimimos
        u.print_population(this->parents);
        
        int cant = this->comprobarCantidadSolucionesConFitnessDado(this->parents,0.0);
        printf("\ncant=%d\n",cant);
        if(cant == cant_inmigrantes){
            printf("\n\nREMPLAZO EXITOSO\n\n");
        }

        

    }


private:

    int comprobarCantidadSolucionesConFitnessDado(Population *p, double fit) {
        int cant = 0;
        for (int i = 0; i < p->size; i++) {
            Individual* indi = &p->individual[i];
            if (indi->fitness == fit) {
                cant++;
                printf("welcome");
            }
            printf("\ncomparo indi=%f fit=%f\n",indi->fitness,fit);
        }
        return cant;
    }
    
    void cambiarFitness(Population *p, double newFit){
        
        for (int i = 0; i < p->size; i++) {
            Individual* indi = &p->individual[i];
            indi->fitness = newFit;
        }
    }
};



