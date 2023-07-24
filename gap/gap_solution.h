#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include "gap_instance.h"

class gapSolution
{
	public:
        gapSolution();
        gapSolution(int m, int n, gapInstance &instance);

        friend std::ostream& operator<<(std::ostream& os, const gapSolution& solution);

        int getN() const; //devuelve _n, cantidad de vendedores

        bool is_vend_assigned(int n) const; // devuelve true si el vendedor fue asignado a algun deposito

        void assign(int vend, int depo); // asigna a un vendedor a su deposito correspondiente (modificando _depo_assignment y _vendedor_assignment)

        void remove(int vend, int depo); // remueve al vendedor vend de su viejo depósito depo (modificando _depo_assignment)

        std::vector<int> get_capacidades() const; // devuelve el vector de capacidades remanentes

  

        std::vector<int> get_assigned_vends(int m) const; // devuelve los vendedores asignados al deposito m
        int get_assigned_depo(int n) const; // devuelve el deposito al que se asignó el vendedor n

        
	private:
        int _n; //cantidad de vendedores
        gapInstance _instance;
        std::vector<std::vector<int> > _depo_assignment; // para cada deposito 0,...,m guarda los vendedores asignados - quisimos quitar este vector de vectores, pero no corría en linux y no creimos que fuera a mejorar siginificativamente como para seguir intentando encontrar el error
        std::vector<int> _vendedor_assignment; // para cada vendedor 0,...,n guarda el deposito al que fue asignado 
        std::vector<int> _capacidades_remanentes;
        
};

#endif