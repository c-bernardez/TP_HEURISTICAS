#ifndef GREEDY_LOCAL_H
#define GREEDY_LOCAL_H

#include<tuple>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"

class greedyLocal
{
	public:
        greedyLocal(); 
        greedyLocal(gapInstance &instancia);

        void solve(); // encuentra el costo total de la asignacion y la asignacion en si
        void calculate();
        int getCostoFromGreedy() const; // devuelve el costo total de la asignacion
        gapSolution getSolution() const; // devuelve la asignacion vendedor - deposito
        double getTime() const; // devuelve el tiempo que tarda en ejecutarse 
        
	private:
        gapInstance _instance; // almacena la instancia
        gapSolution _solution; // almacena la asignacion
        int _costo_asignacion; // almacena el costo total de la asignacion
        double _tiempo; // almacena el tiempo de cómputo
        


};

#endif