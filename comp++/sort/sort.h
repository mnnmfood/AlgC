#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>


template<typename T>
void Swap(T* arr1, T* arr2) {
	T temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

// -- Quicksort
template<typename T>
int Partition(T* arr, int p, int r) {
	T x = arr[r];
	int i = p - 1;
	for (int j{ p }; j < r; j++) {
		if (arr[j] <= x) {
			i++;
			Swap(arr + i, arr + j);
			//std::iter_swap(arr.begin() + i, arr.begin() + j);
		}
	}
	Swap(arr + i + 1, arr + r);
	return i + 1;
}
template<typename T>
void Quicksort(T* arr, int p, int r) {
	if (p < r) {
		int q = Partition(arr, p, r);
		Quicksort(arr, p, q - 1);
		Quicksort(arr, q + 1, r);
	}
}
template<typename T>
void Quicksort(std::vector<T>& arr) {
	Quicksort(arr.data(), 0, arr.size() - 1);
}

// -- Heapsort

#define Parent(i) (i-1) >> 1
#define Left(i) (i << 1) | (0x01)
#define Right(i) ((i << 1) | (0x01)) + 1

template<typename T>
void Max_heapify(T* arr, int i, int size) {
	int l = Left(i);
	int r = Right(i);
	int largest;
	if ((l < size) && (arr[i] < arr[l])) largest = l;
	else largest = i;
	if ((r < size) && (arr[largest] < arr[r])) largest = r;
	if (largest != i) {
		//std::iter_swap(A.begin() + i, A.begin() + largest);
		Swap(arr + i, arr + largest);
		Max_heapify(arr, largest, size);
	}
}
template<typename T>
void Build_max_heap(T* arr, int size) {
	for (int i{ size / 2 - 1 }; i >= 0; i--) {
		Max_heapify(arr, i, size);
	}
}
template<typename T>
void HeapSort(T* arr, int size) {
	Build_max_heap(arr, size);
	for (int i{ size - 1 }; i > 0; i--) {
		//std::iter_swap(A.begin(), A.begin() + i);
		Swap(arr, arr + i);
		size--;
		Max_heapify(arr, 0, size);
	}
}
template<typename T>
void HeapSort(std::vector<T>& arr) {
	HeapSort(arr.data(), arr.size());
}


#endif

