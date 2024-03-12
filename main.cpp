#include "grafo.h"

int main()
{
    // se instancia g1 en el stack
    grafo g1;

    // TESTS , grafo
    // conjunto de vertices
    g1.insertar_vertice('a');
    g1.insertar_vertice('b');
    g1.insertar_vertice('c');
    g1.insertar_vertice('d');
    g1.insertar_vertice('f');
   // g1.insertar_vertice('g');

    // conjunto de aristas
    g1.insertar_arista('a', 'b', 1);
    g1.insertar_arista('a', 'c', 1);
    g1.insertar_arista('a', 'f', 2);
   // g1.insertar_arista('a', 'g', 1);

    g1.insertar_arista('b', 'c', 3);
    g1.insertar_arista('b', 'f', 3);
   // g1.insertar_arista('b', 'g', 2);

    g1.insertar_arista('c', 'd', 4);
    g1.insertar_arista('c', 'd', 6);
  //  g1.insertar_arista('c', 'g', 1);

    g1.insertar_arista('d', 'f', 3);

    g1.kruskal();

    

    return 0;
}