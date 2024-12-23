/*
            Archivo: Clase HashTable
            Hecha en clase

            Descripci�n general: La clase del Hash Table. El m�todo que se utiliza para
            la generaci�n del c�digo hash es polinomial. El m�todo de compresi�n usado es
            el de multiplicaci�n, suma y divisi�n. Las colisiones se manejan con el m�todo
            de encadenamiento. Los factores de carga usados son de max=0.7 y min=0.3

            Modificaci�n hecha por: Carmen Hidalgo Paz

            Descripci�n: Se cambiaron los factores de carga de max=0.6 y min=0.2 a
            max = 0.7 y min=0.3 desp�es de realizar varias pruebas. Asimismo, se le
            agreg� al clear el reseteo al n�mero primo de buckets inicial y se volvieron
            a crear los baldes.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <math.h>
#include "DLinkedList.h"
#include "KVPair.h"
#include "Dictionary.h"

using std::runtime_error;
using std::cout;
using std::endl;
using std::string;

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    DLinkedList<KVPair<K, V>> *buckets;
    int max;
    int size;
    double maxLoad;
    double minLoad;
    DLinkedList<int> *primes; // lista de primos para el tama�o del arreglo

    // carga n�meros primos para ser usados como capacidad
    // m�xima de la tabla. Inicia en 1021.
    void initPrimes() {
        primes = new DLinkedList<int>();
        primes->append(61);
        primes->append(127);
        primes->append(251);
        primes->append(509);
        primes->append(1021);
        primes->append(2039);
        primes->append(4073);
        primes->append(8147);
        primes->append(16273);
        primes->append(32537);
        primes->append(65071);
        primes->append(130147);
        primes->append(260339);
        primes->append(520679);
        primes->append(1041349);
        primes->append(2082709);
        primes->goToPos(4);
    }

    double loadFactor() {
        return (double)size / (double)max;
    }

    // redimensiona la tabla para hacerla m�s grande
    void reHashUp() {
        primes->next();
        int newMax = primes->getElement();
        reHash(newMax);
    }

    // redimensiona la tabla para hacerla m�s peque�a
    void reHashDown() {
        primes->previous();
        int newMax = primes->getElement();
        if (newMax != max)
            reHash(newMax);
    }

    // redimensiona la tabla al tama�o indicado
    void reHash(int newMax) {
        int oldMax = max;
        max = newMax;
        DLinkedList<KVPair<K, V>> *newBuckets = new DLinkedList<KVPair<K, V>>[max];
        for (int i = 0; i < oldMax; i++) {
            buckets[i].goToStart();
            while (!buckets[i].getSize() == 0) {
                KVPair<K, V> p = buckets[i].remove();
                newBuckets[h(p.key)].append(p);
            }
        }
        delete [] buckets;
        buckets = newBuckets;
    }

    // revisa que una llave no exista en la estructura
    // si la encuentra lanza error
    // si no la encuentra la posici�n actual queda al final
    void checkNotExisting(K key) {
        KVPair<K, V> p(key);
        if (buckets[h(key)].contains(p))
            throw runtime_error("Duplicated key.");
    }

    // revisa que una llave exista en la estructura
    // si la encuentra deja la posici�n actual apuntando
    // a la llave buscada
    // si no la encuentra lanza error
    void checkExisting(K key) {
        KVPair<K, V> p(key);
        if (!buckets[h(key)].contains(p))
            throw runtime_error("Key not found.");
    }
    int h(K key) {
        return compress(hashCodePolynomial(key));
    }
    int compress(int code) {
        int a = 1097;
        int b = 1279;
        return abs(a * code + b) % max;
    }
    template <typename T>
    int hashCodePolynomial(T key) {
        int a = 33;
        int result = 0;
        char* bytes = reinterpret_cast<char*>(&key);
        for (unsigned int i = 0; i < sizeof(T); i++) {
            result += bytes[i] * pow(a, i);
        }
        return result;
    }
    int hashCodePolynomial(string key) {
        int a = 33;
        int result = 0;
        for (unsigned int i = 0; i < key.size(); i++) {
            result += (int)key[i] * pow(a, i);
        }
        return result;
    }

public:
    HashTable() {
        initPrimes();
        max = primes->getElement();
        buckets = new DLinkedList<KVPair<K, V>>[max];
        size = 0;
        maxLoad = 0.8;
        minLoad = 0.25;
    }
    ~HashTable() {
        delete [] buckets;
        delete primes;
    }
    void insert(K key, V value) {
        if (loadFactor() > maxLoad)
            reHashUp();
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
        size++;
    }
    V remove(K key) {
        if (loadFactor() <= minLoad)
            reHashDown();
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].remove();
        size--;
        return p.value;
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].getElement();
        return p.value;
    }
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].setElement(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return buckets[h(key)].contains(p);
    }
    void clear() {
        for (int i = 0; i < max; i++) {
            buckets[i].clear();
        }
        size = 0;
        primes->goToPos(4);
        max = primes->getElement();
        delete[] buckets;
        buckets = new DLinkedList<KVPair<K, V>>[max]; // Redimensiona la tabla hash
    }
    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                KVPair<K, V> p = buckets[i].getElement();
                keys->append(p.key);
                buckets[i].next();
            }
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new DLinkedList<V>();
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                KVPair<K, V> p = buckets[i].getElement();
                values->append(p.value);
                buckets[i].next();
            }
        }
        return values;
    }
    int getSize() {
        return size;
    }
    void print() {
        cout << "[";
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                cout << buckets[i].getElement() << " ";
                buckets[i].next();
            }
        }
        cout << "]" << endl;
    }
};

#endif // HASHTABLE_H
