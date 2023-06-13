#include "gap_instance.h"

gapInstance::gapInstance() {}

gapInstance::gapInstance(std::string filename) { //si inicializamos una instancia a partir de un archivo, llamamos al lector

    this->ReadFromFile(filename);
}

void gapInstance::ReadFromFile(std::string filename) {
    std::ifstream input_file(filename);

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
            this->costos[i][j] = std::stoi(line);
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