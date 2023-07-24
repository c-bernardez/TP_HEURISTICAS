#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

class gapInstance
{
	public:
        gapInstance(); 
        gapInstance(std::string filename);
        void ReadFromFile(std::string filename);
        
        
        int m; // numero de depositos
        int n; // numero de vendedores
        
        std::vector<std::vector<int> > costos; // costo de asignarle al deposito i el vendedor j (distancia a recorrer de j a i)
        std::vector<std::vector<int> > demandas; // recursos consumidos por asignarle al deposito i el vendedor j (demanda del vendedor j para el deposito i)

        std::vector<int> capacidades; // capacidad del deposito i
	
	private:

};

#endif