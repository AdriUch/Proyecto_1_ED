/*
			Archivo: Clase UnsortedArrayDictionary
			Hecha en clase

			Descripción general: La clase del diccionario del UnsortedArray. Utiliza un arrayList
			con elementos de tipo KVPair para almacenar los pares. No hay ningún tipo de orden
			en el que se guardan los elementos. Se implementan los métodos para el manejo de los
			elementos.

			Modificación hecha por: Carmen Hidalgo Paz

			Descripción: Se agrega un método clear.
*/

#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "ArrayList.h"
#include "DLinkedList.h"
#include "KVPair.h"

using std::runtime_error;

template <typename K, typename V>
class UnsortedArrayDictionary : public Dictionary<K, V> {
private:
	List<KVPair<K, V>>* pairs;

	void checkNotExisting(K key) {
		KVPair<K, V> p(key);
		pairs->goToStart();
		while (!pairs->atEnd()) {
			if (p == pairs->getElement())
				throw runtime_error("Duplicated key.");
			pairs->next();
		}
	}
	// este método también actualiza la posición actual
	// para que apunte al par de la llave buscada.
	void checkExisting(K key) {
		KVPair<K, V> p(key);
		pairs->goToStart();
		while (!pairs->atEnd()) {
			if (p == pairs->getElement())
				return;
			pairs->next();
		}
		throw runtime_error("Key not found.");
	}
public:
	UnsortedArrayDictionary(int max = DEFAULT_MAX) {
		pairs = new ArrayList<KVPair<K, V>>(max);
	}
	~UnsortedArrayDictionary() {
		delete pairs;
	}
	void insert(K key, V value) {
		checkNotExisting(key);
		KVPair<K, V> p(key, value);
		pairs->append(p);
	}
	void clear() {
		pairs->clear();
	}
	V remove(K key) {
		checkExisting(key);
		KVPair<K, V> p = pairs->remove();
		return p.value;
	}
	V getValue(K key) {
		checkExisting(key);
		KVPair<K, V> p = pairs->getElement();
		return p.value;
	}
	void setValue(K key, V value) {
		checkExisting(key);
		KVPair<K, V> p(key, value);
		pairs->setElement(p);
	}
	bool contains(K key) {
		KVPair<K, V> p(key);
		pairs->goToStart();
		while (!pairs->atEnd()) {
			if (p == pairs->getElement())
				return true;
			pairs->next();
		}
		return false;
	}
	List<K>* getKeys() {
		List<K>* keys = new DLinkedList<K>();
		pairs->goToStart();
		while (!pairs->atEnd()) {
			KVPair<K, V> p = pairs->getElement();
			keys->append(p.key);
			pairs->next();
		}
		return keys;
	}
	List<V>* getValues() {
		List<V>* values = new DLinkedList<V>();
		pairs->goToStart();
		while (!pairs->atEnd()) {
			KVPair<K, V> p = pairs->getElement();
			values->append(p.value);
			pairs->next();
		}
		return values;
	}
	int getSize() {
		return pairs->getSize();
	}
	void print() {
		pairs->print();
	}
};

