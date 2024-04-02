#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<typename T>
class SLLNode
{
public:
	SLLNode() { next = 0; }
	SLLNode(T i, SLLNode* p = 0) : info{ i }, next{ p } {}
	SLLNode* next;
	T info;
};


template<typename T>
class SLList
{
public:
	SLList() { head = tail = 0; }
	int isEmpty() { return head == 0; }
	void addToHead(const T& info) {
		head = new SLLNode(info, head);
		if (tail == 0) {
			tail = head;
		}
	}
	void addToTail(const T& info) {
		if (tail != 0) {
			tail->next = new SLLNode(info);
			tail = tail->next;
		}
		else tail = head = new SLLNode(info);
	}
	T deleteFromTail() {
		T elem = tail->info;
		if (head == tail) {
			delete tail;
			head = tail = 0;
		} // if more than one node
		else {
			SLLNode* temp;
			for (temp = head; temp != tail; temp = temp->next);
			delete tail;
			tail = temp;
			tail->next = 0;
		}
		return elem;
	}
	T deleteFromHead() {
		T elem = head->info;
		SLLNode* temp = head;
		if (head == tail) head = tail = 0;
		else head = head->next;
		delete temp;
		return elem;
	}
	void deleteNode(const T& info) {
		if (head != 0) {
			if (head == tail && head->info == info) {
				delete head;
				head = tail = 0;
			}
			else if (head->info == info) {
				SLLNode* temp = head;
				head = head->next;
				delete temp;
			}
			else {
				SLLNode* temp, * pred;
				for (temp = head->next, pred = head;
					temp != 0 && temp->info != info;
					temp = temp->next, pred = pred->next);
				if (temp != 0) {
					pred->next = temp->next;
					if (temp == tail) {
						tail = pred;
					}
					delete temp;
				}
			}
		}
	}
	bool isInList(const T& info) {
		SLLNode* temp = head;
		for (; temp != 0 && (temp->info != info); temp = temp->next);
		return temp != 0;
	}
	~SLList() {
		for (SLLNode* p; !isEmpty();) {
			p = head->next;
			delete head;
			head = p;
		}
	}
private:
	typedef SLLNode<T> SLLNode;
	SLLNode* head, * tail;
};


// Double linked lists are similar but nodes contain
// pointers to the next and previous node
template<typename T>
class DLLNode {
public:
	DLLNode() {
		next = prev = 0;
	}
	DLLNode(const T& el, DLLNode* n = 0, DLLNode* p = 0) {
		info = el; next = n; prev = p;
	}
	T info;
	DLLNode* next, * prev;
};

template<typename T>
class DLList
{
public:
	DLList() { head = tail = 0; }
	void addToTail(const T& el) {
		if (tail != 0) {
			tail = new DLLNode(el, 0, tail);
			tail->prev->next = tail;
		}
		else head = tail = new DLLNode(el);
	}
	T deleteFromTail() {
		T el = tail->info;
		if (head == tail) { // if only one node in the list;
			delete head;
			head = tail = 0;
		}
		else { // if more than one node in the list;
			tail = tail->prev;
			delete tail->next;
		}
		return el;
	}
	int isEmpty() { return head == 0; }
private:
	typedef DLLNode<T> DLLNode;
	DLLNode* head, * tail;
};

// Circulatr list: in a circular list the nodes are connected
// normally but the tail is connected to the first node. We only
// need to keep track of the tail. 
// If implemented with single links to delete the tail we would need
// to loop throught it to set the previous node to the new tail 
// and it would be O(n), so it is normally implemented as a double
// linked list. A method would be:
#if 0
void addToTail(int el) {
	if (isEmpty()) {
		tail = new IntSLLNode(el);
		tail->next = tail;
	}
	else {
		tail->next = new IntSLLNode(el, tail->next);
		tail = tail->next;
	}
}
#endif

#endif
