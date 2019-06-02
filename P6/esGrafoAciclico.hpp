
#ifndef ES_GRAFO_ACICLICO_HPP
#define ES_GRAFO_ACICLICO_HPP

#include <vector>
#include "../Material/grafoPMC.h"
#include "../Material/alg_grafo_E-S.h"

/**
 * Dado que es más sencillo determinar que un grafo sea cíclico, a que
 * no lo sea, la llamada a "esGrafoAciclico()" devolverá el resultado opuesto
 * de la comprobación "esGrafoCiclico()".
 * 
 * En el momento en que encontramos un ciclo (más de un camino posible entre
 * nodo A y nodo B) ya sabemos que el grafo es cíclico, y detenemos la búsqueda.
 * 
 * Estos métodos solo funcionan para grafos (ponderados o no) NO dirigidos.
*/

template <typename T>
bool esGrafoAciclico(const GrafoP<T>& Gponderado)
{
    return !esGrafoCiclico(Gponderado);
}


template <typename T>
bool esGrafoCiclico(const GrafoP<T>& Gponderado)
{
    vector<bool> visitados(Gponderado.numVert(), false);
    return esGrafoCiclico(Gponderado, visitados, 0, 0);
}

template <typename T>
bool esGrafoCiclico(const GrafoP<T>& Gponderado, vector<bool>& visitados,
                    typename GrafoP<T>::vertice verticeActual, typename GrafoP<T>::vertice verticePadre)
{
    bool esCiclico;
    typename GrafoP<T>::vertice i;
    vector<T> verticesAdyacentes = Gponderado[verticeActual];


    visitados[verticeActual] = true;
    i = 0;
    esCiclico = false;

    while (i < verticesAdyacentes.size() && esCiclico == false)
    {
        // Si existe un camino hasta el vértice 'i'.
        if (verticesAdyacentes[i] != GrafoP<T>::INFINITO)
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
                esCiclico = esGrafoCiclico(Gponderado, visitados, i, verticeActual);
            }
        }
        i++;
    }
    return esCiclico;
}




#endif  //ES_GRAFO_ACICLICO_HPP