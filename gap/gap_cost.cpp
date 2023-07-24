#include "gap_cost.h"


costoAsignacion::costoAsignacion(){}

costoAsignacion::costoAsignacion(gapInstance &instancia, gapSolution &solucion){
    this->_instance = instancia;
    this->_solution = solucion;
}

void costoAsignacion::calculateCost(){
    this->_cost = 0;
    double temp = 0;
    for(int j=0; j<this->_instance.n; j++){
            int deposito_asignado = this->_solution.get_assigned_depo(j);
            temp += this->_instance.costos[deposito_asignado][j]/10.0; 
            //dividimos por 10, por la multiplicación en gapInstance
        }
    this->_cost = temp;
}
int costoAsignacion::getCost() const{
    return this->_cost;
}