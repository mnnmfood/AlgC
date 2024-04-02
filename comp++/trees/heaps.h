#ifndef HEAP_H
#define HEAP_H

// Heaps can be implemented as simple arrays. The nodes are ordered from top to bottom
// and in each level from left to right, so that:
// heap[i] > heap[2*i+1]
// heap[i] > heap[2*i+2]
//
// This algo is the key to the heap sort. It restores the heap property if it has been 
// violated by the root. The root element is moved down the tree until it finds a position
//
template<class T>
void moveDown(T data[], int first, int last) {
	int largest = 2 * first + 1;
	while (largest <= last) {
		if (largest < last && // first has two children (at 2*first+1 and
			data[largest] < data[largest + 1]) // 2*first+2) and the second
			largest++; // is larger than the first;
		if (data[first] < data[largest]) { // if necessary,
			swap(data[first], data[largest]); // swap child and parent,
			first = largest; // and move down;
			largest = 2 * first + 1;
		}
		else largest = last + 1; // to exit the loop: the heap property
	} // isn’t violated by data[first];
}

// Floyd algorith transforms any array into a heap
template<class T>
void FloydAgorithm(T data[], int n) {
	for (int i = n / 2 - 1; i == 0; i--) {
		moveDown(data, i, n - 1);
	}
}

#endif