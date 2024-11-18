/*
            Archivo: Clase SNode
            Hecha en clase

            Descripci�n general: La clase del nodo del �rbol Splay. Se crean nodos
            que tienen punters a dos hijos y al padre. Tambi�n se puede contar la
            cantidad de hijos que tiene un nodo y se puede obtener un hijo.
*/

#ifndef SNODE_H
#define SNODE_H

template <typename E>
class SNode {
public:
    SNode<E> *left;
    SNode<E> *right;
    SNode<E> *parent;
    E element;

    SNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    int childrenCount() {
        return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
    }
    SNode<E>* getUniqueChild() {
        return (left == nullptr? right : left);
    }
};

#endif // SNODE_H
