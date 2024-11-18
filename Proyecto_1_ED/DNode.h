/*
			Archivo: Clase DNode
			Hecha en clase

			Descripción general: La clase del nodo de la lista doblemente enlazada. Crea
			un elemento que tiene dos punteros, uno al elemento anterior y otro para el siguiente
			elemento. De esta manera es más fácil recorrer la lista.
*/

#pragma once

template <typename E>
class DNode {
public:
	E element;
	DNode<E>* next;
	DNode<E>* previous;

	DNode(E element, DNode<E>* next, DNode<E>* previous)  {
		this->element = element;
		this->next = next;
		this->previous = previous;
	}
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
		this->previous = previous;
	}
};

