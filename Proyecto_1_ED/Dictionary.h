/*
			Archivo: Clase Dictionary
			Hecha en clase

			Descripci�n general: La clase abstracta diccionario. Contiene todos los m�todos
			que se van a implementar en los 5 tipos de diccionarios creados en este proyecto.
			Ocupa la clase List para poder crear una lista de las llaves y una lista de los
			valores. Las llaves y los valores tienen tipos gen�ricos para que la clase
			pueda ser utilizada con cualquier tipo de elementos. Se pueden insertar, remover,
			buscar y cambiar elementos.

			Modificaci�n hecha por: Carmen Hidalgo Paz

			Descripci�n: Se le agreg� un m�todo clear.
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

