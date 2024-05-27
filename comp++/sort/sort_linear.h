#ifndef SORT_LINEAR_H
#define SORT_LINEAR_H

#include <vector>
#include <list>
#include <iostream>
#include <cmath>

// Counting Sort
template<typename T>
void CountingSort(T* A, int n, int k, T* B) {
	// sort array A with number in range (0, k)
	std::vector<T> C(k + 1);
	for (auto i : C) i = 0;
	for (int i{ 0 }; i < n; i++) {
		C[A[i]]++;
	}
	for (int i{ 1 }; i < k+1; i++) {
		C[i] += C[i - 1]; // number of elements less or equal to i
	}
	for (int j{ n - 1 }; j >= 0; j--) {
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}
}

template<typename T>
void CountingSort(std::vector<T>& A, int k, std::vector<T>& B) {
	B.resize(A.size());
	CountingSort(A.data(), A.size(), k, B.data());
}

// Radix Sort
// first we need a counting sort that uses d digits of the number

#define mask_and_shift(A, mask, r) (A & mask) >> r 

template<typename T>
void CountingSortBits(T* A, int n, int r, int idx, T* B) {
	int from = r * idx; // using bits from k*idx to k*idx + k
	uint64_t mask_64;
	mask_64 = ~(mask_64 & 0) >> (64 - r); // first k bits to 1
	int k = static_cast<int>(mask_64); // max number using k bits
	mask_64 = mask_64 << from;
	T mask = static_cast<T>(mask_64);
	
	// sort array A with number in range (0, k)
	std::vector<T> C(k + 1);
	for (auto i : C) i = 0;
	for (int i{ 0 }; i < n; i++) {
		int test1 = A[i];
		int test2 = A[i] & mask;
		int ind = mask_and_shift(A[i], mask, from);
		C[ind]++;
	}
	for (int i{ 1 }; i < k+1; i++) {
		C[i] += C[i - 1]; // number of elements less or equal to i
	}
	for (int j{ n - 1 }; j >= 0; j--) {
		int ind = mask_and_shift(A[j], mask, from);
		B[C[ind] - 1] = A[j];
		C[ind]--;
	}
}

template<typename T>
void RadixSort(std::vector<T>& A, int r, std::vector<T>& B) {
	B.resize(A.size());
	int d = sizeof(T) * 8 / r;
	for (int i{ 0 }; i < d; i++) {
		CountingSortBits(A.data(), A.size(), r, i, B.data());
		A = B;
	}
}

// -- Bucket sort

template<typename T>
void InsertionSort(std::list<T>& A) {
	typedef std::list<T>::iterator it_t;
	typedef std::list<T>::reverse_iterator rit_t;
	if (A.size() > 0) {
		it_t j = A.begin();
		j++;
		for (; j != A.end(); j++) {
			T temp = *j;
			rit_t i = std::make_reverse_iterator(j);
			rit_t i_next = i;
			i_next--;
			while ((i != A.rend()) && (*i > temp)) {
				*i_next = *i;
				i++;
				i_next++;
			}
			*i_next = temp;
		}
	}
}

template<typename T>
inline int to_bucket(T a, int n) {
	return static_cast<int>(floor(n * a));
}

template<typename T>
void BucketSort(T* A, int n, std::list<T>& C){
	C.resize(0);
	std::vector<std::list<T>> B(n);
	for (int i{ 0 }; i < n; i++) {
		B[to_bucket(A[i], n-1)].push_back(A[i]);
	}
	for (int i{ 0 }; i < n; i++) {
		InsertionSort(B[i]);
		C.splice(C.end(), B[i]);
	}
}

template<typename T>
void BucketSort(std::vector<T>& A, std::list<T>& C) {
	BucketSort(A.data(), A.size(), C);
}

#endif
