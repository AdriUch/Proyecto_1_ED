/*
			Archivo: Clase List
			Hecha en clase

			Descripci�n general: Una clase abstracta que contiene los
			m�todos que se deber�n implementar en las clases que la hereden.

			Modificaci�n hecha por: Carmen Hidalgo Paz

			Descripci�n: Se agregaron los m�todos indexOf() y contains(), que se
			implementar�n en las clases que heredan a �sta.
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
