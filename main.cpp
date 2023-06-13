#include <string>
#include <iostream>
#include "gap_instance.h"


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    gapInstance instancia(filename); //inicializar instancia de GAP
    
    
    return 0;
}