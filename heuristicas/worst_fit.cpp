#include <limits>
#include <chrono>
#include "worst_fit.h"


worstFit::worstFit(){}

worstFit::worstFit(gapInstance &instancia){
    this->_instance = instancia;
}

void worstFit::solve(){
    gapSolution solucion(this->_instance.m, this->_instance.n, this->_instance); //creo la instancia de solucion a partir del a instancia de asignacion
    std::vector<std::vector<int> > dist = this->_instance.costos;
    std::vector<std::vector<int> > demanda = this->_instance.demandas;
    std::vector<int> capacidad = this->_instance.capacidades;


    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < this->_instance.m; i++) { //para cada depósito, mientras quede capacidad, probamos asignarle todos los vendedores posibles, empezando por los de mayor distancia. la lógica detrás de esto se encuentra en el análisis
        int capacidad_remanente = capacidad[i];
        
        while (capacidad_remanente > 0) {
            int v = -1;
            int d = i;
            int min_dist = 0;
            
            for (int j = 0; j < this->_instance.n; j++) {
                if (solucion.get_assigned_depo(j) == -1 && capacidad_remanente >= demanda[i][j] && dist[i][j] > min_dist) {
                    v = j;
                    min_dist = dist[i][j];
                }
            }
            
            if (v != -1) { //sino quiere decir que no encontramos un vendedor a asignar (no entramos al if) y por ende cortamos el ciclo y seguimos para el siguiente depósito
                solucion.assign(v, d);
                capacidad_remanente -= demanda[d][v];
            } else {
                break; 
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    this->_tiempo = static_cast<double>(duration.count());

    this->_solution = solucion;
} 
    
void worstFit::calculate(){
    costoAsignacion c(this->_instance, this->_solution);
    c.calculateCost();
    this->_costo_asignacion = c.getCost();
}

int worstFit::getCostoFromWorstFit() const{
    return this->_costo_asignacion;
    
}

gapSolution worstFit::getSolution() const{
    return this->_solution;
}

double worstFit::getTime() const{
    return this->_tiempo;
}