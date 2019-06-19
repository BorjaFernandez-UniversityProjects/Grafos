#ifndef ENCONTRAR_RECORRIDO_MINIMO_HPP
#define ENCONTRAR_RECORRIDO_MINIMO_HPP


#include "../Material/grafoPMC.h"
#include "../Material/alg_grafoPMC.h"
#include "../Material/matriz.h"
#include <vector>


/*  Solución al problema 3 de la segunda relación de problemas de Grafos    */



//Precondición:     la función recibe tres parámetros:
//                   - Grafo ponderado de la distancia entre ciudades
//                   - vector de tamaño n (número de vértices) que indica cuántos viajes
//                      (cargas) hay que realizar a cada ciudad
//                   - vértice del grafo que representa la capital, desde donde salen
//                      todos los viajes
//Postcondición:    devuelve la distancia total a recorrer para hacer todos los envíos
template <typename T>
T encontrarRecorridoMinimo(const GrafoP<T>& distanciaCiudades, const vector<int>& parteDiario,
                            typename GrafoP<T>::vertice capital)
{
    T distanciaTotal;
    matriz<T> matrizCostes;
    typename GrafoP<T>::vertice i;

    // En esta matriz tenemos la distancia mínima entre dos nodos cualesquiera, teniendo en cuenta
    // que el grafo es dirigido, y la distancia A->B no tiene por qué ser igual que B->A
    matrizCostes = Kruskall(distanciaCiudades);

    distanciaTotal = 0;
    i = 0;
    while (i < matrizCostes.dimension() && i != capital)
    {
        // Para cada ciudad calculamos el coste de ida y vuelta desde la capital, multiplicado
        // por la carga (número de envíos = número de camiones) a llevar a cada una.
        distanciaTotal += (matrizCostes[capital, i] + matrizCostes[i, capital]) * parteDiario[i];
        i++;
    }

    return distanciaTotal;
}


#endif  //ENCONTRAR_RECORRIDO_MINIMO_HPP