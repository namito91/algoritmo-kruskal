#include "grafo.h"

int contador = 0;

void grafo::insertar_vertice(const char &v)
{

    // valida que no se ingrese un vertice ya existente,y no mas de 10 vertices
    for (size_t i = 0; i < V.size(); i++)
    {
        if (V.at(i) == v)
        {

            cout << "vertice ya existente" << endl;

            cout << "no se agrego en el conjunto" << endl;

            break;
        }
    }

    if (V.size() == 10)
    {
        cout << "limite de vertices superado(10)" << endl;

        return;
    }

    V.push_back(v);

    cout << "vertice ingresado : " << v << endl;

    cout << "vector size : " << V.size() << endl;
}

void grafo::insertar_arista()
{
    int cantidadAristas = 0, peso = 0;
    char v1, v2;

    cout << "ingresa la cantidad de aristas a usar : " << endl;
    cout << "(no ingresar mas de 15 aristas)" << endl;
    cin >> cantidadAristas;

    // !(cin >> cantidadAristas), valida el tipo de dato
    while (cantidadAristas < 0 || cantidadAristas > 15 || !(cin >> cantidadAristas))
    {
        cout << "valor incorrecto" << endl;
        cout << "ingresa nuevamente la cantidad de aristas a usar : " << endl;
        cout << "(no ingresar mas de 15 aristas)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cantidadAristas;
    }

    while (contador < cantidadAristas)
    {
        cout << " Vertices : " << endl;
        for (size_t i = 0; i < V.size(); i++)
        {
            cout << i << " : " << V.at(i) << endl;
        }

        cout << "elegi la opcion del vertice 1 " << endl;
        cin >> v1;
        cout << "elegi la opcion del vertice 2 " << endl;
        cin >> v2;
        cout << "ingresa el peso de la arista o bucle(entre 0 y 20) " << endl;
        cin >> peso;

        // valida que sean opciones existentes
        // valida el tipo de dato ingresado
        while (v1 < 0 || v1 > V.size() || v2 < 0 || v2 > V.size() || !(cin >> v1) || !(cin >> v2))
        {
            cout << "opciones incorrectas,volve a ingresarlas " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << " Vertices : " << endl;
            for (size_t i = 0; i < V.size(); i++)
            {
                cout << i << " : " << V.at(i) << endl;
            }

            cout << "elegi la opcion del vertice 1 " << endl;
            cin >> v1;
            cout << "elegi la opcion del vertice 2 " << endl;
            cin >> v2;
        }

        // valida el peso ingresado y su tipo de dato
        while (peso < 0 || peso > 20 || !(cin >> peso))
        {
            cout << "valor del peso incorrecto" << endl;
            cout << "ingresa nuevamente el peso de la arista o bucle(entre 0 y 20) " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> peso;
        }

        // no puede haber mas de 4 aristas entre dos vertices
        if (aristasSalientesDelVertice[v1] > 4)
        {
            cout << "el vertice " << v1 << " ya contiene 4 aristas salientes" << endl;
            cout << "no es posible agregar esta arista" << endl;
        }
        else if (aristasSalientesDelVertice[v2] > 4)
        {
            cout << "el vertice " << v2 << " ya contiene 4 aristas salientes" << endl;
            cout << "no es posible agregar esta arista" << endl;
        }
        // valida que no haya mas de 3 bucles en el mismo vertice
        else if (v1 == v2 && (aristasSalientesDelVertice[v1] > 3 || aristasSalientesDelVertice[v2] > 3))
        {
            cout << "cantidad de bucles en el mismo vertice supero el limite" << endl;
            cout << "no es posible agregar esta arista" << endl;
        }
        else
        {
            E.push_back(arista{{v1, v2}, peso}); // ingresa la arista al vector con exito
            cout << "arista ingresada con exito : " << E.at(contador).first.first << " " << E.at(contador).first.second << " peso :" << E.at(contador).second << endl;

            // incrementa la arista saliente de cada vertice en 1 unidad
            aristasSalientesDelVertice[v1]++;
            aristasSalientesDelVertice[v2]++;

            contador++;
            cout << "cantidad de aristas ingresadas : " << contador << endl;
        }
    }
}

void grafo::insertar_arista(const char &v1, const char &v2, const int &peso)
{
    // no se pueden ingresar mas de 15 aristas
    if (E.size() > 15)
    {
        cout << "limite de aristas superados(mas de 15)" << endl;
    }
    // valida que el peso ingresado no sea mayor a 20 ni menor a 0
    else if (peso < 0 || peso > 20)
    {
        cout << "peso ingresado incorrecto, debe ser entre 0 y 20 " << endl;
    }
    // valida que no puede haber mas de 4 aristas entre dos vertices(pueden tener el mismo peso)
    else if (aristasSalientesDelVertice[v1] > 4 || aristasSalientesDelVertice[v2] > 4)
    {
        cout << "el vertice/s ingresado ya contiene 4 aristas salientes" << endl;
        cout << "no es posible agregar esta arista" << endl;
    }
    // no puede haber mas de 3 bucles en el mismo vertice
    else if ((v1 == v2 && aristasSalientesDelVertice[v1] > 3) || (v1 == v2 && aristasSalientesDelVertice[v2] > 3))
    {
        cout << "cantidad de bucles en el mismo vertice supero el limite" << endl;

        cout << "no es posible agregar esta arista" << endl;
    }
    else
    {
        aristasSalientesDelVertice[v1]++;

        aristasSalientesDelVertice[v2]++;

        E.push_back(arista{{v1, v2}, peso});

        cout << "arista ingresada con exito : " << v1 << " " << v2 << " " << peso << endl;
    }
}

void grafo::inicial(const char &conjunto, const char &vertice)
{
    auto it = CE.encabezados.find(conjunto);

    // valida que no se use el mismo vertice para distintos conjuntos(componentes)
    // Si conjunto está presente en el contenedor CE.encabezados,
    // el iterador apuntará al elemento correspondiente;
    // de lo contrario, apuntará al final del contenedor.
    if (it != CE.encabezados.end())
    {
        cout << "el conjunto ya se encuentra ingresado,elegi otro nombre" << endl;
    }

    CE.nombres.insert({conjunto, {vertice, '0'}});

    CE.encabezados.insert({conjunto, {1, vertice}});

    cout << "conjunto iniciado : " << conjunto << endl;
}

void grafo::combina(const char &a, const char &b)
{

    // busco el conjunto al que pertenece A
    char conjA = CE.nombres.find(a)->second.first;

    // busco el conjunto al que pertenece B
    char conjB = CE.nombres.find(b)->second.first;

    // busco el conjunto de A en el encabezado,
    auto encabezadoA = CE.encabezados.find(conjA);

    // busco el conjunto de B en el encabezado,
    auto encabezadoB = CE.encabezados.find(conjB);

    // cuenta de los encabezados
    int cuentaA = encabezadoA->second.first;

    int cuentaB = encabezadoB->second.first;

    // compara el tamaño de los dos conjuntos
    // si el conjunto A es mayor,combina el conjunto B dentro del conjunto A
    if (cuentaA > cuentaB)
    {
        // primer elemento del encabezado B,
        char i = encabezadoB->second.second;

        auto nombresB = CE.nombres.find(i);

        // primer caso , componentes recien iniciados,
        if (nombresB->second.second == '0')
        {
            nombresB->second.first = conjA;

            char verticeSigB = nombresB->second.second;
        }

        // encuentra el final de B , cambiando los nombres de los conjuntos
        // por A conforme se avanza1
        //  nombres{ ['a',('a','b')],['b',('b','c')],['c',('c','0')] }
        while (nombresB->second.second != '0')
        {
            // se cambia el nombre de conjunto , del elemento en B
            nombresB->second.first = conjA;

            char verticeSigB = nombresB->second.second;

            // se busca el siguiente vertice
            nombresB = CE.nombres.find(verticeSigB);
        }

        // se cambia el nombre de conjunto , del ultimo elemento en B
        nombresB->second.first = conjA;

        // ahora nombresB es el ultimo par de vertices del conjunto B , ['c',('c','0')]

        // se toma el primer vertice del encabezado A
        char primerVerticeA = encabezadoA->second.second;

        // se engancha el final del conjunto B , con el inicio del conjunto A
        nombresB->second.second = primerVerticeA;

        // suma de las cuentas de los encabezados A y B
        int cuenta = cuentaA + cuentaB;

        // se actualiza la cuenta del encabezado A
        encabezadoA->second.first = cuenta;

        // primer vertice del encabezado B
        char primeVerticeB = encabezadoB->second.second;

        // se actualiza el primer elemento del encabezado A ,
        // ahora el primer vertice de A, es el primer vertice de B
        encabezadoA->second.second = primeVerticeB;

        // CE.encabezados.erase(b);
    }

    else
    {
        // else | B es al menos tan grande como A |
        // combina el conjunto A dentro del conjunto B

        // a{a,c}  b{b,d}

        // primer elemento del encabezado A
        char i = encabezadoA->second.second;

        auto nombresA = CE.nombres.find(i);

        if (nombresA->second.second == '0')
        {
            nombresA->second.first = conjB;

            char verticeSigA = nombresA->second.second;
        }

        // se avanza al final del conjunto de vertices de A
        // '0' indica el final del conjunto de vertices,
        // nombres{ ['a',('a','b')],['b',('b','c')],['c',('c','0')] }
        while (nombresA->second.second != '0')
        {
            // se cambia el nombre de conjunto , del elemento en A
            nombresA->second.first = conjB;

            char verticeSigA = nombresA->second.second;

            nombresA = CE.nombres.find(verticeSigA);
        }

        // se cambia el nombre de conjunto , del ultimo elemento en A
        nombresA->second.first = conjB;

        // ahora nombresA es el ultimo par de vertices del conjunto A , ['c',('c','0')]
        // se toma el primer vertice del encabezado B
        char primerVerticeB = encabezadoB->second.second;

        // se engancha el final del conjunto A , con el inicio del conjunto B
        nombresA->second.second = primerVerticeB;

        // suma de las cuentas de los encabezados A y B
        int cuenta = cuentaA + cuentaB;

        // se actualiza la cuenta del encabezado B
        encabezadoB->second.first = cuenta;

        // primer vertice del encabezado A
        char primerVerticeA = encabezadoA->second.second;

        // se actualiza el primer elemento del encabezado B ,
        // ahora el primer vertice de B, es el primer vertice de A
        encabezadoB->second.second = primerVerticeA;

        //  CE.encabezados.erase(a);
    }

    // end ; | COMBINA |
}

char grafo::encuentra(const char &v)
{
    // devuelve el nombre de aquel conjunto que tiene a v como miembro |
    char conjunto = CE.nombres.find(v)->second.first;

    // cout << "conjunto de " << v << " : " << conjunto << endl;

    // return ( C . nombres [ v ]. nombre_conjunto )
    return conjunto;
}

// Guarda al conjunto E dentro de la cola de prioridad teniendo en cuenta los costos.
void grafo::inserta()
{

    vector<arista> aristas = this->getAristas();

    for (size_t i = 0; i < aristas.size(); i++)
    {
        // insertar aristas en la cola de prioridad
        this->grafo_ordenado.push(aristas.at(i));
    }
}

arista grafo::sacar_min()
{

    arista a = this->grafo_ordenado.top();

    this->grafo_ordenado.pop();

    return a;
}

void grafo::kruskal()
{

    vector<char> vertices = this->getVertices();

    // numero de componentes
    int comp_n = vertices.size();

    // vector<arista> aristas = this->getAristas();

    // inicia componentes, cada vertice es un componente en si mismo,
    for (char v : vertices)
    {
        inicial(v, v);
    }

    // se inicializa la cola de prioridad
    inserta();

    // se itera sobre la cantidad de componentes,
    while (comp_n > 1)
    {
        // primer arista de la cola de prioridad,
        arista a = sacar_min();

        // se obtienen los vertices de la arista,
        char v1 = a.first.first;

        char v2 = a.first.second;

        // se buscan los conjuntos a los que pertenece cada vertice,
        char conj_v1 = encuentra(v1);

        char conj_v2 = encuentra(v2);

        // se comprueba si los 2 vertices pertenecen a conjuntos disjuntos,
        if (conj_v1 != conj_v2)
        {
            // se combinan los vertices en un mismo conjunto,
            combina(v1, v2);

            // se ingresa la arista en el arbol min
            this->arbol_minimo.push_back(a);

            // se reduce en 1 la cantidad de componentes a analizar,
            comp_n -= 1;
        }
    }

    // se imprime el arbol minimal obtenido
    cout << "kruskal : " << endl;

    for (size_t i = 0; i < this->arbol_minimo.size(); i++)
    {
        cout << "( " << this->arbol_minimo.at(i).first.first << " , " << this->arbol_minimo.at(i).first.second << " ) " << endl;
    }
}