/*
			Archivo: Clase BSTNode
			Hecha en clase

			Descripci�n general: La clase del nodo del BSTree. Se crean nodos
			que tienen punteros para dos hijos. Adem�s, en esta clase se calcula
			si el nodo es una hoja y cu�ntos hijos tiene.
*/

#pragma once

template <typename E>
class BSTNode {
public:
	E element;
	BSTNode<E>* left;
	BSTNode<E>* right;

	BSTNode(E element) {
		this->element = element;
		left = nullptr;
		right = nullptr;
	}
	bool isLeaf() {
		return left == nullptr && right == nullptr;
	}
	int childrenCount() {
		return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
	}
	BSTNode<E>* onlyChild() {
		return left == nullptr? right : left;
	}

};

