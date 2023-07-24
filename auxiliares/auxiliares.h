#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <tuple>
#include <vector>
#include <utility>
#include <algorithm>
#include "../gap/gap_instance.h"
#include "../gap/gap_solution.h"
#include "../gap/gap_cost.h"
#include "../heuristicas/greedy_local.h"
#include "../heuristicas/worst_fit.h"
#include "../busq_locales/relocate_ls.h"
#include "../busq_locales/swap_ls.h"


int dmax(int j, const std::vector<std::vector<int>>& demandas); //función auxiliar de gapInstance

//definimos varias auxiliares a utilizar en el main, para no tener que realizar todos los cómputos relevantes a nuestra experimentación a mano, y para poder modularizar el código.

std::tuple<gapSolution, int, double> computarGreedy(gapInstance &instancia); //devuelve la solución de la heurística greedy, el costo de dicha asignación, y el tiempo que tarda en encontrarse

std::tuple<gapSolution, int, double> computarWorstFit(gapInstance &instancia); //devuelve la solución de la heurística worst fit, el costo de dicha asignación, y el tiempo que tarda en encontrarse

std::tuple<gapSolution, int, double> computarBI_Relocate(gapInstance &instancia, gapSolution solution); //devuelve la solución de aplicar el operador relocate hasta encontrar la mejor solución en el vecindario de la solución original, el costo de la nueva asignación, y el tiempo que tarda en encontrarse

std::tuple<gapSolution, int, double> computarBI_Swap(gapInstance &instancia, gapSolution solution); //devuelve la solución de aplicar el operador swap hasta encontrar la mejor solución en el vecindario de la solución original, el costo de la nueva asignación, y el tiempo que tarda en encontrarse


std::tuple<gapSolution, int, double>  vecindario_BI(gapInstance &instancia, gapSolution solution, std::vector<std::string> operadores); //devuelve la solución de aplicar un VND de BI comenzando con relocate. Es decir que aplica relocate hasta encontrar la mejor solución posible en ese vecindario. Luego vuelve a aplicar relocate para el vecindario de la nueva solución. Si ya no hay más que mejorar con relocate pasa a swap y repite el mismo procedimiento. También devuelve el costo de la nueva asignación, y el tiempo que tarda en encontrarse. 


#endif 