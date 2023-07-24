#ifndef GRASP_H
#define GRASP_H

#include <limits>
#include <random>
#include <cstdlib>
#include <utility>

#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"
#include "../auxiliares/auxiliares.h"


class GRASP
{
	public:
        GRASP(); 
        GRASP(gapInstance &instancia);


        gapSolution greedyRandomized(); //encuentra la solucion con un greedy de manera randomizada
        gapSolution busquedaLocalGRASP(gapSolution solucion); //encuentra el optimo local

        void solve(int k); // encuentra el costo total de la asignacion y la asignacion en si
        void calculate();

        int getCostoFromGRASP() const; // devuelve el costo total de la asignacion
        gapSolution getSolution() const; // devuelve la asignacion vendedor - deposito

        double getTime() const; // devuelve el tiempo que tarda en ejecutarse k iteraciones del GRASP
        
	private:
        gapInstance _instance; // almacena la instancia
        gapSolution _solution; // almacena la asignacion
        int _costo_asignacion; // almacena el costo total de la asignacion
        double _tiempo; // almacena el tiempo de cómputo
        

};

#endif