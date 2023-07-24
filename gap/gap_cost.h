#ifndef GAP_COST_H
#define GAP_COST_H

#include "gap_instance.h"
#include "gap_solution.h"

class costoAsignacion{

    public:
    costoAsignacion();
    costoAsignacion(gapInstance &instancia, gapSolution &solution);

    void calculateCost(); //obtiene el costo de una asignación (distancia total recorrida por cada vendedor hasta su depósito asignado)
    int getCost() const; //devuelve el costo


    private:
    gapInstance _instance;
    gapSolution _solution;
    int _cost; //almacena el costo
};

#endif