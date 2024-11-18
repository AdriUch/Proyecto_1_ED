/*
            Trabajo: Proyecto 1 - Análisis de Implementaciones de Diccionarios
            Hecho por: Carmen Hidalgo Paz, Britany Romero Hernández y Adrián Ugalde Chaves
            Fecha de Entrega: 14 de noviembre del 2024
            Clase: Estructuras de Datos

            Descripción General: En esta sección se manejan los métodos
            de inserción, borrado y búsqueda para todos los diccionarios.
            Además se tiene el método para tomar el tiempo de cada acción
            mencionada anteriormente. Asimismo, se tienen métodos para insertar elementos
            de manera aleatoria, ascendente y con llaves similares. Cada vez
            que se realiza un método para cada diccionario los valores se guardan
            en un archivo .csv.

*/
#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include <stdexcept>
#include "UnsortedArrayDictionary.h"
#include "HashTable.h"
#include "BSTDictionary.h"
#include "AVLDictionary.h"
#include "SplayDictionary.h"

using std::runtime_error;
using std::cout;
using std::endl;

// - - - - - INICIO TIPOS DE LISTAS - - - - -

// Se insertan elementos en tres tipos de listas
// - - - ALEATORIA - - -
void insertRandomValues(Dictionary<int, int>* numeros) {
    int numLista = 0;
    while (numLista < 10000) {
        int r = rand() % 10500;
        if (!numeros->contains(r)) {
            numeros->insert(r, r);
            numLista = numLista + 1;
        }
    }
}
// - - - ASCENDENTE - - -
void insertAscendingValues(Dictionary<int, int>* numeros) {
    for (int i = 0; i < 10000; i++) {
        numeros->insert(i + 1, i + 1);
    }
}
// - - - LLAVES SIMILARES - - -
void insertSimilarValues(Dictionary<int, int>* numeros) {
    int spacesLeft = 0;
    while (spacesLeft < 10000) {
        int amountElements = 10 + (rand() % 41);
        int r = rand() % 10500;
        for (int i = 0; i < amountElements; i++) {
            if (spacesLeft >= 10000) {
                break;
            }
            if (!numeros->contains(r)) {
                numeros->insert(r, r);
                spacesLeft = spacesLeft + 1;
            }
            r = r + 1;
        }
    }
}
// - - - - - FIN TIPOS DE LISTAS - - - - -

// - - - - - INICIO MEDICIONES DE TIEMPOS - - - - -

//Se mide el tiempo en milisegundos
// - - - INSERCIÓN
double measureTimeInsercion(Dictionary<int, int>* numeros, int opcion, int num) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    // Valor aleatorio
    if (opcion == 0) {
        // Se toma el tiempo
        QueryPerformanceCounter(&start);
        numeros->insert(num, num);
        QueryPerformanceCounter(&end);
    }
    // Valor ascendente
    if (opcion == 1) {
        int numActual = num + 1;
        // Se toma el tiempo
        QueryPerformanceCounter(&start);
        numeros->insert(numActual, numActual);
        QueryPerformanceCounter(&end);
    }
    // Llave mezclada
    if(opcion == 2) {
        // Se toma el tiempo
        QueryPerformanceCounter(&start);
        numeros->insert(num, num);
        QueryPerformanceCounter(&end);
    }

    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}
// - - - BÚSQUEDA
double measureTimeBusqueda(Dictionary<int, int>* numeros, int element) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    // Se toma el tiempo
    QueryPerformanceCounter(&start);
    numeros->contains(element);
    QueryPerformanceCounter(&end);

    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}
// - - - BORRADO
double measureTimeBorrado(Dictionary<int, int>* numeros, int key) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    try {
        QueryPerformanceCounter(&start);
        numeros->remove(key);  // Intento de borrado
        QueryPerformanceCounter(&end);
    }
    catch (const std::runtime_error& e) {
        // Si ocurre una excepción, simplemente ignoramos este caso
        QueryPerformanceCounter(&end);  // Termina el tiempo de medición
        return 0.0;  // Tiempo de borrado omitido debido a la excepción
    }

    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}
// - - - OPERACIONES MEZCLADAS
double measureTimeMezcladas(Dictionary<int, int>* numeros, int operacion) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    int randomKey = rand() % 10500; // Generar una llave aleatoria

    try {

        if (operacion == 0) { // Inserción
            if (!numeros->contains(randomKey)) {
                QueryPerformanceCounter(&start);
                numeros->insert(randomKey, randomKey);
                QueryPerformanceCounter(&end);
            }
        }
        else if (operacion == 1) { // Búsqueda
            if (numeros->getSize()==0) {  // Verificar si el diccionario tiene elementos
                QueryPerformanceCounter(&start);
                numeros->contains(randomKey);
                QueryPerformanceCounter(&end);
            }
            else {
                return 0.0; // Saltar si no hay elementos
            }
        }
        else if (operacion == 2) { // Borrado
            if (numeros->getSize()==0) {  // Verificar si el diccionario tiene elementos
                QueryPerformanceCounter(&start);
                numeros->remove(randomKey);
                QueryPerformanceCounter(&end);
            }
            else {
                return 0.0; // Saltar si no hay elementos
            }
        }
    }
    catch (const std::runtime_error& e) {
        // Ignorar errores de borrado cuando la clave no existe
        QueryPerformanceCounter(&end);
        return 0.0;
    }

    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}
// - - - - - FIN MEDICIONES DE TIEMPOS

// - - - - - INICIO DE APUNTE DE TIEMPOS EN ARCHIVOS .CSV
// - - - INSERCIONES
void tiempoInserciones(Dictionary<int, int>* numeros, string nomDictionary) {
    const int repeticiones = 10000;
    // Guardar tiempos
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    numeros->clear();
    // Aleatorio
    int iteracion = 0;
    while (iteracion < repeticiones) {
        int r = rand() % 10500;
        if (!numeros->contains(r)) {
            tiempoAleatorio[iteracion] = measureTimeInsercion(numeros, 0, r);
            iteracion++;
        }
    }
    numeros->clear();
    cout << endl << "Prueba 1 terminada" << endl;
    // Ascendente
    for (int i = 0; i < repeticiones; ++i) {
        tiempoAscendente[i] = measureTimeInsercion(numeros, 1, i);
    }
    numeros->clear();
    cout << endl << "Prueba 2 terminada" << endl;
    // Llaves Similares

    int spacesLeft = 0;
    while (spacesLeft < 10000) {
        int amountElements = 10 + (rand() % 41);
        int r = rand() % 10500;
        for (int i = 0; i < amountElements; i++) {
            if (spacesLeft >= 10000) {
                break;
            }
            if (!numeros->contains(r)) {
                tiempoSimilares[spacesLeft] = measureTimeInsercion(numeros, 2, r);
                spacesLeft = spacesLeft + 1;
            }
            r = r + 1;
        }
    }
    numeros->clear();
    cout << endl << "Prueba 3 terminada" << endl;

    // Se escribe en un .csv
    std::ofstream file(nomDictionary + "_tiempo_Insercion.csv");
    if (file.is_open()) {
        // Nombre de cada columna
        file << "Iteracion,Orden Ascendente (ms),Orden Aleatorio (ms),Llaves Similares (ms)\n";

        for (int i = 0; i < repeticiones; ++i) {
            file << (i + 1) << ","
                << tiempoAleatorio[i] << ","
                << tiempoAscendente[i] << ","
                << tiempoSimilares[i] << "\n";
        }

        file.close();
        cout << endl << "Tiempos guardados en el archivo " + nomDictionary + "_tiempo_Insercion.csv" << endl;
    }
    else {
        std::cerr << "Error para abrir el archivo" << endl;
    }
}
// - - - BÚSQUEDAS
void tiempoBusquedas(Dictionary<int, int>* numeros, string nomDictionary) {
    const int repeticiones = 10000;
    // Guardar tiempos
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    numeros->clear();
    // Aleatorio
    insertRandomValues(numeros);
    List<int>* llaves = numeros->getKeys();
    llaves->goToStart();
    for (int i = 0; i < repeticiones; ++i) {
        llaves->goToPos(i);
        int element = llaves->getElement();
        tiempoAleatorio[i] = measureTimeBusqueda(numeros, element);
    }
    delete llaves;
    numeros->clear();
    cout << endl << "Prueba 1 terminada" << endl;
    // Ascendente
    insertAscendingValues(numeros);
    for (int i = 0; i < repeticiones; ++i) {
        tiempoAscendente[i] = measureTimeBusqueda(numeros, i+1);
    }
    numeros->clear();
    cout << endl << "Prueba 2 terminada" << endl;
    // Llaves Similares
    insertSimilarValues(numeros);
    List<int>* keys = numeros->getKeys();
    keys->goToStart();
    for (int i = 0; i < repeticiones; ++i) {
        keys->goToPos(i);
        int elemento = keys->getElement();
        tiempoSimilares[i] = measureTimeBusqueda(numeros, elemento);
    }
    delete keys;
    numeros->clear();
    cout << endl << "Prueba 3 terminada" << endl;

    // Se escribe en un .csv
    std::ofstream file(nomDictionary + "_tiempo_Busqueda.csv");
    if (file.is_open()) {
        // Nombre de cada columna
        file << "Iteracion,Orden Ascendente (ms),Orden Aleatorio (ms),Llaves Similares (ms)\n";

        for (int i = 0; i < repeticiones; ++i) {
            file << (i + 1) << ","
                << tiempoAleatorio[i] << ","
                << tiempoAscendente[i] << ","
                << tiempoSimilares[i] << "\n";
        }

        file.close();
        cout << endl << "Tiempos guardados en el archivo " + nomDictionary + "_tiempo_Busqueda.csv" << endl;
    }
    else {
        std::cerr << "Error para abrir el archivo" << endl;
    }
}
// - - - BORRADOS
void tiempoBorrados(Dictionary<int, int>* numeros, std::string nomDictionary) {
    const int repeticiones = 10000;
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    // Borrado en orden aleatorio
    numeros->clear();
    insertRandomValues(numeros);
    List<int>* llaves = numeros->getKeys();
    llaves->goToStart();

    // Guardar llaves y mezclar para obtener orden aleatorio
    std::vector<int> keyVector;
    while (!llaves->atEnd()) {
        keyVector.push_back(llaves->getElement());
        llaves->next();
    }
    std::shuffle(keyVector.begin(), keyVector.end(), std::random_device());
    for (int i = 0; i < repeticiones && i < keyVector.size(); ++i) {
        tiempoAleatorio[i] = measureTimeBorrado(numeros, keyVector[i]);
    }
    cout << endl << "Prueba 1 de borrado aleatorio terminada" << endl;

    // Borrado en orden ascendente
    numeros->clear();
    insertRandomValues(numeros);
    std::sort(keyVector.begin(), keyVector.end()); // Orden ascendente
    for (int i = 0; i < repeticiones && i < keyVector.size(); ++i) {
        tiempoAscendente[i] = measureTimeBorrado(numeros, keyVector[i]);
    }
    cout << endl << "Prueba 2 de borrado ascendente terminada" << endl;

    // Borrado en grupos de llaves similares
    numeros->clear();
    insertSimilarValues(numeros);
    // Agrupar llaves similares para simular "grupos"
    for (int i = 0; i < repeticiones && i < keyVector.size(); ++i) {
        tiempoSimilares[i] = measureTimeBorrado(numeros, keyVector[i]);
    }
    cout << endl << "Prueba 3 de borrado en grupos de llaves similares terminada" << endl;

    delete llaves;

    // Guardar resultados en un archivo .CSV
    std::ofstream file(nomDictionary + "_tiempo_Borrado.csv");
    if (file.is_open()) {
        file << "Iteracion,Orden Aleatorio (ms),Orden Ascendente (ms),Llaves Similares (ms)\n";
        for (int i = 0; i < repeticiones; ++i) {
            file << (i + 1) << ","
                << tiempoAleatorio[i] << ","
                << tiempoAscendente[i] << ","
                << tiempoSimilares[i] << "\n";
        }
        file.close();
        cout << endl << "Tiempos de borrado guardados en el archivo " + nomDictionary + "_tiempo_Borrado.csv" << endl;
    }
    else {
        std::cerr << "Error al abrir el archivo para guardar tiempos de borrado" << endl;
    }
}
// - - - OPERACIONES MEZCLADAS
void tiempoMezcladas(Dictionary<int, int>* numeros, std::string nomDictionary) {
    const int repeticiones = 10000;
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    std::vector<int> keyVector;

    // Aleatorio
    numeros->clear();
    for (int i = 0; i < repeticiones; ++i) {
        int operacion = rand() % 3;
        tiempoAleatorio[i] = measureTimeMezcladas(numeros, operacion);
    }
    numeros->clear();
    cout << endl << "Prueba 1 (Aleatorio) terminada" << endl;

    // Ascendente
    numeros->clear();
    insertAscendingValues(numeros);
    List<int>* llavesAsc = numeros->getKeys();
    llavesAsc->goToStart();
    while (!llavesAsc->atEnd()) {
        keyVector.push_back(llavesAsc->getElement());
        llavesAsc->next();
    }
    delete llavesAsc;

    for (int i = 0; i < repeticiones && i < keyVector.size(); ++i) {
        int operacion = rand() % 3;
        tiempoAscendente[i] = measureTimeMezcladas(numeros, operacion);
    }
    numeros->clear();
    cout << endl << "Prueba 2 (Ascendente) terminada" << endl;

    // Llaves Similares
    numeros->clear();
    insertSimilarValues(numeros);
    List<int>* llavesSim = numeros->getKeys();
    llavesSim->goToStart();
    while (!llavesSim->atEnd()) {
        keyVector.push_back(llavesSim->getElement());
        llavesSim->next();
    }
    delete llavesSim;

    for (int i = 0; i < repeticiones && i < keyVector.size(); ++i) {
        int operacion = rand() % 3;
        tiempoSimilares[i] = measureTimeMezcladas(numeros, operacion);
    }
    numeros->clear();
    cout << endl << "Prueba 3 (Llaves Similares) terminada" << endl;

    // Escribir resultados a archivo .csv
    std::ofstream file(nomDictionary + "_tiempo_Mixta.csv");
    if (file.is_open()) {
        file << "Iteracion,Orden Aleatorio (ms),Orden Ascendente (ms),Llaves Similares (ms)\n";
        for (int i = 0; i < repeticiones; ++i) {
            file << (i + 1) << ","
                << tiempoAleatorio[i] << ","
                << tiempoAscendente[i] << ","
                << tiempoSimilares[i] << "\n";
        }
        file.close();
        cout << endl << "Tiempos de operaciones mezcladas guardados en " + nomDictionary + "_tiempo_Mixta.csv" << endl;
    }
    else {
        std::cerr << "Error al abrir el archivo para guardar tiempos de operaciones mezcladas" << endl;
    }
}
// - - - - - FINAL DE APUNTE DE TIEMPOS EN ARCHIVOS .CSV

int main() {

    Dictionary<int, int>* numerosUnsorted = new UnsortedArrayDictionary<int, int>();
    Dictionary<int, int>* numerosHash = new HashTable<int, int>();
    Dictionary<int, int>* numerosBST = new BSTDictionary<int, int>();
    Dictionary<int, int>* numerosAVL = new AVLDictionary<int, int>();
    Dictionary<int, int>* numerosSplay = new SplayDictionary<int, int>();

    srand(time(0));
    // Pruebas de inserciones
    cout << endl << "Pruebas de Insercion:" << endl;
    /*cout << endl << "1. unsorted" << endl;
    tiempoInserciones(numerosUnsorted, "Unsorted");*/
    cout << endl << "2. hash" << endl;
    tiempoInserciones(numerosHash, "Hash");
    /*cout << endl << "3. bst" << endl;
    tiempoInserciones(numerosBST, "BST");
    cout << endl << "4. avl" << endl;
    tiempoInserciones(numerosAVL, "AVL");
    cout << endl << "5. splay" << endl;
    tiempoInserciones(numerosSplay, "Splay");*/

    //Pruebas de búsquedas
    cout << endl << "Pruebas de Busqueda:" << endl;
    /*cout << endl << "1. unsorted" << endl;
    tiempoBusquedas(numerosUnsorted, "Unsorted");*/
    cout << endl << "2. hash" << endl;
    tiempoBusquedas(numerosHash, "Hash");
    /*cout << endl << "3. bst" << endl;
    tiempoBusquedas(numerosBST, "BST");
    cout << endl << "4. avl" << endl;
    tiempoBusquedas(numerosAVL, "AVL");
    cout << endl << "5. splay" << endl;
    tiempoBusquedas(numerosSplay, "Splay");*/

    // Pruebas de borrados
    cout << endl << "Pruebas de Borrado:" << endl;
    /*cout << endl << "1. unsorted" << endl;
    tiempoBorrados(numerosUnsorted, "Unsorted");*/
    cout << endl << "2. hash" << endl;
    tiempoBorrados(numerosHash, "Hash");
    /*cout << endl << "3. bst" << endl;
    tiempoBorrados(numerosBST, "BST");
    cout << endl << "4. avl" << endl;
    tiempoBorrados(numerosAVL, "AVL");
    cout << endl << "5. splay" << endl;
    tiempoBorrados(numerosSplay, "Splay");*/

    //Pruebas operacionez mezcladas
    cout << endl << "Pruebas Mixtas:" << endl;
    /*cout << endl << "1. unsorted" << endl;
    tiempoMezcladas(numerosUnsorted, "Unsorted");*/
    cout << endl << "2. hash" << endl;
    tiempoMezcladas(numerosHash, "Hash");
    /*cout << endl << "3. bst" << endl;
    tiempoMezcladas(numerosBST, "BST");
    cout << endl << "4. avl" << endl;
    tiempoMezcladas(numerosAVL, "AVL");
    cout << endl << "5. splay" << endl;
    tiempoMezcladas(numerosSplay, "Splay");*/

    delete numerosUnsorted;
    delete numerosHash;
    delete numerosBST;
    delete numerosAVL;
    delete numerosSplay;

    return 0;
}
