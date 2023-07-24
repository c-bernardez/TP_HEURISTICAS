#ifndef RELOCATE_LS_H
#define RELOCATE_LS_H

#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"

class relocateSearch
{
    public:
    relocateSearch();
    relocateSearch(gapInstance &instancia, gapSolution &solucion);

    void calculateBI(); //calcula la mejor solución dentro de un vecindario de relocate
    gapSolution getBestImprovement() const;

    double getTime_BI() const;

    private:
    gapInstance _instance;
    gapSolution _solution;
    gapSolution _BI;
    double _tiempo_BI;
};

#endif