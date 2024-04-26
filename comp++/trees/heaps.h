#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <algorithm>
#include <limits>

#define Parent(i) (i-1) >> 1
#define Left(i) (i << 1) | (0x01)
#define Right(i) ((i << 1) | (0x01)) + 1

template<typename T>
class MaxHeap
{
public:
	MaxHeap(std::vector<T> arr)
		:A{ arr }, size{ static_cast<int>(arr.size()) }
	{
		restore_heap();
	}
	// O(nlogn)
	std::vector<T> sorted() {
		for (int i{ size - 1 }; i > 0; i--) {
			std::iter_swap(A.begin(), A.begin() + i);
			size--;
			max_heapify(0);
		}
		return A;
	}
	// Restores max-heap properties asumming that the sub-trees rooted at 
	// node i are heaps. O(lgn)
	void max_heapify(int i) {
		int l = Left(i);
		int r = Right(i);
		int largest;
		if ((l < size) && (A[i] < A[l])) largest = l;
		else largest = i;
		if ((r < size) && (A[largest] < A[r])) largest = r;
		if (largest != i) {
			std::iter_swap(A.begin() + i, A.begin() + largest);
			max_heapify(largest);
		}
	}
	// Floyd algorithm. Restores heap property for the whole array. O(n)
	void restore_heap() {
		for (int i{ size / 2 - 1 }; i >= 0; i--) {
			max_heapify(i);
		}
	}

private:
	int size;
	std::vector<T> A;
};

template<typename T>
struct el
{
	el(T k) : key{ k } {};
	T key;
};

template<typename T>
class HeapQueue
{
public:
	// Obtaining the max in queue is O(1)
	el<T> max(){
		assert((size > 0) && "heap underflow");
		return A[0];
	}
	// Excracting the max el is O(1) + O(logn) 
	el<T> extract_max() {
		assert((size > 0) && "heap underflow");
		el<T> max = A[0];
		A[0] = A[size - 1];
		size--;
		max_heapify(0);
		return max;
	}
	// Increasing is O(logn) because we traverse a simple path upwards
	void increase_key(int i, T key) {
		assert((A[i].key < key) && "New key is smaller than current key\n");
		A[i].key = key;
		while ((i > 0) && (A[int(Parent(i))].key < A[i].key)) {
			std::iter_swap(A.begin() + i, A.begin() + int(Parent(i)));
			i = Parent(i);
		}
	}
	// Insert: makes use of increase key. O(logn)
	void insert(T key) {
		A.push_back(el(MIN_VAL));
		size = A.size();
		increase_key(size - 1, key);
	}

	// Restores max-heap properties asumming that the sub-trees rooted at 
	// node i are heaps. O(lgn)
	void max_heapify(int i) {
		int l = Left(i);
		int r = Right(i);
		int largest;
		if ((l < size) && (A[i].key < A[l].key)) largest = l;
		else largest = i;
		if ((r < size) && (A[largest].key < A[r].key)) largest = r;
		if (largest != i) {
			std::iter_swap(A.begin() + i, A.begin() + largest);
			max_heapify(largest);
		}
	}
	// Floyd algorithm, Restores heap property for the whole array. O(n)
	void restore_heap() {
		for (int i{ size / 2 - 1 }; i >= 0; i--) {
			max_heapify(i);
		}
	}

private:
	T MIN_VAL = std::numeric_limits<T>::min();
	std::vector<el<T>> A;
	int size;
};

#endif