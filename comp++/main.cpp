#include <iostream>
#include <random>
#include "linked_list/linked_list.h"
#include "stacks_queues/queue.h"
#include "trees/binary_tree.h"
#include "trees/red_black_tree.h"
#include "hash_table/hash_table.h"

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
	std::cout << "--- QUEUE\n";
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
	std::cout << "--- Linked List\n";
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

void testBSTree() {
	std::cout << "--- Binary Tree\n";
	int val = 0;
	BSTree<int> tree;
	tree.insert(val);
	std::cout << "Node 0: ";
	tree.inorder(tree.root);
	std::cout << "\n";
	val = 3;
	tree.insert(val);
	val = 5;
	tree.insert(val);
	val = 1;
	tree.insert(val);
	std::cout << "Nodes 0, 1, 3, 5: ";
	tree.inorder(tree.root);
	std::cout << "\n";
	BSTree<int>::node* p; 
	val = 3;
	p = tree.recursive_search(tree.root, val);
	std::cout << "Predecessor of node 3: " << tree.predecessor(p)->key << "\n";
	std::cout << "Successor of node 3: " << tree.successor(p)->key << "\n";
}

void testRBTree() {
	std::cout << "--- Red-Black Tree\n";
	int val = 0;
	RBTree<int> tree;
	tree.insert(val);
	std::cout << "Node 0: ";
	tree.inorder(tree.root);
	std::cout << "\n";
	val = 3;
	tree.insert(val);
	val = 5;
	tree.insert(val);
	val = 1;
	tree.insert(val);
	std::cout << "Nodes 0, 1, 3, 5: ";
	tree.inorder(tree.root);
	std::cout << "\n";
	RBTree<int>::node* p; 
	val = 0;
	p = tree.recursive_search(tree.root, val);
	std::cout << "Predecessor of node 0: " << tree.predecessor(p)->key << "\n";
	std::cout << "Successor of node 0: " << tree.successor(p)->key << "\n";
	tree.tdelete(p);
	std::cout << "Deleted node 3: ";
	tree.inorder(tree.root);
	std::cout << "\n";
}

void testHashTable() {
	std::cout << "--- Hash Table \n";
	HashTable<int> dict;
	dict.insert("uno", 1);
	dict.insert("dos", 1);
	dict.insert("tres", 1);
	dict.insert("cuat", 1);
	dict.insert("cinc", 1);
	std::cout << "Element with key 'cuatro': " << dict["cuatro"] << "\n";
}

int main()
{
	testLinkedList();
	testQueue();
	testHashTable();
	testBSTree();
	testRBTree();
}
