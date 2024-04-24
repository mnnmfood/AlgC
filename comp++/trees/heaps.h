#ifndef HEAP_H
#define HEAP_H

#include <vector>

#define Parent(i) (i-1) >> 1
#define Left(i) (i << 1) | (0x01)
#define Right(i) ((i << 1) | (0x01)) + 1

template<typename T>
class Heap
{
public:
	Heap() :size{ 2 } { resize(); }
	void resize() { size = 2 * size; A.reserve(size); }
	void max_heapify(int i) {
		int l = Left(i);
		int r = Right(i);
		int largest;
		if ((l < size) && (A[i] < A[l])) largest = l;
		else largest = i;
		if ((r < size) && (A[largest] < A[r])) largest = r;
		if (largest != i) {
			std::swap(A.begin() + i, A.begin() + largest);
			max_heapify(largest);
		}
	}

private:
	int size;
	std::vector<T> A;
};

#endif