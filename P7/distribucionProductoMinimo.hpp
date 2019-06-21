#ifndef DISTRIBUCION_PRODUCTO_MINIMO_HPP
#define DISTRIBUCION_PRODUCTO_MINIMO_HPP


#include "../Material/grafoPMC.h"
#include "../Material/alg_grafoPMC.h"
#include "../Material/matriz.h"
#include <vector>
#include <limits>

/*  Solución al problema 3 de la segunda relación de problemas de Grafos    */


//Precondiciones:     la función recibe seis parámetros:
//                   - el vértice que representa el centro de producción en el grafo
//                   - la cantidad de producto que hay que distribuir en la región
//                   - la matriz de distancia entre las ciudades de la región
//                   - un vector que representa la capacidad de almacenamiento de cada ciudad
//                   - un vector que representa el porcentaje de subvención sobre los costes
//                      mínimos de cada ciudad
//                   - un vector de enteros (parámetro de salida) de tamaño igual
//                      al número de ciudades
//Postcondición:     en el parámetro de salida se guarda la cantidad de producto a almacenar
//                      en cada ciudad. Además, la función devuelve el coste total de hacer
//                      toda la distribución. 


template <typename T>
T distribucionProductoMinimo(typename GrafoP<T>::vertice centroProduccion,
                                int cantidadProducto, const matriz<T>& distanciaCiudades,
                                const vector<int>& almacenamiento, const vector<float>& subvencion,
                                vector<int>& productoDistribuido)
{
    size_t numCiudades = distanciaCiudades.dimension();
    vector<T> distanciasMinimas;
    vector<float> rentabilidadCiudades{numCiudades};
    vector<bool> ciudadesLlenas{numCiudades};
    vector<typename GrafoP<T>::vertice> camino{numCiudades};
    GrafoP<T> grafoDistanciaCiudades;
    size_t i;
    size_t ciudadRentable;
    float menorCoste;
    float costeDistribucion;

    grafoDistanciaCiudades = generarGrafo(distanciaCiudades);
    distanciasMinimas = Dijkstra(grafoDistanciaCiudades, centroProduccion, camino);

    i = 0;
    while (i < numCiudades)
    {
        // La rentabilidad por unidad de producto de almacenar en una determinada ciudad
        // viene dada por el coste de almacenamiento por el porcentaje a pagar del mismo.
        rentabilidadCiudades[i] = distanciasMinimas[i] * (1 - subvencion[i]);
        i++;
    }

    costeDistribucion = 0;
    i = 0;
    productoDistribuido = vector<int>(numCiudades, 0);
    while (i < numCiudades && cantidadProducto > 0)
    {
        j = 0;
        menorCoste = std::numeric_limits<float>::max();
        // Con este bucle obtenemos en cada iteración la ciudad más rentable no-llena
        while (j < numCiudades)
        {
            // Si encontramos una ciudad más rentable, distinta del centro de producción
            // y que no tenga el almacén lleno.
            if (rentabilidadCiudades[j] < menorCoste && j != centroProduccion
                && ciudadesLlenas[j] == false)
            {
                menorCoste = rentabilidadCiudades[j];
                ciudadRentable = j;
            }
            j++;
        }
        // Si el almacenamiento de una ciudad es menor que el producto restante
        if (cantidadProducto >= almacenamiento[ciudadRentable])
        {
            productoDistribuido[ciudadRentable] = almacenamiento[ciudadRentable];
            costeDistribucion += rentabilidadCiudades[ciudadRentable] * almacenamiento[ciudadRentable];
            cantidadProducto = cantidadProducto - almacenamiento[ciudadRentable];
        }
        // Si el almacenamiento de una ciudad es mayor que el producto restante
        else
        {
            productoDistribuido[ciudadRentable] = cantidadProducto;
            costeDistribucion += rentabilidadCiudades[ciudadRentable] * cantidadProducto;
            cantidadProducto = 0;
        }
        // Marcamos la ciudad actual como llena
        ciudadesLlenas[ciudadRentable] = true;
        i++;
    }
    return costeDistribucion;
}


template <typename T>
GrafoP<T> generarGrafo(const matriz<T>& matrizCostes)
{
    GrafoP<T> grafoPonderado{matrizCostes.dimension()};
    size_t i;

    i = 0;
    while (i < matrizCostes.dimension())
    {
        grafoPonderado[i] = new vector(matrizCostes[i]);
        i++;
    }

    return grafoPonderado;
}


template <typename T>
void ordenarVectorMenorMayor(vector<T>& v)
{
    size_t i;
    size_t j;
    T aux;

    while (i < v.size())
    {
        j = i + 1;
        while (j < v.size())
        {
            if (v[j] < v[i])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
            j++;
        }
        i++;
    }
}


#endif  //DISTRIBUCION_PRODUCTO_MINIMO_HPP