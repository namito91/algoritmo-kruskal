#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <limits>
#include "menorValor.h"
using namespace std;

/*
* \ struct combina_encuentra

* @param nombres: es un map cuya key sera un char ( nombre del vertice )
 y un pair con el vertice y el vertice siguiente ( adyacente)

* @param encabezados: map cuya key sera un char ( conjunto ) y un pair que tiene a
* un entero como indice de cantidad de adyacencias y el primer elemento del conjunto de vertices .
*/
typedef struct combina_encuentra
{
    map<char, pair<char, char>> nombres; // conjunto, vertice y vertice siguiente

    map<char, pair<int, char>> encabezados; // conjunto, cuenta y primer elemento

} conjunto_CE;

class grafo
{
    vector<char> V; // Conjunto de vertices

    vector<arista> E; // Conjunto de aristas con sus pesos

    map<char, int> aristasSalientesDelVertice; // contenedor de la cantidad de aristas salientes de cada vertice // sirve para controlar la cantidad de aristas del grafo

    conjunto_CE CE; // Estructura para el analisis de adyacencias

    arbol grafo_ordenado; // cola de prioridad con los pesos de las aristas

    vector<arista> arbol_minimo; // Arbol minimal

public:
    grafo() {} // / constructor

    ~grafo() {} // / destructor

    void insertar_vertice(const char &); // Guarda los vertices en el conjunto V

    void insertar_arista(const char &, const char &, const int &); // / Guarda las aristas en el Conjunto E

    void insertar_arista(); // Guarda las aristas en el conjunto E pidiendolas ingresar por Teclado

    void inicial(const char &, const char &); // inicializa a las estructuras de conjunto COMBINA-ENCUENTRA // (cada vertice es un componente conexo por si mismo)

    void combina(const char &, const char &); // Combina los conjuntos que se encuentran formando el árbol

    char encuentra(const char &); // / Encuentra los vertices dentro del conjunto COMBINA - ENCUENTRA

    void kruskal(); // Algoritmo generador del árbol recubridor minimal

    void inserta(); // Guarda al conjunto E dentro de la cola de prioridad teniendo en cuenta los costos.

    arista sacar_min();

    friend ostream &operator<<(ostream &, grafo); // Sobrercarga de la salida estandar para mostrar al grafo

    // setters, getters
    vector<char> getVertices()
    {

        return this->V;
    }

    vector<arista> getAristas()
    {

        return this->E;
    }

    vector<arista> getArbolMin()
    {

        return this->arbol_minimo;
    }

    void setCE(conjunto_CE &ce)
    {

        this->CE = ce;
    }

    conjunto_CE getCE()
    {

        return this->CE;
    }

    // void printCE(const char &);
};

#endif