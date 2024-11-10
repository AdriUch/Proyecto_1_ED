/*
			Archivo: Clase List
			Hecha en clase

			Descripción general: Hereda de la clase List. Se implementan los
			métodos para el manejo de los elementos dentro de la lista.

			Modificación hecha por: Carmen Hidalgo Paz

			Descripción: Se agregó el método privado expand() para expandir el
			arreglo cuando se desea insertar un elemento y el arreglo está lleno.
			Asimismo, se implementaron las funciones indexOf() y contains() para
			encontrar la posición de un elemento en la lista y si el elemento está
			en la lista, respectivamente.

			Modificación hecha por: Adrián Ugalde Chaves

			Descripción: Se crearon los métodos getArray que devuelve un puntero hacia
			el arreglo de datos y getTheElement que recibe una posición y retorna
			el elemento en esta. Asimismo se incluyó un constructor de copia.
*/

#pragma once
#define DEFAULT_MAX 100

#include <stdexcept>
#include <iostream>
#include "List.h"


using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
protected:
	E* elements;
	int max;
	int size;
	int pos;

	void expand() {
		E* temp;
		temp = new E[max * 2];

		for (int i = 0; i < size; i++) {
			temp[i] = elements[i];
		}

		delete[] elements;
		elements = temp;
		max = max * 2;
	}

public:
	// Constructor
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		size = 0;
		pos = 0;
	}
	// Destructor
	~ArrayList() {
		delete[] elements;
	}

	// Método para obtener el arreglo interno de las listas
	E* getArray() const {
		return elements;
	}

	void setElement(E element) {
		elements[pos] = element;
	}

	// Constructor de copia. Apoya los "other" de la función del operador de asignación
	ArrayList(const ArrayList<E>& other) {
		max = other.max;
		size = other.size;
		pos = other.pos;
		elements = new E[max];

		for (int i = 0; i < size; i++) {
			elements[i] = other.elements[i];
		}
	}

	// Inserta un elemento nuevo en la posición actual
	void insert(E element) {
		if (size == max) {
			expand();
		}

		for (int i = size; i > pos; i--) {
			elements[i] = elements[i - 1];
		}

		elements[pos] = element;
		size++;
	}
	// Agrega un elemento nuevo en la última posición de la lista
	void append(E element) {
		if (size == max) {
			expand();
		}

		elements[size] = element;
		size++;
	}
	// Elimina el elemento encontrado en la posición actual
	E remove() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos == size) {
			throw runtime_error("No current element.");
		}

		E result = elements[pos];
		for (int i = pos + 1; i < size; i++) {
			elements[i - 1] = elements[i];
		}

		size--;

		return result;
	}
	// Retorna el valor del elemento encontrado en la posición actual
	E getElement() {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (pos == size) {
			throw runtime_error("No current element.");
		}

		return elements[pos];
	}
	// Retorna el valor del elemento encontrado en la posición especificada
	E getTheElement(int element) const {
		if (size == 0) {
			throw runtime_error("List is empty.");
		}
		if (element < 0 || element >= size) {
			throw runtime_error("Index out of range.");
		}

		return elements[element];
	}

	// Elimina todos los elementos de la lista y la deja vacía
	void clear() {
		size = pos = 0;
	}
	// Mueve la posición actual al inicio de la lista
	void goToStart() {
		pos = 0;
	}
	// Mueve la posición actual al final de la lista
	void goToEnd() {
		pos = size;
	}
	// Mueve la posición actual a la posición indicada por parámetro
	void goToPos(int pos) {
		if (pos < 0 || pos > size) {
			throw runtime_error("Index out of bounds.");
		}
		this->pos = pos;
	}
	// Mueve la posición actual al siguiente elemento, si lo hay
	void next() {
		if (pos < size) {
			pos++;
		}
	}
	// Mueve la posición actual al elemento anterior, si lo hay
	void previous() {
		if (pos > 0) {
			pos--;
		}
	}
	// Retorna verdadero si la posición actual de la lista se encuentra al inicio
	bool atStart() {
		return pos == 0;
	}
	// Retorna verdadero si la posición actual de la lista se encuentra al final
	bool atEnd() {
		return pos == size;
	}
	// Retorna un entero con la posición actual dentro de la lista
	int getPos() {
		return pos;
	}
	// Retorna el tamaño de la lista
	int getSize() {
		return size;
	}
	// Dice si la lista está vacía
	bool isEmpty() {
		return size == 0;
	}
	// Dice la posición de un elemento en una lista, empezando la búsqueda desde
	// una posición dada por parámetro
	int indexOf(E element, int start) {
		if (start < 0 || start > size) {
			throw runtime_error("Invalid start position.");
		}
		for (int i = start; i < size; i++) {
			if (elements[i] == element) {
				return i;
			}
		}

		return -1;

	}
	// Retorna verdadero si una lista contiene un elemento dado por parámetro
	bool contains(E element) {
		bool exists = false;

		for (int i = 0; i < size; i++) {
			if (elements[i] == element) {
				exists = true;
			}
		}

		return exists;
	}
	// Imprime la lista
	void print() {
		for (int i = 0; i < size; i++) {
			cout << "		" << elements[i] << endl;
		}
	}
};
