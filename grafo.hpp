/*
 *
 * Implementación del TAD Grafo (tanto dirigido como no dirigido).
 * 
 */

#ifndef GRAFO_H
#define GRADO_H

#include <vector>

class Grafo
{
    public:
        typedef size_t vertice;     //Valor entre 0 y numVert() -1
        explicit Grafo(size_t n);
        size_t numVert() const;

        const vector<bool>& operator[](vertice v) const;    //Observador de solo lectura
        vector<bool>& operator [](vertive v);              //Observador para lectura/escritura

    private:
        vector<vector<bool>> ady;
};


explicit Grafo::Grafo(size_t n) :
    ady(n, vector<bool>(n, false))
{}


size_t Grafo::numVert() const
{
    return ady.size();
}


const vector<bool>& Grafo::operator [](vertice v) const
{
    return ady[v];
}


vector<bool>& Grafo::operator [](vertice v)
{
    return ady[v];
}






#endif  //GRAFO_H