/*
			Archivo: Clase List
			Hecha en clase

			Descripción general: Una clase abstracta que contiene los
			métodos que se deberán implementar en las clases que la hereden.

			Modificación hecha por: Carmen Hidalgo Paz

			Descripción: Se agregaron los métodos indexOf() y contains(), que se
			implementarán en las clases que heredan a ésta.
*/


#pragma once

template <typename E>
class List {
private:
	List(const List<E>& other) {}
	void operator =(const List<E>& other) {}

public:
	List() {}
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual E remove() = 0;
	virtual E getElement() = 0;
	virtual void setElement(E element) = 0;
	virtual void clear() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atStart() = 0;
	virtual bool atEnd() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual bool isEmpty() = 0;
	virtual bool contains(E element) = 0;
	virtual void print() = 0;
};
