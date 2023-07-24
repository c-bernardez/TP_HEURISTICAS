#include "relocate_ls.h"

relocateSearch::relocateSearch(){};

relocateSearch::relocateSearch(gapInstance &instancia, gapSolution &solucion){
    this->_instance = instancia;
    this->_solution = solucion;
}

void relocateSearch::calculateBI(){
    int n = this->_instance.n;
    int m = this->_instance.m;

    gapSolution mejor_solucion = this->_solution; //calcula en una primera instancia la mejor_solucion como la solución encontrada hasta el momento (en nuestro trabajo será la encontrada con alguna de las heurísticas planteadas)
    costoAsignacion mejor(this->_instance, mejor_solucion);
    mejor.calculateCost();
    int mejor_costo = mejor.getCost(); //también el mejor_costo es en principio el costo de la solucion_original

    int costo_original = mejor_costo;
    std::vector<int> capacidades_actuales = this->_solution.get_capacidades();
   

    auto start = std::chrono::high_resolution_clock::now();
    
    for(int j=0; j<n; j++){
        for(int i=0; i<m; i++){

            int depo_actual = this->_solution.get_assigned_depo(j);

            if(depo_actual != i && capacidades_actuales[i] - this->_instance.demandas[i][j] >= 0){
        
                int costo_actual = costo_original - this->_instance.costos[depo_actual][j] + this->_instance.costos[i][j];
                //el costo de la nueva solucion será el mismo que el de la solución original (porque se calcula el vecindario sobre ella) menos el costo de asignar el vendedor a su depósito antiguo más el costo de la nueva asignación

                if(costo_actual < mejor_costo){
                    mejor_solucion = this->_solution;
                    mejor_solucion.assign(j,i);
                    mejor_solucion.remove(j, depo_actual);
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

gapSolution relocateSearch::getBestImprovement() const{
    return this->_BI;
}


double relocateSearch::getTime_BI() const{
    return this->_tiempo_BI;
}




