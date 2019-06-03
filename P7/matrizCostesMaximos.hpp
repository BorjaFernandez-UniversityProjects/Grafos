#ifndef MATRIZ_COSTES_MAXIMOS_HPP
#define MATRIZ_COSTES_MAXIMOS_HPP

#include "../Material/alg_grafoPMC.h"
#include "../Material/grafoPMC.h"
#include "../Material/matriz.h"
#include "../P6/clonarGrafos.hpp"

/*  Solución al problema 1 de la segunda relación de problemas de Grafos    */

// Precondición:    la función recibe por parámetro un grafo ponderado,
//                   y tiene tres parámetros de salida: el coste del camino
//                   máximo entre los vértices (SIN repetir vértices),
//                   y los vértices de origen y destino de dicho camino,
//                   respectivamente.
template <typename T>
void datosCaminoMaximo(const GrafoP<T>& Gponderado, T costeMaximo,
                        typename GrafoP<T>::vertice verticeOrigen,
                        typename GrafoP<T>::vertice verticeDestino)
{
    matriz<T> matrizCostes;
    size_t i;
    size_t j;
    costeMaximo = 0;

    matrizCostes = matrizCostesMaximos(Gponderado);

    i = 0;
    while (i < matrizCostes.dimension())
    {
        j = 0;
        while (j < matrizCostes.dimension())
        {
            if (matrizCostes[i][j] > costeMaximo)
            {
                costeMaximo = matrizCostes[i][j];
                verticeOrigen = i;
                verticeDestino = j;
            }
            j++;
        }
        i++;
    }
}


// Precondición:    la función recibe un grafo ponderado como parámetro.
// Postcondición:   devuelve una matriz de costes que contiene los costes
//                   máximos del camino entre dos nodos cualesquiera A y B
//                   del grafo ponderado.
template <typename T>
matriz<T> matrizCostesMaximos(const GrafoP<T>& Gponderado)
{
    matriz<T> matrizCostes;
    matriz<typename GrafoP<T>::vertice> camino;
    GrafoP<T> Gauxiliar;

    Gauxiliar = clonarGrafoP(Gponderado);
    invertirCostesGrafo(Gauxiliar);

    matrizCostes = Floyd(Gauxiliar, camino);
    invertirCostesMatriz(matrizCostes);

    return matrizCostes;
}

// Precondición:    la función recibe un grafo ponderado como parámetro.
// Postcondición:   la función invierte el coste de los caminos del grafo,
//                   convirtiendo aquellos de menor coste, en los de mayor coste
//                   y viceversa.
template <typename T>
void invertirCostesGrafo(GrafoP<T>& Gponderado)
{
    typename GrafoP<T>::vertice i;
    typename GrafoP<T>::vertice j;

    i = 0;
    while (i < Gauxiliar.numVert())
    {
        j = 0;
        while (j < Gauxiliar.numVert())
        {
            Gauxiliar[i][j] = Gauxiliar[i][j] * -1;
            j++;
        }
        i++;
    }
}


// Precondición:    la función recibe una matriz<T> como parámetro.
// Postcondición:   la función invierte el valor de los elementos de la
//                   matriz, multiplicándolos todos por '-1'.
template <typename T>
void invertirCostesMatriz(matriz<T>& M)
{
    size_t i;
    size_t j;

    i = 0;
    while (i < M.dimension())
    {
        j = 0;
        while (j < M.dimension())
        {
            M[i][j] = M[i][j] * -1;
            j++;
        }
        i++;
    }
}

#endif  //MATRIZ_COSTES_MAXIMOS_HPP