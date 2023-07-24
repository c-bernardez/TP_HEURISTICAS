#include "auxiliares.h"

int dmax(int j, const std::vector<std::vector<int>>& v) {
    //como en gapInstance definimos un nuevo depósito de penalización para los vendedores que no pueden ser asignados, utilizamos dmax para encontrar la distancia máxima que podría recorrer un vendedor si fuera asignado a su depósito más lejano
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i][j] > max) {
            max = v[i][j];
        }
    }
    return max;
}


std::tuple<gapSolution, int, double> computarGreedy(gapInstance &instancia){
    greedyLocal solver(instancia); 
    solver.solve(); 

    gapSolution solution(instancia.m, instancia.n, instancia); 
    solution = solver.getSolution();

    solver.calculate();

    int distancia_recorrida = solver.getCostoFromGreedy();
    double tiempo = solver.getTime();

    std::tuple<gapSolution, int, double> res (solution, distancia_recorrida, tiempo);      
    return res;
}


std::tuple<gapSolution, int, double> computarWorstFit(gapInstance &instancia){
    worstFit solver(instancia); 
    solver.solve(); 

    gapSolution solution(instancia.m, instancia.n, instancia); 
    solution = solver.getSolution();

    solver.calculate();

    int distancia_recorrida = solver.getCostoFromWorstFit();
    double tiempo = solver.getTime();

    std::tuple<gapSolution, int, double> res (solution, distancia_recorrida, tiempo);      
    return res;
}


std::tuple<gapSolution, int, double> computarBI_Relocate(gapInstance &instancia, gapSolution solution){
    relocateSearch busqueda(instancia, solution);

    busqueda.calculateBI();
    gapSolution BI = busqueda.getBestImprovement();

    costoAsignacion BI_costo(instancia, BI);
    BI_costo.calculateCost();
    int BI_distancia = BI_costo.getCost();

    int BI_tiempo = busqueda.getTime_BI();

    std::tuple<gapSolution, int, double>  res(BI, BI_distancia, BI_tiempo); 
    return res;
}


std::tuple<gapSolution, int, double> computarBI_Swap(gapInstance &instancia, gapSolution solution){
    swapSearch busqueda(instancia, solution);

    busqueda.calculateBI();
    gapSolution BI = busqueda.getBestImprovement();

    costoAsignacion BI_costo(instancia, BI);
    BI_costo.calculateCost();
    int BI_distancia = BI_costo.getCost();

    double BI_tiempo = busqueda.getTime_BI();

    std::tuple<gapSolution, int, double> res(BI, BI_distancia, BI_tiempo);
 
    return res;
}

std::tuple<gapSolution, int, double> vecindario_BI(gapInstance &instancia, gapSolution solution, std::vector<std::string> operadores){
    gapSolution mejor_solucion = solution; //definimos como mejor_solucion a la solucion ya encontrada, en primera instancia
    costoAsignacion mejor(instancia, mejor_solucion); 
    mejor.calculateCost(); //encontramos su costo
    int mejor_costo = mejor.getCost();
    int costo_actual;
    double tiempo;

    int i=0;
    while(i<operadores.size()){
        if (operadores[i] == "relocate") {
            std::tuple<gapSolution, int, double> relocate_BI_sol = computarBI_Relocate(instancia, mejor_solucion); //computamos el Best Improvement con relocate
            gapSolution solucion_actual = std::get<0>(relocate_BI_sol); //obtenemos la solución
            costo_actual = std::get<1>(relocate_BI_sol); //obtenemos el costo (distancia)
            tiempo += std::get<2>(relocate_BI_sol); //obtenemos el tiempo gastado en ejecución

            if (costo_actual < mejor_costo) { //si la solución encontrada es mejor (si no lo era computarBI_Relocate devuelve la original, porque getBestImprovement lo hace), se actualiza el nuevo costo y la nueva solución. De esta manaera en la próxima iteración se puede calcular el vecindario de esta nueva solución
                mejor_solucion = solucion_actual;
                mejor_costo = costo_actual;
            }
            else {
               i++; //si relocate ya no puede encontrar una mejor opción, se pasa al siguiente operador en la lista
            }
        }

        else if (operadores[i] == "swap") {
            std::tuple<gapSolution, int, double>swap_BI_sol = computarBI_Swap(instancia, mejor_solucion);
            gapSolution solucion_actual = std::get<0>(swap_BI_sol);
            costo_actual = std::get<1>(swap_BI_sol);
            tiempo += std::get<2>(swap_BI_sol);

            if (costo_actual < mejor_costo) {
                mejor_solucion = solucion_actual;
                mejor_costo = costo_actual;
                
            } 
            else {
                i++; //si swap ya no encuentra mejor opción,  se pasa al siguiente operador en la lista
            }
        } 
    }
    std::tuple<gapSolution, int, double> res(mejor_solucion, mejor_costo, tiempo); 
    return res;
}

    