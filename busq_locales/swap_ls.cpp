#include "swap_ls.h"

swapSearch::swapSearch(){};

swapSearch::swapSearch(gapInstance &instancia, gapSolution &solucion){
    this->_instance = instancia;
    this->_solution = solucion;
}

void swapSearch::calculateBI(){

    int n = this->_instance.n;
    int m = this->_instance.m;

    gapSolution mejor_solucion = this->_solution; //calcula en una primera instancia la mejor_solucion como la solución encontrada hasta el momento (en nuestro trabajo será la encontrada con alguna de las heurísticas planteadas)
    costoAsignacion mejor(this->_instance, mejor_solucion);
    mejor.calculateCost();
    int mejor_costo = mejor.getCost();
    int costo_original = mejor_costo; //también el mejor_costo es en principio el costo de la solucion_original
    
    std::vector<int> capacidades_actuales = this->_solution.get_capacidades();

    auto start = std::chrono::high_resolution_clock::now();
    for(int j=0; j<n; j++){ //consideramos el primer vendedor
        for(int k=0; k<n; k++){ //consideramos el segundo vendedor
        
            int depo_primero = this->_solution.get_assigned_depo(j);
            int depo_segundo = this->_solution.get_assigned_depo(k);

            int demanda_k_al_primero = this->_instance.demandas[depo_primero][k];
            int demanda_k_al_segundo = this->_instance.demandas[depo_segundo][k];
            int demanda_j_al_primero = this->_instance.demandas[depo_primero][j];
            int demanda_j_al_segundo = this->_instance.demandas[depo_segundo][j];

            if(depo_primero !=  depo_segundo && capacidades_actuales[depo_primero] + demanda_j_al_primero - demanda_k_al_primero >=0 && capacidades_actuales[depo_segundo] + demanda_k_al_segundo - demanda_j_al_segundo >=0){ //chequeamos que no estemos swappeando dentro del mismo deposito, que asignar el k al depo del primero no se pase de la capacidad, y que asignar el j al depo del segundo no se pase de la capacidad

                int costo_j_actual = this->_instance.costos[depo_primero][j]; 
                int costo_k_actual = this->_instance.costos[depo_segundo][k];
                
                int costo_j_nuevo = this->_instance.costos[depo_segundo][j];
                int costo_k_nuevo = this->_instance.costos[depo_primero][k];

                int costo_actual = costo_original - costo_j_actual  - costo_k_actual + costo_j_nuevo +costo_k_nuevo;

                if(costo_actual < mejor_costo){
                    mejor_solucion = this->_solution;
                    mejor_solucion.assign(j, depo_segundo);
                    mejor_solucion.remove(j, depo_primero);
                    mejor_solucion.assign(k, depo_primero);
                    mejor_solucion.remove(k, depo_segundo);
                    
                    mejor_costo = costo_actual;
                }
            }
        
        }
        
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    this->_tiempo_BI = static_cast<double>(duration.count());

    this->_BI = mejor_solucion;
}

gapSolution swapSearch::getBestImprovement() const{
    return this->_BI;
}

   
double swapSearch::getTime_BI() const{
    return this->_tiempo_BI;
}
 