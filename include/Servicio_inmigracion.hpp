/* 
 * File:   Servicio_inmigracion.hpp
 * Author: braian
 *
 * Created on 14 de octubre de 2020, 09:05 PM
 */

#ifndef SERVICIO_INMIGRACION_HPP
#define SERVICIO_INMIGRACION_HPP
#include <random>
#include <memory>
#include "individual.hpp"
#include "problem.hpp"
#include "utils.hpp"
#include "selector.hpp"
using namespace std;

class Servicio_inmigracion {
public:
    /**
     * Constructor
     * 
     * @param Problem, para inicializar su poblacion interna
     * @param tamaño de la poblacion interna, debe ser <2
     * @param probabilidad de que un inmigante remplace a un individuo local mejor
     */
    Servicio_inmigracion(Problem&, int, double);
    
    virtual ~Servicio_inmigracion();

    //dado la poblacion, te elige los mejores y los copia a la lista de inmigracion
    void copiar_mejores(Population*);
    //dado la poblacion te quita los peores y te pone los inmigrantes
    void eliminar_peores_y_migrar(Population *);
    
    
    //retornar referencia inmigrantes, no se puede cambiar el contenido del puntero
    Population *get_lista_inmigrantes(){return this->inmigrantes;}
    /**
     * en eliminar_peores_y_migrar, se tira una probabilidad,
     * si el inmigrante falla en la probabilidad de remplazar mas alla de esta variable
     * entonces es descartado, y no califica para migrar.
     */
    int cantidad_de_intentos_tolerados= 5;
private:
    Servicio_inmigracion(const Servicio_inmigracion& orig); //no se permite copiar    
    Population* inmigrantes;
    double probabilidad_quedarse_con_inmigrante_malo;
    Utils utilidad;
    

};

#endif /* SERVICIO_INMIGRACION_HPP */

