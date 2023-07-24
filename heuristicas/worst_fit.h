#ifndef WORST_FIT_H
#define WORST_FIT_H

#include<tuple>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"
#include "../auxiliares/auxiliares.h"

class worstFit
{
	public:
        worstFit(); 
        worstFit(gapInstance &instancia);

        void solve(); // encuentra el costo total de la asignacion y la asignacion en si
        void calculate();
        int getCostoFromWorstFit() const; // devuelve el costo total de la asignacion
        gapSolution getSolution() const; // devuelve la asignacion vendedor - deposito
        double getTime() const; // devuelve el tiempo que tarda la asignación
        
	private:
        gapInstance _instance; // almacena la instancia
        gapSolution _solution; // almacena la asignacion
        int _costo_asignacion; // almacena el costo total de la asignacion
        double _tiempo; // almacena el tiempo de cómputo
        


};

#endif