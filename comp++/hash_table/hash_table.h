#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <cmath>
#include <assert.h>

struct Mult_hash
{
	int w = 32; // word size
	float A = (sqrt(5) - 1) / 2;
	uint32_t s = 2654435769;
	int p;
	Mult_hash() { p = 2; }
	Mult_hash(uint32_t m)
	{
		p = static_cast<int>(ceil(log2(static_cast<float>(m))));
		assert((p < 32) && "Size of hash table exceeds limit");
	}

	uint32_t operator()(uint32_t key) {
		uint64_t tmp = s * key;
		uint32_t r0 = tmp;
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
	int nil;
	int deleted = 0;

	elem() :nil{ 1 } {};
	elem(uint32_t k, T d) :key{ k }, data{ d }, nil{ 0 } {}
};


template<typename T>
class HashTable
{
	uint32_t m = 0;
	uint32_t p = 1;
	std::vector<elem<T>> D;
	Mult_hash hash;
	
	uint32_t linear_hash(uint32_t key, uint32_t i) {
		return (hash(key) + i) % m;
	}

public:
	HashTable() { resize(); }
	void resize() {
		p++;
		m = static_cast<uint32_t>(exp(p));
		D.resize(m);
		hash = Mult_hash(m);
	}

	uint32_t insert(std::string s, T data) {
		uint32_t key = encodeString(s);
		if (D.size() == m) { resize(); }
		for (uint32_t i{ 0 }; i < m; i++) {
			uint32_t j = linear_hash(key, i);
			if (D[j].nil) {
				D[j] = elem(key, data);
				return j;
			}
		}

	}

	T operator[](std::string s){
		uint32_t key = encodeString(s);
		for (uint32_t i{ 0 }; i < m; i++) {
			uint32_t j = linear_hash(key, i);
			if (D[j].key == key) {
				return D[j].data;
			}
		}
		return T(-1);
	}
};

#endif
