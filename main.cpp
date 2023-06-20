#include <string>
#include <iostream>
#include "gap_instance.h"
#include "greedy_local.h"
#include "worst_fit.h"

int main(int argc, char** argv) {
    std::vector<std::string> v = {"instances/gap/gap_a/a05100", "instances/gap/gap_b/b10200", "instances/gap/gap_e/e801600"};

    std::cout << "GREEDY" << std::endl;

    for(std::string filename : v){
        std::cout << "Reading file " << filename << std::endl;

        gapInstance instancia(filename); //inicializar instancia de GAP

        greedyLocal mediano(instancia); //inicializar greedyLocal
        
        mediano.solve(); //resolver con greedy

        gapSolution solution(instancia.m, instancia.n); 
        
        solution = mediano.getSolution();

        int distancia = mediano.getCosto();

        std::cout << "distancia total (+ penalizacion): " << distancia << std::endl;
    }

    std::cout << "WORST FIT" << std::endl;

    std::cout << std::endl;
    
    for(std::string filename : v){
        std::cout << "Reading file " << filename << std::endl;

        gapInstance instancia(filename); //inicializar instancia de GAP

        worstFit mediano(instancia); //inicializar greedyLocal
        
        mediano.solve(); //resolver con greedy

        gapSolution solution(instancia.m, instancia.n); 
        
        solution = mediano.getSolution();

        int distancia = mediano.getCosto();

        std::cout << "distancia total (+ penalizacion): " << distancia << std::endl;
    }
    // std::string filename = "instances/gap/gap_a/a05100";
    

    //std::cout << solution << std::endl;

    return 0;
}