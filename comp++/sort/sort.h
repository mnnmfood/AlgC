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


// -Merge sort

template<typename T>
void Merge(T* A, int p, int q, int r) {
	// from p to q
	int n1 = q - p + 1;
	T* L = new T[n1 + 1];
	// from q to r
	int n2 = r - q;
	T* R = new T[n2 + 1];
	
	for (int i{ 0 }; i < n1; i++) {
		L[i] = A[p + i];
	}
	for (int i{ 0 }; i < n2; i++) {
		R[i] = A[q + i + 1];
	}
	L[n1] = std::numeric_limits<T>::max();
	R[n2] = std::numeric_limits<T>::max();
	
	int i = 0, j = 0;
	for (int k{ p }; k < r + 1; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
	}

	delete L;
	delete R;
}

template<typename T>
void MergeSort(T* A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}

template<typename T>
void MergeSort(std::vector<T>& A) {
	MergeSort(A.data(), 0, A.size() - 1);
}




#endif

