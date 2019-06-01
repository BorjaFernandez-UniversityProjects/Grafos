#ifndef ES_GRAFO_ACICLICO_HPP
#define ES_GRAFO_ACICLICO_HPP

#include <vector>
#include "../Material/grafoPMC.h"
#include "../Material/listaenla.h"

template <typename T>
bool esGrafoAciclico(const GrafoP<T>& GrafoP)
{
    vector<bool> visitados{GrafoP.numVert(), false};
    return !esGrafoAciclico(GrafoP, visitados, 0, -1);
}

template <typename T>
bool esGrafoCiclico(const GrafoP<T>& GrafoP, vector<bool>& visitados,
                    typename GrafoP<T>::vertice vertice, typename GrafoP<T>::vertice verticePadre)
{
    bool esCiclico;
    int i;
    vector<T> verticesAdyacentes = GrafoP[vertice];


    visitados[vertice] = true;
    i = 0;
    esCiclico = false;

    while (i < verticesAdyacentes.size() && esCiclico = false)
    {
        // Si existe un camino hasta el vértice 'i'.
        if (verticesAdyacentes[i] != 0)
        {
            // Si el vértice 'i' ya ha sido visitado.
            if (visitados[i] == true)
            {
                // Si el vértice 'i' NO es el padre del vértice actual.
                if (i != verticePadre)
                {
                    esCiclico = true;
                }
            }
            else
            {
                esCiclico = esGrafoAciclico(GrafoP, visitados, i, vertice);
            }
        }
        i++;
    }
}




#endif  //ES_GRAFO_ACICLICO_HPP