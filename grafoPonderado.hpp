/*
 *
 * Implementación del TAD Grafo Ponderado (tanto dirigido como no dirigido).
 * 
 */

#ifndef GRAFO_PONDERADO_H
#define GRAFO_PONDERADO_H

#include <vector>
#include <limits>


template <typename T> class GrafoP
{

    public:
        typedef T tCoste;
        typedef size_t vertice;             //Valor entre 0 y numVert() -1
        static const tCoste INFINITO;       //Peso de la arista inexistente.

        explicit GrafoP(size_t n);
        size_t numVert() const;

        const vector<tCoste>& operator [](vertice v) const;
        vector<tCoste>& operator [](vertice v);

        bool esDirigido() const;
    
    private:
        vector<vector<tCoste>> costes;

};

template <typename T>
    const tCoste GrafoP<T>::INFINITO = std::numeric_limits<T>::max();



template <typename T>
    explicit GrafoP::GrafoP(size_t n) :
        costes(n, vector<tCoste>(n, INFINITO))
    {}


template <typename T>
    size_t numVert() const
    {
        return costes.size();
    }


template <typename T>
    const vector<tCoste>& GrafoP::operator [](vertice v) const
    {
        return costes[v];
    }


template <typename T>
    vector<tCoste>& GrafoP::operator [](vertice v)
    {
        return costes[v];
    }

template <typename T>
    bool GrafoP::esDirigido() const
    {
        
    }


#endif  //GRAFO_PONDERADO_H