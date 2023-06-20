#include <limits>
#include <chrono>
#include "worst_fit.h"

int dmax_2(int j, const std::vector<std::vector<int> >& demandas){
    int max = 0;
    for(int i=0;i<demandas.size();i++){
        if(demandas[i][j]>max){
            max = demandas[i][j];
        }
    }
    return max;
}
worstFit::worstFit(){}

worstFit::worstFit(gapInstance &instancia){
    this->_instance = instancia;
}

void worstFit::solve(){
    gapSolution solucion(this->_instance.m, this->_instance.n); //creo la instancia de solucion a partir del a instancia de asignacion
    std::vector<std::vector<int> > dist = this->_instance.costos;
    std::vector<std::vector<int> > demanda = this->_instance.demandas;
    std::vector<int> capacidad = this->_instance.capacidades;

    int dist_total = 0;
    int v = -1;
    int d = -1;
    
    int min_demand = std::numeric_limits<int>::max();

    //auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < this->_instance.m; i++) {
        int capacidad_remanente = capacidad[i];
        
        while (capacidad_remanente > 0) {
            int v = -1;
            int d = -1;
            int min_demand = std::numeric_limits<int>::max();
            
            for (int j = 0; j < this->_instance.n; j++) {
                if (solucion.get_assigned_depo(j) == -1 && capacidad_remanente >= demanda[i][j] && dist[i][j] < min_demand) {
                    v = j;
                    d = i;
                    min_demand = dist[i][j];
                }
            }
            
            if (v != -1) {
                solucion.assign(v, d);
                capacidad_remanente -= demanda[d][v];
                dist_total += dist[d][v];
            } else {
                break; // No more vendors can fit in the deposit
            }
        }
    }
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout <<"time "<< static_cast<double>(duration.count()) << std::endl;

    int penalizacion = 0;
    for(int i = 0; i<this->_instance.n; i++){
        if(solucion.get_assigned_depo(i) == -1){
            penalizacion += 3*dmax_2(i, demanda);
            dist_total += penalizacion;
            //std::cout << i << std::endl;
        }
    }

    this->_solution = solucion;
    this->_costo_asignacion = dist_total;
    // std::cout << "dist total: "<<dist_total << std::endl;
    // std::cout << "greedy vendedores" << std::endl  
} 
    
int worstFit::getCosto() const{
    return this->_costo_asignacion;
}

gapSolution worstFit::getSolution() const{
    return this->_solution;
}