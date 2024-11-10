/*
			Archivo: Clase KVPair
			Hecha en clase

			Descripci�n general: Una clase que contiene los atributos necesarios
			para poder crear un objeto llamado KVPair que despu�s se guardar�
			en un diccionario. Se detalla el funcionamiento de la asignaci�n
			las comparaciones entre objetos y la impresi�n.
*/

#pragma once
#include <iostream>

using std::ostream;

template <typename K, typename V>
class KVPair {
public:
	K key;
	V value;

	KVPair() {}
	KVPair(K key) {
		this->key = key;
	}
	KVPair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	void operator =(const KVPair<K, V> & other) {
		this->key = other.key;
		this->value = other.value;
	}
	bool operator==(const KVPair<K, V>& other) {
		return this->key == other.key;
	}
	bool operator!=(const KVPair<K, V>& other) {
		return this->key != other.key;
	}
	bool operator<(const KVPair<K, V>& other) {
		return this->key < other.key;
	}
	bool operator<=(const KVPair<K, V>&other){
		return this->key <= other.key;
	}
	bool operator>(const KVPair<K, V>& other) {
		return this->key > other.key;
	}
	bool operator>=(const KVPair<K, V>& other) {
		return this->key >= other.key;
	}
};

template <typename K, typename V>
ostream& operator <<(ostream& os, const KVPair<K, V>& pair) {
	os << "(" << pair.key << ", " << pair.value << ")";
	return os;
}