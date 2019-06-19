#ifndef ENCONTRAR_CAMINO_MINIMO_HPP
#define ENCONTRAR_CAMINO_MINIMO_HPP


#include "../Material/grafoPMC.h"
#include "../Material/alg_grafoPMC.h"
#include "../Material/listaenla.h"
#include "../Material/matriz.h"
#include <vector>

/*  Solución al problema 2 de la segunda relación de problemas de Grafos    */


// Precondición:    la función recibe cuatro parámetros:
//                   - El número de vértices del nodo (cuadrado, NxN).
//                   - La lista de aristas inexistentes, es decir, con coste
//                      infinito. En nuestro caso, representan las paredes del laberinto.
//                   - El vértice origen del camino a calcular.
//                   - El vértice destino del camino a calcular.
// Postcondición:   devuelve el camino de coste mínimo entre el vértice origen y
//                   el vértice destino, siendo el coste de cada movimiento 1 (grafo no ponderado).
template <typename T>
vector<typename GrafoP<T>::vertice> encontrarCaminoMinimo(size_t nVertices,
                                                        Lista<typename GrafoP<T>::arista>& paredes,
                                                        typename GrafoP<T>::vertice& verticeOrigen,
                                                        typename GrafoP<T>::vertice& verticeDestino)
{
    matriz<T> matrizCostes{nVertices, 1};
    Lista<T>::posicion iteradorLista;
    GrafoP<T> Gauxiliar{nVertices};
    vector<typename GrafoP<T>::vertice> caminoVertices;
    size_t i;

    i = 0;
    while (i < nVertices)
    {
        // El coste del camino entre un nodo y él mismo es infinito (no navegable).
        matrizCostes[i][i] = GrafoP<T>::INFINITO;
    }

    iteradorLista = paredes.primera();
    while (iteradorLista != paredes.fin())
    {
        i = paredes.elemento(iteradorLista).orig;
        j = paredes.elemento(iteradorLista).dest;
        // Al encontrar una pared entre dos nodos, hacemos el camino entre
        // ellos intraspasable, convirtiendo su coste en infinito.
        matrizCostes[i][j] = GrafoP<T>::INFINITO;
        // Una pared bloquea en ambos sentidos.
        matrizCostes[j][i] = GrafoP<T>::INFINITO;
        iteradorLista = paredes.siguiente(iteradorLista);
    }

    i = 0;
    while (i < nVertices)
    {
        // Copiamos la matriz de costes en el grafo.
        Gauxiliar[i] = new vector{matrizCostes[i]};
    }

    Dijkstra(Gauxiliar, verticeOrigen, caminoVertices);
    caminoVertices = camino(verticeOrigen, verticeDestino, caminoVertices);

    return caminoVertices;
}
                                           

#endif  //ENCONTRAR_CAMINO_MINIMO_HPP