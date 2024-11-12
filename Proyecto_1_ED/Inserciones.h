/*
Creado por Britany
En estas pruebas los diccionarios inician vac�os y se llenan con 10000 elementos. Las llaves se insertan
de las siguientes formas:
a. Llaves en orden aleatorio
b. Llaves en orden ascendente
c. Grupos de llaves similares
*/

#pragma once
#include <iostream>
#include <vector>
#include "Dictionary.h"

using namespace std;
class Inserciones {
private:
    vector<Dictionary<int, int>*> diccionarios; // Lista de diccionarios a probar
    int size; // Tama�o de la prueba (n�mero de inserciones)
    // M�todo para limpiar todos los diccionarios
    void limpiarDiccionarios() {
        for (auto dic : diccionarios) {
            dic->clear();
        }
    }
public:
    // Constructor de la clase
    Inserciones(vector<Dictionary<int, int>*>& diccionarios, int size)
        : diccionarios(diccionarios), size(size) {}
    // Inserci�n aleatoria
    void insercionAleatoria() {
        cout << "Inserci�n aleatoria:" << endl;
        limpiarDiccionarios();
        for (int i = 0; i < size; ++i) {
            int key = rand() % size;
            for (auto dic : diccionarios) {
                dic->insert(key, key);
            }
        }
        cout << "Inserci�n aleatoria completada." << endl;
    }
    // Inserci�n ascendente
    void insercionAscendente() {
        cout << "Inserci�n ascendente:" << endl;
        limpiarDiccionarios();
        for (int i = 0; i < size; ++i) {
            for (auto dic : diccionarios) {
                dic->insert(i, i);
            }
        }
        cout << "Inserci�n ascendente completada." << endl;
    }
    // Inserci�n en grupos similares
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
};