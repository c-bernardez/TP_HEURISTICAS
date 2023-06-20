#include "gap_solution.h"

gapSolution::gapSolution(){
}

gapSolution::gapSolution(int m, int n){
    this->_n = n;
    this->_vendedor_assignment = std::vector<int>(n, -1);
    this->_depo_assignment = std::vector<std::vector<int>>(m);
}

int gapSolution::getN () const{
    return this->_n;
}

void gapSolution::assign(int vend, int depo) {
    this->_depo_assignment[depo].push_back(vend);
    this->_vendedor_assignment[vend] = depo;
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

std::ostream& operator<<(std::ostream& os, const gapSolution& solution){
    //completar como el de taxi para que printee una asignacion
    for (int i = 0; i < solution.getN(); ++i) {
        os << "Vendor " << i << " assigned to Deposit " << solution.get_assigned_depo(i) << std::endl;
    }
    return os;
}

        
