#include <iostream>
#include <random>
#include "linked_list.h"
#include "queue.h"

inline std::random_device rd{};
inline std::mt19937 gen{rd()};
std::uniform_int_distribution unif{ 1, 10 };

template<typename T>
void fill(T* arr, int len) {
	for (int i{ 0 }; i < len; i++) {
		arr[i] = static_cast<T>(unif(gen));
	}
}

void testQueue() {
	Queue<int, 3> q;
	q.enqueue(2);
	q.enqueue(3);
	std::cout << "Is queue empty: " << (q.isEmpty() ? "True" : "False") << "\n";
	q.enqueue(5);
	std::cout << "Is queue full: " << (q.isFull() ? "True" : "False") << "\n";
	int var = q.dequeue();
	std::cout << "First inserted: " << var << "\n";
	std::cout << "\n";
}

void testLinkedList() {
	SLList<int> l;
	l.addToHead(10);
	l.addToHead(2);
	std::cout << "Is 2 in list: " << (l.isInList(2) ? "True" : "False") << "\n";
	l.deleteNode(2);
	std::cout << "Is 2 in list: " << (l.isInList(2) ? "True" : "False") << "\n";
	l.deleteFromHead();
	std::cout << "Is list empty: " << (l.isEmpty() ? "True" : "False") << "\n";

	DLList<int> dl;
	dl.addToTail(10);
	dl.addToTail(2);
	std::cout << "Is list empty: " << (dl.isEmpty() ? "True" : "False") << "\n";
	dl.deleteFromTail();
	std::cout << "Is list empty: " << (dl.isEmpty() ? "True" : "False") << "\n";
	dl.deleteFromTail();
	std::cout << "Is list empty: " << (dl.isEmpty() ? "True" : "False") << "\n";
	std::cout << "\n";
}


int main()
{
	testLinkedList();
	testQueue();
}
