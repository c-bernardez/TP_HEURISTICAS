#ifndef SWAP_LS_H
#define SWAP_LS_H

#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"

class swapSearch
{
    public:
    swapSearch();
    swapSearch(gapInstance &instancia, gapSolution &solucion);

    void calculateBI(); //calcula la mejor solución dentro de un vecindario de swap
    gapSolution getBestImprovement() const;

    double getTime_BI() const;

    private:
    gapInstance _instance;
    gapSolution _solution;
    gapSolution _BI;
    double _tiempo_BI;
};

#endif