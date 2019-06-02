#ifndef MATRIZ_COSTES_MINIMO_HPP
#define MATRIZ_COSTES_MINIMO_HPP


#include "../Material/alg_grafoPMC.h"
#include "../Material/grafoPMC.h"
#include "../Material/matriz.h"
#include <vector>


/**
 * Generalización del problema:
 * Encontrar la matriz de costes mínimos para un grafo con las siguientes
 * restricciones:
 *  - El grafo es dirigido.
 *  - Hay una serie de nodos que no pueden visitarse.
 *  - Hay una serie de aristas que no pueden recorrerse.
 *  - Todos los caminos deben pasar por un nodo concreto.
*/


// Precondición:    la función recibe cuatro parámetros:
//                  - La referencia a un grafo ponderado.
//                  - Un vector de vértices qe contiene todos aquellos vértices
//                      que no sean visitables.
//                  - Un vector de aristas que contiene todas aquellas aristas
//                      que no sean navegables.
//                  - El vértice central por el que deben pasar todos los caminos.
template <typename T>
matriz<T> matrizCostesMinimos(const GrafoP<T>& Gponderado,
                            const vector<typename GrafoP<T>::vertice>& verticesBloqueados,
                            const vector<typename GrafoP<T>::arista>& aristasBloqueadas,
                            typename GrafoP<T>::vertice nodoCentral)
{
    matriz<T> matrizCostes;
    GrafoP<T> grafoAuxiliar;

    grafoAuxiliar = clonarGrafoP(Gponderado);

    eliminarAristas(grafoAuxiliar, aristasBloqueadas);
    aislarVertices(grafoAuxiliar, verticesBloqueados);
    matrizCostes = matrizCostesMinimos(grafoAuxiliar);
    incluirNodoEnCaminos(matrizCostes, nodoCentral);

    return matrizCostes;
}

// Precondición:    la función recibe como parámetro una matriz de costes que representa
//                   el coste mínimo de ir desde un vértice cualquiera A a otro B de
//                   de un grafo ponderado.
//                  También recibe un vértice del grafo por el que se desea que se
//                   deba pasar en todos los caminos.
// Postcondición:   modifica la matriz de costes de forma que todos los caminos posibles
//                   a hacer en el grafo pasan por el vértice indicado.
template <typename T>
void incluirNodoEnCaminos(matriz<T>& matrizCostes, typename GrafoP<T>::vertice nodoCentral)
{
    typename GrafoP<T>::vertice i;
    typename GrafoP<T>::vertice j;

    i = 0;
    while (i < matrizCostes.dimension())
    {
        j = 0;
        while (j < matrizCostes.dimension())
        {
            // Sustituimos el coste de viajar entre un nodo y otro por el coste entre viajar
            // del primero al nodo central, y del nodo central al segundo.
            matrizCostes[i][j] = matrizCostes[i][nodoCentral] + matrizCostes[nodoCentral][j];
            j++;
        }
        i++;
    }
}

// Precondición:    la función recibe como parámetro la referencia a un grafo
//                   ponderado, y un vector de vértices a aislar del grafo.
// Postcondición:   modifica el grafo de tal manera que aisla los vértices
//                   indicados del grafo, haciendo el coste de todo camino
//                   hacia ellos infinito.
template <typename T>
void aislarVertices(GrafoP<T>& Gponderado, const vector<typename GrafoP<T>::vertice>& vertices)
{
    size_t j;
    typename GrafoP<T>::vertice i;
    typename GrafoP<T>::vertice verticeBloqueado;

    i = 0;
    while (i < Gponderado.numVert())
    {
        j = 0;
        while (j < vertices.size())
        {
            verticeBloqueado = vertices[j];
            Gponderado[i][verticeBloqueado] = GrafoP<T>::INFINITO;
            j++;
        }
        i++;
    }
}

// Precondición:    la función recibe como parámetro la referencia a un grafo
//                   ponderado, y un vector de aristas a eliminar del grafo.
// Postcondición:   modifica el grafo de tal manera que "elimina" las aristas
//                   indicadas del grafo, haciendo su coste infinito.
template <typename T>
void eliminarAristas(GrafoP<T>& Gponderado, const vector<typename GrafoP<T>::arista>& aristas)
{
    size_t i;
    typename GrafoP<T>::vertice verticeOrigen;
    typename GrafoP<T>::vertice verticeDestino;

    i = 0;
    while (i < aristas.size())
    {
        verticeOrigen = aristas[i].orig;
        verticeDestino = aristas[i].dest;
        Gponderado[verticeOrigen][verticeDestino] = GrafoP<T>::INFINITO;
        i++;
    }
}

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

// Precondición:    la función recibe como parámetro la referencia a un grafo
//                   ponderado. Es irrelevante si el grafo es dirigido o no.
// Postcondición:   devuelve una matriz<T> con el coste mínimo entre los
//                   vértices del grafo.
template <typename T>
matriz<T> matrizCostesMinimos(const GrafoP<T>& Gponderado)
{
    typename GrafoP<T>::vertice i;
    size_t nVertices = Gponderado.numVert();
    matriz<T> matrizCostes{nVertices};
    vector<typename GrafoP<T>::vertice> camino{nVertices};

    i = 0;
    while (i != nVertices)
    {
        matrizCostes[i] = Dijkstra(Gponderado, i, camino);
        i++;
    }

    return matrizCostes;
}

#endif  //MATRIZ_COSTES_MINIMO