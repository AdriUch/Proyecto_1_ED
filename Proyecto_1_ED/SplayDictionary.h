/*
            Archivo: Clase SplayDicitonary
            Hecho por: Adrián Ugalde Chaves

            Descripción general: Clase del diccionario Splay, basada en la clase SplayTree
            realizada en clase

            Modificación hecha por: Carmen Hidalgo Paz

            Descripción: Se agrega un método clear.

*/

#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "KVPair.h"
#include "SplayTree.h"

template <typename K, typename V>
class SplayDictionary : public Dictionary<K, V> {
private:
    SplayTree<KVPair<K, V>>* pairs;

public:
    SplayDictionary(const SplayDictionary<K, V>& other) = delete;
    void operator =(const SplayDictionary<K, V>& other) = delete;

    SplayDictionary() {
        pairs = new SplayTree<KVPair<K, V>>();
    }

    ~SplayDictionary() {
        delete pairs;
    }

    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->insert(p);
    }

    void clear() {
        pairs->clear();
    }

    V remove(K key) {
        KVPair<K, V> p(key);
        p = pairs->remove(p);
        return p.value;
    }

    V getValue(K key) {
        KVPair<K, V> p(key);
        p = pairs->find(p);
        return p.value;
    }

    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        if (pairs->contains(p)) {
            pairs->remove(p);
        }
        pairs->insert(p);
    }

    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }

    List<K>* getKeys() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<K>* keys = new DLinkedList<K>();
        while (!items->atEnd()) {
            KVPair<K, V> p = items->getElement();
            keys->append(p.key);
            items->next();
        }
        delete items;
        return keys;
    }

    List<V>* getValues() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<V>* values = new DLinkedList<V>();
        while (!items->atEnd()) {
            KVPair<K, V> p = items->getElement();
            values->append(p.value);
            items->next();
        }
        delete items;
        return values;
    }

    int getSize() {
        return pairs->getSize();
    }

    void print() {
        pairs->print();
    }
};
