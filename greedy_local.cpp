#include<limits>
#include "greedy_local.h"

int dmax(int j, const std::vector<std::vector<int> >& demandas){
    int max = 0;
    for(int i=0;i<demandas.size();i++){
        if(demandas[i][j]>max){
            max = demandas[i][j];
        }
    }
    return max;
}
greedyLocal::greedyLocal(){}

greedyLocal::greedyLocal(gapInstance &instancia){
    this->_instance = instancia;
}

void greedyLocal::solve(){
    gapSolution solucion(this->_instance.m, this->_instance.n); //creo la instancia de solucion a partir del a instancia de asignacion
    std::vector<std::vector<int> > dist = this->_instance.costos;
    std::vector<std::vector<int> > demanda = this->_instance.demandas;
    std::vector<int> capacidad = this->_instance.capacidades;

    int dist_total = 0;
    int v = -1;
    int d = -1;
    
    int min_demand = std::numeric_limits<int>::max();

    //auto start = std::chrono::high_resolution_clock::now();
    
    for(int j=0; j<this->_instance.n; j++){
        for(int i=0; i<this->_instance.m; i++){
            if(dist[i][j]<min_demand  && capacidad[i]-demanda[i][j] >=0){
                v = j; 
                d = i;
                min_demand = dist[i][j];
            }
        }
        if (v != -1) {
            solucion.assign(v, d);
            capacidad[d] -= demanda[d][v];
            dist_total = dist[d][v];
        } 
        min_demand = std::numeric_limits<int>::max();
    }
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout <<"time "<< static_cast<double>(duration.count()) << std::endl;

    int penalizacion = 0;
    for(int i = 0; i<this->_instance.n; i++){
        if(solucion.get_assigned_depo(i) == -1){
            penalizacion += 3*dmax(i, demanda);
            dist_total += penalizacion;
            //std::cout << i << std::endl;
        }
    }

    this->_solution = solucion;
    this->_costo_asignacion = dist_total;
    // std::cout << "dist total: "<<dist_total << std::endl;
    // std::cout << "greedy vendedores" << std::endl  
} 
    
int greedyLocal::getCosto() const{
    return this->_costo_asignacion;
}

gapSolution greedyLocal::getSolution() const{
    return this->_solution;
}