/*
			Archivo: Clase Dictionary
			Hecha en clase

			Descripción general: La clase abstracta diccionario. Contiene
			todos los métodos que se van a implementar en los tipos
			de diccionarios.

			Modificación hecha por: Carmen Hidalgo Paz

			Descripción: Se le agregó un método clear.
*/

#pragma once

#include "List.h"

template <typename K, typename V>
class Dictionary {
private:
	Dictionary(const Dictionary<K, V>& other) {}
	void operator =(const Dictionary<K, V>& other) {}

public:
	Dictionary() {}
	virtual ~Dictionary() {}
	virtual void insert(K key, V value) = 0;
	virtual void clear() = 0;
	virtual V remove(K key) = 0;
	virtual V getValue(K key) = 0;
	virtual void setValue(K key, V value) = 0;
	virtual bool contains(K key) = 0;
	virtual List<K>* getKeys() = 0;
	virtual List<V>* getValues() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};

