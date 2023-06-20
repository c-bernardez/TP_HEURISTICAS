#ifndef HEURISTICA_1_H
#define HEURISTICA_1_H

#include<tuple>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include "gap_instance.h"
#include "gap_solution.h"

class greedyLocal
{
	public:
        greedyLocal(); 
        greedyLocal(gapInstance &instancia);

        void solve(); // encuentra el costo total de la asignacion y la asignacion en si
        int getCosto() const; // devuelve el costo total de la asignacion
        gapSolution getSolution() const; // devuelve la asignacion vendedor - deposito
        
	private:
        gapInstance _instance; // almacena la instancia
        gapSolution _solution; // almacena la asignacion
        int _costo_asignacion; // almacena el costo total de la asignacion
        


};

#endif