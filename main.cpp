#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "auxiliares/auxiliares.h"
#include "gap/gap_instance.h"
#include "metaheuristicas/grasp.h"

int main(int argc, char** argv) {
    std::vector<std::string> files = {
        "instances/gap/gap_a/a05100",
        "instances/gap/gap_a/a05200",
        "instances/gap/gap_a/a10100",
        "instances/gap/gap_a/a10200",
        "instances/gap/gap_a/a20100",
        "instances/gap/gap_a/a20200", 
        "instances/gap/gap_b/b05100", 
        "instances/gap/gap_b/b05200", 
        "instances/gap/gap_b/b10100",
        "instances/gap/gap_b/b10200",
        "instances/gap/gap_b/b20100",
        "instances/gap/gap_b/b20200",
        "instances/gap/gap_e/e05200",
        "instances/gap/gap_e/e15900",
        "instances/gap/gap_e/e10400",
        "instances/gap/gap_e/e60900",
        "instances/gap/gap_e/e401600",
        "instances/real/real_instance"
        }; //para analizar la distancia total encontrada con las heurísticas, y las mejoras que se pueden obtener mediante los operadores de búsqueda local elegimos computarlo sobre todas las instancias de gap_a, todas las de gap_b, la instancia real y 5 instancias representativas de gap_e. Esto porque las instancias de gap_e en muchos casos son demasiado grandes y durante la realización del trabajo y los códigos que fuimos probando concluimos que llevaría demasiado tiempo. Como mencionamos en el análisis, el tiempo de ejecución podría disminuirse pero nos vemos limitados en tiempo para conseguir esta mejora.

    std::ofstream outfile_1("analisis/greedy_analisis.csv");
    outfile_1 << "filename,dist_total,time_greedy,dist_relocate,time_relocate,dist_swap,time_swap" << std::endl; //csv para analizar el valor de la funcion objetivo con una heurística greedy, el resultado de aplicar un best improvement de operadores de búsqueda local relocate y swap, y el tiempo de ejecución de cada uno (en microsegundos)

    std::ofstream outfile_2("analisis/worstFit_analisis.csv");
    outfile_2 << "filename,dist_total,time_wf,dist_relocate,time_relocate,dist_swap,time_swap" << std::endl; //csv para analizar el valor de la funcion objetivo con una heurística worstfit, el resultado de aplicar un BI de relocate y swap, y el tiempo de ejecución de cada uno (en microsegundos)

    for(int i=0; i<files.size(); i++){
        gapInstance instancia(files[i]); //inicializamos una instancia para cada archivo
    
        greedyLocal greedy(instancia);
        greedy.solve(); //encontramos la solución greedy
        greedy.calculate(); //computamos el costo (distancia total de la asignación)
        int dist_total_greedy = greedy.getCostoFromGreedy();
        double time_greedy = greedy.getTime(); //obtenemos el tiempo que tardó en computarse la asignación
       
        std::tuple<gapSolution, int, double> relocate_greedy = vecindario_BI(instancia, greedy.getSolution(),{"relocate"}); //aplicamos el operador de relocate con criterio Best Improvement para la solución obtenida con la heurística greedy, hasta mínimo local
        int dist_relocate_greedy = std::get<1>(relocate_greedy);
        double time_relocate_greedy = std::get<2>(relocate_greedy);
       
        std::tuple<gapSolution, int, double> swap_greedy = vecindario_BI(instancia, greedy.getSolution(),{"swap"}); //aplicamos el operador de swap con criterio Best Improvement también para la misma heurística greedy, hasta mínimo local
        int dist_swap_greedy = std::get<1>(swap_greedy);
        double time_swap_greedy = std::get<2>(swap_greedy);

        outfile_1 << files[i] << "," << dist_total_greedy << "," << time_greedy << "," << dist_relocate_greedy<< ","  << time_relocate_greedy << "," << dist_swap_greedy << "," << time_swap_greedy <<std::endl;


        worstFit worstfit(instancia); 
        worstfit.solve(); //encontramos la solución worst fit
        worstfit.calculate(); //computamos el costo encontrado con esta heurística
        int dist_total_wf = worstfit.getCostoFromWorstFit();
        double time_wf = worstfit.getTime(); //obtenemos el tiempo que tardó en computarse la asignació

        std::tuple<gapSolution, int, double> relocate_wf = vecindario_BI(instancia, worstfit.getSolution(),{"relocate"}); //aplicamos el relocate con criterio Best Improvement para la solución obtenida con el método worst fit, hasta mínimo local
        int dist_relocate_wf = std::get<1>(relocate_wf);
        double time_relocate_wf = std::get<2>(relocate_wf);

        std::tuple<gapSolution, int, double> swap_wf = vecindario_BI(instancia, worstfit.getSolution(),{"swap"}); //aplicamos el swap con criterio Best Improvement para la solución obtenida con el método worst fit, hasta mínimo local
        int dist_swap_wf = std::get<1>(swap_wf);
        double time_swap_wf = std::get<2>(swap_wf);

        outfile_2 << files[i] << "," << dist_total_wf << "," << time_wf << "," << dist_relocate_wf<< ","  << time_relocate_wf<< "," << dist_swap_wf << "," << time_swap_wf<<std::endl;
    }

    std::vector<std::string> files_reducido = {
        "instances/gap/gap_a/a05100",
        "instances/gap/gap_b/b10200",
        "instances/gap/gap_e/e10400",
        "instances/real/real_instance"
        };
    
    std::ofstream outfile_3("analisis/grasp_analisis.csv");
    outfile_3 << "filename,k,dist_grasp,time_grasp" << std::endl;

    std::map<int, std::vector<int> > valores = {{0,{1,25,50,100}},{1,{1,5,10,25}},{2,{1,5,10}},{3,{1,5,10,20}}};

    for(int i=0; i<files_reducido.size(); i++){
        for(int k : valores[i]){
            gapInstance instancia(files_reducido[i]);

            GRASP grasp(instancia);
          
            grasp.solve(k);

            grasp.calculate();
            int dist_bi = grasp.getCostoFromGRASP();
            double time_bi = grasp.getTime();

            outfile_3 << files_reducido[i] << "," << k << "," << dist_bi << "," << time_bi << std::endl;
        }
        
    
    }

    return 0;
}