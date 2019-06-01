#ifndef PSEUDOCENTRO_HPP
#define PSEUDOCENTRO_HPP



#include <iostream>
#include <vector>
#include <list>
#include "../Material/alg_grafoPMC.h"
#include "../Material/grafoPMC.h"


template <typename T>
typename GrafoP<T>::vertice pseudocentro(const typename GrafoP<T>& GrafoP){

    int i;
    vertice verticeMinimo;
    typename GrafoP<tCoste>::tCoste minimo, minimoTemp;
    List<tCoste> vectorCosteTemp{GrafoP.numVert()};

    minimo = std::numeric_limits<tCoste>::max();

    for(i = 0; i < vectorCosteTemp.size(); i++){

        vectorCosteTemp = Dijkstra(GrafoP, i, vectorCamino);
        minimoTemp = diametroTemporal(vectorCosteTemp);

        if(minimoTemp < minimo){
            verticeMinimo = i;
            minimo = minimoTemp;
        }
    }
    
    return verticeMinimo;
}

template <typename T>
typename GrafoP<T>::tCoste diametro(const typename GrafoP<T>& GrafoP){

    int i;
    tCoste minimo, minimoTemp;
    List<tCoste> vectorCosteTemp{GrafoP.numVert()};

    minimo = std::numeric_limits<tCoste>::max();

    for(i = 0; i < GrafoP.numVert(); i++){
        
        vectorCosteTemp = Dijkstra(GrafoP, i, vectorCamino);
        minimoTemp = diametroTemporal(vectorCosteTemp);

        if(minimoTemp < minimo){
            minimo = minimoTemp;
        }
    }

    return minimo;
}

template <typename T>
typename GrafoP<T>::tCoste diametroTemporal(const typename vector<T>& costesVertice){

    int i;
    tCoste primerMayor, segundoMayor, mayorTemporal;

    primerMayor = 0;
    segundoMayor = 0;
    
    for(i = 0; i < costesVertice.size(); i++){
        mayorTemporal = costesVertice[i];

        if(mayorTemporal > segundoMayor){
            if(mayorTemporal > primerMayor){

                segundoMayor = primerMayor;         //Pasamos el mayor temporal al segundo puesto
                primerMayor = mayorTemporal;        //Ponemos en el primer puesto al nuevo mayor encontrado
            }
            else{
                segundoMayor = mayorTemporal;       //Ponemos en el segundo puesto al nuevo mayor encontrado
            }
        }
    }

    return primerMayor + segundoMayor;
}






#endif  //PSEUDOCENTRO_HPP