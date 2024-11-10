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

            Editado por Britany para las pruebas de inserción

*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "UnsortedArrayDictionary.h"
#include "HashTable.h"
#include "BSTDictionary.h"
#include "AVLDictionary.h"
#include "SplayDictionary.h"

using std::runtime_error;
using std::cout;
using std::endl;


//Se mide el tiempo en milisegundos
double measureTimeBusqueda(Dictionary<int, int>* numeros) {
    int r = rand() % 10000;

    List<int>* llaves = numeros->getKeys();
    llaves->goToStart();
    llaves->goToPos(r);
    int element = llaves->getElement();

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);
    numeros->contains(element);
    QueryPerformanceCounter(&end);

    delete llaves;
    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}

void insertRandomValues(Dictionary<int, int>* numeros) {
    int numLista = 0;
    while (numLista < 10000) {
        int r = rand() % 10500;
        if (!numeros->contains(r)) {
            numeros->insert(r, r);
            numLista++;
        }
    }
}

void insertAscendingValues(Dictionary<int, int>* numeros) {
    for (int i = 0; i < 10000; i++) {
        numeros->insert(i + 1, i + 1);
    }
}

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
                spacesLeft++;
            }
            r++;
        }
    }
}

void tiempoInserciones(Dictionary<int, int>* numeros, string nomDictionary) {
    const int repeticiones = 10000;
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    // Medir tiempo de inserción aleatoria
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    numeros->clear();
    QueryPerformanceCounter(&start);
    insertRandomValues(numeros);
    QueryPerformanceCounter(&end);
    double tiempoInsercionAleatoria = static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;

    cout << "Insercion aleatoria completada." << endl;

    // Medir tiempo de inserción ascendente
    numeros->clear();
    QueryPerformanceCounter(&start);
    insertAscendingValues(numeros);
    QueryPerformanceCounter(&end);
    double tiempoInsercionAscendente = static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;

    cout << "Inserción ascendente completada." << endl;

    // Medir tiempo de inserción en grupos similares
    numeros->clear();
    QueryPerformanceCounter(&start);
    insertSimilarValues(numeros);
    QueryPerformanceCounter(&end);
    double tiempoInsercionSimilares = static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;

    cout << "Insercion en grupos similares completada." << endl;

    // Escribir resultados en archivo CSV
    std::ofstream file(nomDictionary + "_tiempo_Insercion.csv");
    if (file.is_open()) {
        file << "Tipo de Insercion,Tiempo (milisegundos)\n";
        file << "Aleatoria," << tiempoInsercionAleatoria << "\n";
        file << "Ascendente," << tiempoInsercionAscendente << "\n";
        file << "Similares," << tiempoInsercionSimilares << "\n";

        file.close();
        cout << "Tiempos guardados en el archivo " + nomDictionary + "_tiempo_Insercion.csv" << endl;
    } else {
        std::cerr << "Error para abrir el archivo" << endl;
    }
}

void tiempoBusquedas(Dictionary<int, int>* numeros, string nomDictionary) {
    const int repeticiones = 10000;
    // Guardar tiempos
    double tiempoAleatorio[repeticiones];
    double tiempoAscendente[repeticiones];
    double tiempoSimilares[repeticiones];

    numeros->clear();
    insertRandomValues(numeros);
    for (int i = 0; i < repeticiones; ++i) {
        tiempoAleatorio[i] = measureTimeBusqueda(numeros);
    }
    numeros->clear();
    cout << endl << "Prueba 1 terminada" << endl;
    insertAscendingValues(numeros);
    for (int i = 0; i < repeticiones; ++i) {
        tiempoAscendente[i] = measureTimeBusqueda(numeros);
    }
    numeros->clear();
    cout << endl << "Prueba 2 terminada" << endl;
    insertSimilarValues(numeros);
    for (int i = 0; i < repeticiones; ++i) {
        tiempoSimilares[i] = measureTimeBusqueda(numeros);
    }
    numeros->clear();
    cout << endl << "Prueba 3 terminada" << endl;

    // Se escribe en un .csv
    std::ofstream file(nomDictionary + "_tiempo_Busqueda.csv");
    if (file.is_open()) {
        // Nombre de cada columna
        file << "Iteracion,Orden Ascendente (milisegundos),Orden Aleatorio (milisegundos),Llaves Similares (milisegundos)\n";

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

int main() {

    Dictionary<int, int>* numerosUnsorted = new UnsortedArrayDictionary<int, int>();
    Dictionary<int, int>* numerosHash = new HashTable<int, int>();
    Dictionary<int, int>* numerosBST = new BSTDictionary<int, int>();
    Dictionary<int, int>* numerosAVL = new AVLDictionary<int, int>();
    Dictionary<int, int>* numerosSplay = new SplayDictionary<int, int>();




    
    srand(time(0));
    cout << endl<< "1. unsorted" << endl;
    tiempoBusquedas(numerosUnsorted, "Unsorted");
    cout << endl << "2. hash" << endl;
    tiempoBusquedas(numerosHash, "Hash");
    cout << endl << "3. bst" << endl;
    tiempoBusquedas(numerosBST, "BST");
    cout << endl << "4. avl" << endl;
    tiempoBusquedas(numerosAVL, "AVL");
    cout << endl << "5. splay" << endl;
    tiempoBusquedas(numerosSplay, "Splay");

    // Pruebas de inserciones
    cout << "1. Inserciones en UnsortedArrayDictionary" << endl;
    tiempoInserciones(numerosUnsorted, "Unsorted");

    cout << "2. Inserciones en HashTable" << endl;
    tiempoInserciones(numerosHash, "Hash");

    cout << "3. Inserciones en BSTDictionary" << endl;
    tiempoInserciones(numerosBST, "BST");

    cout << "4. Inserciones en AVLDictionary" << endl;
    tiempoInserciones(numerosAVL, "AVL");

    cout << "5. Inserciones en SplayDictionary" << endl;
    tiempoInserciones(numerosSplay, "Splay");


    delete numerosUnsorted;
    delete numerosHash;
    delete numerosBST;
    delete numerosAVL;
    delete numerosSplay;

    return 0;
}
