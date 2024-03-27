#ifndef QUEUE_H
#define QUEUE_H

template<typename T, size_t size = 100>
class Queue
{
public: 
	Queue() : first{ -1 }, last{ -1 } {}
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
private:
	T data[size];
	int first, last;
};

#endif
