#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue
{
public: 
	Queue(int n) : size{ n }, first{ -1 }, last{ -1 } {
		data = new T[size];
	}
	int isFull() { return (first == 0 && last == size - 1) || (first == last + 1); }
	int isEmpty() { return first == -1; }
	void enqueue(T el){
		if (!isFull()) {
			if (last == -1 || last == size - 1) {
				data[0] = el;
				last = 0;
				if (first == -1) first = 0;
			}
			else data[++last] = el;
		}
	}
	T dequeue() {
		if (!isEmpty()) {
			T temp = data[first];
			if (first == size - 1) {
				first = 0;
			}
			else if (first == last) {
				first = last = -1;
			}
			else first++;
			return temp;
		}
	}
	~Queue() { delete data; }
private:
	int size;
	T* data;
	int first, last;
};

#endif
