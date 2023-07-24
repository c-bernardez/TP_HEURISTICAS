#include <limits>
#include <chrono>
#include "greedy_local.h"

greedyLocal::greedyLocal(){}

greedyLocal::greedyLocal(gapInstance &instancia){
    this->_instance = instancia;
}

void greedyLocal::solve(){
    gapSolution solucion(this->_instance.m, this->_instance.n, this->_instance); //creo la instancia de solucion a partir del a instancia de asignacion
    std::vector<std::vector<int> > dist = this->_instance.costos;
    std::vector<std::vector<int> > demanda = this->_instance.demandas;
    std::vector<int> capacidad = this->_instance.capacidades;

    int v;
    int d;
    
    int min_dist = INT_MAX;

    auto start = std::chrono::high_resolution_clock::now();
    
    for(int j=0; j<this->_instance.n; j++){ //para cada vendedor j encontramos un depósito i que cumpla tener la menor distancia posible y que la demanda no exceda la capacidad remanente (siempre va a suceder por la existencia del último depósito de capacidad infinita y distancia máxima seguro que menor a INT_MAX (min_dist))
    
        int v = j;
        int d = this->_instance.m-1;
        for(int i=0; i<this->_instance.m; i++){
            if(dist[i][j]<min_dist  && capacidad[i]-demanda[i][j] >= 0){
                v = j; 
                d = i;
                min_dist = dist[i][j];
            }
        }
        
        solucion.assign(v, d);
        capacidad[d] -= demanda[d][v]; //restamos de la capacidad remanente la demanda del vendedor v al depósito d
        min_dist = INT_MAX; //reseteamos la min_dist luego de asignar un vendedor
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    this->_tiempo = static_cast<double>(duration.count());

    this->_solution = solucion;
} 

void greedyLocal::calculate(){
    costoAsignacion c(this->_instance, this->_solution);
    c.calculateCost();
    this->_costo_asignacion = c.getCost();
}

int greedyLocal::getCostoFromGreedy() const{
    return this->_costo_asignacion;
    
}

gapSolution greedyLocal::getSolution() const{
    return this->_solution;
}

double greedyLocal::getTime() const{
    return this->_tiempo;
}