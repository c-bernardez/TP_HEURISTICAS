#include <limits>
#include "gap_instance.h"

#include "../auxiliares/auxiliares.h"

gapInstance::gapInstance() {}

gapInstance::gapInstance(std::string filename) { //si inicializamos una instancia a partir de un archivo, llamamos al lector

    this->ReadFromFile(filename); //llamamos al lector que computa el vector de capacidades, y las matrices demandas y costos

    //para manejar la penalización de vendedores no asignados a ningún depósito, creamos un nuevo depósito de capacidad infinita y costos 3*dmax (distancia máxima a recorrer por un vendedor j a algún depósito i)

    this->capacidades.push_back(INT_MAX); //fijamos capacidad "infinita" (trabajamos con entero, así que es INT_MAX)
    this->demandas.push_back(std::vector<int>(this->n,0)); //los elementos del vector de demandas para el último depósito pueden tener cualquier valor razonable, ya que la capacidad máxima es "infinita", pero por simplicidad los fijamos en cero

    std::vector<int> depo_penalizaciones; //sumamos el vector de costos para el último depósito
    int maximo = 0;
    for(int j=0; j<this->n; j++){
        depo_penalizaciones.push_back(3*dmax(j, this->costos));
    }

    this->costos.push_back(depo_penalizaciones);
    this->m += 1; //actualizamos m para considerar el nuevo depósito agregado
}

void gapInstance::ReadFromFile(std::string filename) {
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    // lee la cantidad de depositos m y vendedores n
    input_file >> this->m >> this->n;
    this->costos = std::vector<std::vector<int> >(this->m, std::vector<int>(this->n));
    this->demandas = std::vector<std::vector<int> >(this->m, std::vector<int>(this->n));
    this->capacidades = std::vector<int> (this->m);
    
    // leer y agregar costos
    for (int i = 0; i < this->m; i++) {
        for(int j=0; j<this->n; j++){
            std::string line;
            input_file >> line;
            this->costos[i][j] = std::stof(line)*10;
        }
    }

    // leer y agregar demandas
    for (int i = 0; i < this->m; i++) {
        for(int j=0; j<this->n; j++){
            std::string line;
            input_file >> line;
            this->demandas[i][j] = std::stoi(line);
        }
    }

    // leer y agregar capacidades
     for (int i = 0; i < this->m; i++) {
        std::string line;
        input_file >> line;
        this->capacidades[i] = std::stoi(line);
    }
}