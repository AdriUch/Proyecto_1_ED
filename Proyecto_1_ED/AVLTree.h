/*
			Archivo: Clase AVLTree
			Hecha en clase

			Descripción general: La clase del árbol AVL. El árbol AVL busca siempre
			estar balanceado (para tener la menor altura posible) y por lo tanto tiene
			varias funciones que se encargan de manejar esto (rotateRight, rotateLeft,
			rebalanceRight y rebalanceLeft). Además tiene los métodos de insertar, borrar,
			buscar, etc. elementos para poder utilizar el árbol.
*/

#pragma once
#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

// Clase AVLTree: Implementa un árbol AVL que mantiene el equilibrio en cada operación.
template <typename E>
class AVLTree {
private:
	// Prevención de copia y asignación para garantizar que solo haya una instancia del árbol.
	AVLTree(const AVLTree<E>& other) {}
	void operator =(const AVLTree<E>& other) {}

	// Nodo raíz del árbol
	BSTNode<E>* root;

	// Función auxiliar para insertar un elemento en el árbol
	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element); // Inserta un nuevo nodo si es necesario

		// Prevención de duplicados (opcional, depende del caso de uso)
		if (element == current->element)
			throw runtime_error("Duplicated element.");
		
		// Inserción recursiva en el subárbol izquierdo o derecho
		if (element < current->element) {
			current->left = insertAux(current->left, element);
			return rebalanceLeft(current); // Rebalanceo del árbol tras la inserción
		} else {
			current->right = insertAux(current->right, element);
			return rebalanceRight(current);
		}
	}

	// Función auxiliar para verificar si un elemento está en el árbol
	bool containsAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return false; // Elemento no encontrado

		if (element == current->element)
			return true; // Elemento encontrado

		// Búsqueda recursiva en el subárbol izquierdo o derecho
		return element < current->element
			? containsAux(current->left, element)
			: containsAux(current->right, element);
	}

	// Función auxiliar para buscar y devolver un elemento específico
	E findAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			throw runtime_error("Element not found."); // Si no está, lanza una excepción
		
		if (element == current->element)
			return current->element; // Elemento encontrado

		// Búsqueda recursiva
		return element < current->element
			? findAux(current->left, element)
			: findAux(current->right, element);
	}

	// Función auxiliar para eliminar un elemento
	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found."); // Si no está, lanza una excepción

		// Búsqueda recursiva del nodo a eliminar
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return rebalanceRight(current);
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return rebalanceLeft(current);
		}

		// Nodo encontrado
		*result = current->element;
		int childrenCount = current->childrenCount();

		// Caso 1: Nodo sin hijos
		if (childrenCount == 0) {
			delete current;
			return nullptr;
		}

		// Caso 2: Nodo con un solo hijo
		if (childrenCount == 1) {
			BSTNode<E>* child = current->onlyChild();
			delete current;
			return child;
		}

		// Caso 3: Nodo con dos hijos
		BSTNode<E>* successor = findMin(current->right); // Busca el sucesor en el subárbol derecho
		swap(current, successor); // Intercambia los valores del nodo actual y el sucesor
		current->right = removeAux(current->right, element, result); // Elimina el sucesor
		return current;
	}

	// Encuentra el nodo con el menor valor en un subárbol
	BSTNode<E>* findMin(BSTNode<E>* current) {
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	// Intercambia los elementos de dos nodos
	void swap(BSTNode<E>* n1, BSTNode<E>* n2) {
		E temp = n1->element;
		n1->element = n2->element;
		n2->element = temp;
	}

	// Función auxiliar para limpiar el árbol recursivamente
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}

	// Obtiene los elementos en orden ascendente
	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}

	// Calcula el tamaño del árbol recursivamente
	int getSizeAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		return 1 + getSizeAux(current->left) + getSizeAux(current->right);
	}

	// Rotaciones para mantener el equilibrio
	BSTNode<E>* rotateRight(BSTNode<E>* current) {
		if (current->left == nullptr)
			throw runtime_error("Can't rotate right with null left child.");
		BSTNode<E>* temp = current->left;
		current->left = temp->right;
		temp->right = current;
		return temp;
	}
	BSTNode<E>* rotateLeft(BSTNode<E>* current) {
		if (current->right == nullptr)
			throw runtime_error("Can't rotate left with null right child.");
		BSTNode<E>* temp = current->right;
		current->right = temp->left;
		temp->left = current;
		return temp;
	}

	// Calcula la altura de un nodo
	int height(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		int lh = height(current->left);
		int rh = height(current->right);
		return 1 + (lh > rh ? lh : rh);
	}

	// Rebalanceo tras inserciones o eliminaciones
	BSTNode<E>* rebalanceLeft(BSTNode<E>* current) {
		int lh = height(current->left);
		int rh = height(current->right);
		if (lh - rh > 1) {
			int llh = height(current->left->left);
			int lrh = height(current->left->right);
			if (llh >= lrh) {
				return rotateRight(current);
			} else {
				current->left = rotateLeft(current->left);
				return rotateRight(current);
			}
		}
		return current;
	}
	BSTNode<E>* rebalanceRight(BSTNode<E>* current) {
		int rh = height(current->right);
		int lh = height(current->left);
		if (rh - lh > 1) {
			int rrh = height(current->right->right);
			int rlh = height(current->right->left);
			if (rrh >= rlh) {
				return rotateLeft(current);
			} else {
				current->right = rotateRight(current->right);
				return rotateLeft(current);
			}
		}
		return current;
	}

public:
	// Constructor y destructor
	AVLTree() : root(nullptr) {}
	~AVLTree() {
		clear();
	}

	// Inserta un elemento en el árbol
	void insert(E element) {
		root = insertAux(root, element);
	}

	// Verifica si un elemento está en el árbol
	bool contains(E element) {
		return containsAux(root, element);
	}

	// Busca un elemento en el árbol
	E find(E element) {
		return findAux(root, element);
	}

	// Elimina un elemento del árbol
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		return result;
	}

	// Limpia el árbol
	void clear() {
		clearAux(root);
		root = nullptr;
	}

	// Devuelve una lista con los elementos del árbol en orden ascendente
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>();
		getElementsAux(root, elements);
		return elements;
	}

	// Devuelve el tamaño del árbol
	int getSize() {
		return getSizeAux(root);
	}

	// Imprime los elementos del árbol
	void print() {
		List<E>* elements = getElements();
		elements->print();
		delete elements;
	}

	// Devuelve la altura del árbol
	int getHeight() {
		return height(root);
	}
};

