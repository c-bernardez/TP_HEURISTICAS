#include "gap_solution.h"

gapSolution::gapSolution(){
}

gapSolution::gapSolution(int m, int n, gapInstance &instance){
    this->_n = n;
    this->_instance = instance;
    this->_vendedor_assignment = std::vector<int>(n, -1); // el vector de _vendedor_assignment tiene n elementos para considerar la asignación de n vendedores a algún depóstio
    this->_depo_assignment = std::vector<std::vector<int>>(m); // la matriz de _depo_assignment considera un subvector de tamaño _m por cada depósito, donde cada uno puede tener asignado como mucho _n vendedores, pero puede ser menos.
    this->_capacidades_remanentes = this->_instance.capacidades;
}

int gapSolution::getN () const{
    return this->_n;
}

void gapSolution::assign(int vend, int depo) {
    this->_depo_assignment[depo].push_back(vend); 
    this->_vendedor_assignment[vend] = depo; \
    this->_capacidades_remanentes[depo] -= this->_instance.demandas[depo][vend];
}

void gapSolution::remove(int vend, int depo){
    auto it = std::find(this->_depo_assignment[depo].begin(), this->_depo_assignment[depo].end(), vend);
    this->_depo_assignment[depo].erase(it);
    this->_capacidades_remanentes[depo] += this->_instance.demandas[depo][vend];
}

std::vector<int> gapSolution::get_assigned_vends(int m) const{
    return this->_depo_assignment[m];
}

int gapSolution::get_assigned_depo(int n) const{
    return this->_vendedor_assignment[n];
}

bool gapSolution::is_vend_assigned(int n) const{
    return this->_vendedor_assignment[n] != -1;
}

std::vector<int> gapSolution::get_capacidades() const{
    return this->_capacidades_remanentes;
}


std::ostream& operator<<(std::ostream& os, const gapSolution& solution){
    for (int i = 0; i < solution.getN(); ++i) {
        os << "Vendor " << i << " assigned to Deposit " << solution.get_assigned_depo(i) << std::endl;
    }
    return os;
}

        
