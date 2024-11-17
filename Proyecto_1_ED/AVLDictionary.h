/*
			Archivo: Clase AVLDicitonary
			Hecho por: Britany Romero Hernández

			Descripción general:la clase utiliza un objeto de tipo AVLTree<KVPair<K, V>> para almacenar los pares llave-valor, 
                        donde KVPair<K, V> es una estructura que contiene una llave (K) y un valor (V). 
                        La clase ofrece métodos para insertar, eliminar, buscar y modificar elementos, 
		        así como para obtener todas las llaves y valores almacenados.

			Modificación hecha por: Carmen Hidalgo Paz

			Descripción: Se agrega un método clear.

*/

#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "KVPair.h"
#include "AVLTree.h"

template <typename K, typename V>
class AVLDictionary : public Dictionary<K, V> {
private:
	AVLTree<KVPair<K, V>>* pairs;

public:
	AVLDictionary(const AVLDictionary<K, V>& other) = delete;
	void operator =(const AVLDictionary<K, V>& other) = delete;
// Constructor por defecto
// Crea un nuevo diccionario basado en un árbol AVL vacío.
	AVLDictionary() {
		pairs = new AVLTree<KVPair<K, V>>();
	}
// Destructor
// Libera la memoria utilizada por el árbol AVL.
	~AVLDictionary() {
		delete pairs;
	}
// Método: insert
// Inserta un nuevo par llave-valor en el diccionario.
// Si la llave ya existe, el valor no se actualiza, se debe usar setValue para actualizarlo.
	void insert(K key, V value) {
		KVPair<K, V> p(key, value);
		pairs->insert(p);
	}
// Método: clear
// Elimina todos los elementos del diccionario, dejando el árbol AVL vacío.
	void clear() {
		pairs->clear();
	}
// Método: remove
// Elimina el par llave-valor asociado a la llave especificada.
// Lanza una excepción si la llave no existe.
	V remove(K key) {
		KVPair<K, V> p(key);
		p = pairs->remove(p);
		return p.value;
	}
// Método: getValue
// Busca el valor asociado a una llave dada.
// Lanza una excepción si la llave no se encuentra.
	V getValue(K key) {
		KVPair<K, V> p(key);
		p = pairs->find(p);
		return p.value;
	}
// Método: setValue
// Actualiza el valor asociado a una llave dada. Si la llave no existe, se inserta un nuevo par.
	void setValue(K key, V value) {
		KVPair<K, V> p(key, value);
		if (pairs->contains(p)) {
			pairs->remove(p);
		}
		pairs->insert(p);
	}
// Método: contains
// Verifica si existe un par con la llave especificada en el diccionario.
// Parámetros:
	bool contains(K key) {
		KVPair<K, V> p(key);
		return pairs->contains(p);
	}
// Método: getKeys
// Obtiene una lista con todas las llaves del diccionario.
// Retorna: un puntero a una lista con las llaves.
	List<K>* getKeys() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<K>* keys = new DLinkedList<K>();
		while (!items->atEnd()) {
			auto p = items->getElement();
			keys->append(p.key);
			items->next();
		}
		delete items; 
		return keys;
	}
// Método: getValues
// Obtiene una lista con todos los valores del diccionario.
// Retorna: un puntero a una lista con los valores.
	List<V>* getValues() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<V>* values = new DLinkedList<V>();
		while (!items->atEnd()) {
			auto p = items->getElement();
			values->append(p.value);
			items->next(); 
		}
		delete items;
		return values;
	}
// Método: getSize
// Obtiene el número de elementos almacenados en el diccionario.
// Retorna: el tamaño del diccionario.
	int getSize() {
		return pairs->getSize();
	}
// Método: print
// Imprime el contenido del diccionario, mostrando los pares llave-valor.
void print() {
	void print() {
		pairs->print();
	}
};
