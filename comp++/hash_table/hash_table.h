#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <cmath>
#include <assert.h>

struct Mult_hash
{
	int w = 32; // word size
	uint32_t s = 2654435769;
	int p;
	Mult_hash() { p = 14; }
	Mult_hash(int _p) {
		assert((_p < 32) && "Exceeded size of hash");
		p = _p; 
	}

	uint32_t operator()(uint32_t key) {
		// size of mult is 2*w=64 bits but we only take first 32
		uint32_t r0 = s * key; 
		return r0 >> (32 - p);
	}
};

uint32_t encodeString(std::string s) {
	assert((s.size() < 5) && "Max length of key is 4 characters"); // max len is 
	uint32_t temp = 0;
	for (int i{ 0 }; i < s.size(); i++) {
		temp = temp | (static_cast<uint32_t>(s[i]) << (i * 8 * sizeof(s[0])));
	}
	return temp;
}

template<typename T>
struct elem
{
	uint32_t key;
	T data;
	int nil = 1;
	int deleted = 0;

	elem() :nil{ 1 }, deleted{ 0 } {};
	elem(uint32_t k, T d) :key{ k }, data{ d }, nil{ 0 }, deleted{ 0 } {}
};


template<typename T>
class HashTable
{
	int m = 0;
	int p = 1;
	int m_size= 0;
	elem<T>* D;
	Mult_hash hash1;

	uint32_t linear_hash(uint32_t key, uint32_t i) {
		return (hash1(key) + i) % m;
	}

public:
	HashTable() { 
		hash1 = Mult_hash(14);
		resize(); 
	}
	void resize() {
		p++;
		assert((p < 15) && "Reached max size of hash table\n");
		m = static_cast<uint32_t>(exp2(p));
		// Resize data array
		elem<T>* temp = D;
		D = new elem<T>[m];
		// Copy elements with new hash
		if (m_size > 0) {
			for (int i{ 0 }; i < m_size; i++) {
				elem<T> el = temp[i];
				if ((el.nil == 0) || (el.deleted == 0)) {
					insert(el.key, el.data);
				}
			}
		}
	}

	uint32_t insert(std::string s, T data) {
		uint32_t key = encodeString(s);
		return insert(key, data);
	}

	uint32_t insert(uint32_t key, T data){
		if (m_size == m) { resize(); }
		for (uint32_t i{ 0 }; i < m; i++) {
			//uint32_t j = linear_hash(key, i);
			uint32_t j = linear_hash(key, i);
			if (D[j].nil || D[j].deleted) {
				D[j] = elem(key, data);
				m_size++;
				return j;
			}
		}
	}

	uint32_t del(std::string s) {
		uint32_t key = encodeString(s);
		return del(key);
	}

	uint32_t del(uint32_t key) {
		for (uint32_t i{ 0 }; i < m; i++) {
			//uint32_t j = linear_hash(key, i);
			uint32_t j = linear_hash(key, i);
			if (D[j].nil) break;
			if (D[j].key == key) {
				D[j].deleted = 1;
				m_size--;
			}
		}
	}

	T operator[](std::string s){
		uint32_t key = encodeString(s);
		for (uint32_t i{ 0 }; i < m; i++) {
			//uint32_t j = linear_hash(key, i);
			uint32_t j = linear_hash(key, i);
			if (D[j].nil) break;
			if ((D[j].key == key)){
				if (D[j].deleted) return  T(-1);
				else return D[j].data;
			}
		}
		return T(-1);
	}
};

#endif
