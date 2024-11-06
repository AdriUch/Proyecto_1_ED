#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "KVPair.h"
#include "BSTree.h"

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V> {
private:
	BSTree<KVPair<K, V>>* pairs;
public:
	BSTDictionary(const BSTDictionary<K, V>& other) = delete;
	void operator =(const BSTDictionary<K, V>& other) = delete;

	BSTDictionary() {
		pairs = new BSTree<KVPair<K, V>>();
	}
	~BSTDictionary() {
		delete pairs;
	}
	void insert(K key, V value) {
		KVPair<K, V> p(key, value);
		pairs->insert(p);
	}
	V remove(K key) {
		KVPair<K, V> p(key);
		p = pairs->remove(p);
		return p.value;
	}
	V getValue(K key) {
		KVPair<K, V> p(key);
		p = pairs->find(p);
		return p.value;
	}
	void setValue(K key, V value) {
		KVPair<K, V> p(key, value);
		pairs->remove(p);
		pairs->insert(p);
	}
	bool contains(K key) {
		KVPair<K, V> p(key);
		return pairs->contains(p);
	}
	List<K>* getKeys() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<K>* keys = new DLinkedList<K>();
		while (!items->atEnd()) {
			auto p = items->getElement();
			keys->append(p.key);
			items->next();
		}
		delete items; 
		return keys;
	}
	List<V>* getValues() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<V>* values = new DLinkedList<V>();
		while (!items->atEnd()) {
			auto p = items->getElement();
			values->append(p.value);
			items->next(); 
		}
		delete items;
		return values;
	}
	int getSize() {
		return pairs->getSize();
	}
	void print() {
		pairs->print();
	}
};

