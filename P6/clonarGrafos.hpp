#ifndef CLONAR_GRAFOS_HPP
#define CLONAR_GRAFOS_HPP

#include "../Material/grafoPMC.h"

// Precondición:    la función recibe como parámetro la referencia a un grafo
//                   ponderado. Es irrelevante si el grafo es dirigido o no.
// Postcondición:   devuelve un grafo ponderado idéntico al recibido como
//                   parámetro.
template <typename T>
GrafoP<T> clonarGrafoP(const GrafoP<T>& Gponderado)
{
    typename GrafoP<T>::vertice i;
    size_t nVertices = Gponderado.numVert();
    GrafoP<T> Gauxiliar{nVertices};

    i = 0;
    while (i < nVertices)
    {
        Gauxiliar[i] = new vector<T>{Gponderado[i]};
        i++;
    }
    return Gauxiliar;
}

#endif  //CLONAR_GRAFOS_HPP