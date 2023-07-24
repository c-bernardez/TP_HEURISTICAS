#include "grasp.h"


GRASP::GRASP(){}

GRASP::GRASP(gapInstance &instancia){
    this->_instance = instancia;
    // this->gen = std::mt19937(std::random_device{}());
    // this->dis = std::uniform_int_distribution<>(0, std::numeric_limits<int>::max());
}

void GRASP::solve(int k){
    std::srand(1); //seedeamos la semilla para poder elegir los depósitos más cercanos de manera aleatoria
    gapSolution mejor_solucion;
    int mejor_costo = INT_MAX;

    auto start = std::chrono::high_resolution_clock::now();
    while(k>0){ //hacemos k iteraciones 
        gapSolution solucion_actual = greedyRandomized(); 
        solucion_actual = busquedaLocalGRASP(solucion_actual); //aplicamos una búsqueda local para llegar a un óptimo local a partir de la solución randomizada
        
        costoAsignacion costo_temp(this->_instance, solucion_actual);
        costo_temp.calculateCost();
        int costo_actual = costo_temp.getCost(); //calculamos el costo de la solución óptima local
        

        if(costo_actual < mejor_costo){
            mejor_solucion = solucion_actual;
            mejor_costo = costo_actual; //si es mejor a la encontrada en una iteración anterior, la actualizamos
        }
        
        k--;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    this->_tiempo = static_cast<double>(duration.count());

    this->_solution = mejor_solucion;
} 

gapSolution GRASP::greedyRandomized(){
    
    gapSolution solucion(this->_instance.m, this->_instance.n, this->_instance); 
    std::vector<std::vector<int> > dist = this->_instance.costos;
    std::vector<std::vector<int> > demanda = this->_instance.demandas;
    std::vector<int> capacidad = this->_instance.capacidades;

    int v;
    int d;
    for(int j=0; j<this->_instance.n; j++){
        v = j;
        d = this->_instance.m-1;
        
        int rcl_size = this->_instance.m*0.4; //fijamos la lista de candidatos en 40% de la cantidad de depósitos
        std::vector<int> rcl_depositos;

        while(rcl_size > 0){
            int min_dist = INT_MAX;
            
            for(int i=0; i<this->_instance.m; i++){
                auto it = std::find(rcl_depositos.begin(), rcl_depositos.end(), i);
                if(dist[i][j]<min_dist  && capacidad[i]-demanda[i][j] >=0 && it == rcl_depositos.end()){
                    //verificamos que la distancia al depósito i sea menor a la encontrada antes, que la demanda del vendedor no se pase de la capacidad Y que no hayamos considerado este depósito con anticipación
                    v = j; 
                    d = i;
                    min_dist = dist[i][j];
                }
            }
            rcl_depositos.push_back(d); 
            rcl_size--;
        }
        int random_index = std::rand() % rcl_depositos.size(); //elegimos de manera "aleatoria" a un depósito random para cada vendedor
        d = rcl_depositos[random_index];
        solucion.assign(v, d);
        capacidad[d] -= demanda[d][v];
    }

    return solucion;
}

gapSolution GRASP::busquedaLocalGRASP(gapSolution solucion){
    std::tuple<gapSolution, int, double> BI = vecindario_BI(this->_instance, solucion, {"swap", "relocate"}); //aplicamos la busqueda local de un VND relocate-swap de Best Improvement (agota un vecindario antes de moverse a otro)
    return std::get<0>(BI);
}


void GRASP::calculate(){
    costoAsignacion c(this->_instance, this->_solution);
    c.calculateCost();
    this->_costo_asignacion = c.getCost();
}

int GRASP::getCostoFromGRASP() const{
    return this->_costo_asignacion;
    
}

gapSolution GRASP::getSolution() const{
    return this->_solution;
}

double GRASP::getTime() const{
    return this->_tiempo;
}