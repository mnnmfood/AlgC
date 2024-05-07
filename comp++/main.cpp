#include <iostream>
#include <random>
#include "linked_list/linked_list.h"
#include "stacks_queues/queue.h"
#include "trees/binary_tree.h"
#include "trees/red_black_tree.h"
#include "hash_table/hash_table.h"
#include "Advanced DS/b_tree.h"
#include "trees/heaps.h"
#include "trees/fibonacci_heap.h"
#include "graphs/Graph.h"
#include "sets/DisjForest.h"
#include "graphs/MST.h"

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
	std::cout << "Queue size 3\nEnqueue: 2, 3 \n";
	Queue<int> q(3);
	q.enqueue(2);
	q.enqueue(3);
	std::cout << "Is queue empty: " << (q.isEmpty() ? "True" : "False") << "\n";
	std::cout << "Is queue full: " << (q.isFull() ? "True" : "False") << "\n";
	std::cout << "Enqueue: 5 \n";
	q.enqueue(5);
	std::cout << "Is queue full: " << (q.isFull() ? "True" : "False") << "\n";
	int var = q.dequeue();
	std::cout << "First inserted: " << var << "\n";
	std::cout << "Enqueue 4" << "\n";
	q.enqueue(4);
	std::cout << "Elements in order: ";
	for (int i{ 0 }; i < 3; i++) std::cout << q.dequeue() << ", ";
	std::cout << "\n\n";
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
	std::cout << "Successor of node 3: " << tree.successor(p)->key << "\n\n";
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
	std::cout << "\n\n";
}

void testHashTable() {
	std::cout << "--- Hash Table \n";
	HashTable<int> dict;
	dict.insert("zero", 0);
	dict.insert("uno", 1);
	dict.insert("dos", 2);
	dict.insert("tres", 3);
	dict.insert("cuat", 4);
	dict.insert("cinc", 5);
	std::cout << "Element with key 'cuatro': " << dict["cuat"] << "\n\n";
}

void testBTree() {
	std::cout << "--- B-Tree \n";
	BTree<int, 3> tree;
	using res_t = BTree<int, 3>::return_t;
	for (int i{ 0 }; i < 23; i++) {
		tree.insert(2*i);
	}
	tree.insert(3);
	std::cout << "Nodes: ";
	tree.inorder(tree.root);
	res_t res = tree.search(tree.root, 3);
	std::cout << "\n";
	std::cout << "Find Node 3: ";
	std::cout << res.first->key[res.second] << "\n";
	std::cout << "\n";
	std::cout << "Delete Node 14: ";
	tree.del(tree.root, 14);
	tree.inorder(tree.root);
	std::cout << "\n\n";

}

void testHeap() {
	std::cout << "--- Heap Array\n";
	std::cout << "Original: ";
	std::vector<int> test = { 1, 4, 2 ,3, 9, 16, 10, 8, 7, 14 };
	for (auto i : test) std::cout << i << ", ";
	MaxHeap<int> heap(test);
	std::vector<int> sorted = heap.sorted();
	std::cout << "\nSorted: ";
	for (auto i : sorted) std::cout << i << ", ";
	std::cout << "\n\n";

	std::cout << "--- Heap Queue\n";
	HeapQueue<int> queue;
	for (auto i : test) queue.insert(i);
	std::cout << "Elements in order of priority: ";
	for (int i{ 0 }; i < test.size(); i++) std::cout << queue.extract_max().key << ", ";
	std::cout << "\n\n";

}

void testFibonacci() {
	std::cout << "--- Fibonacci Heap\n";
	typedef FibHeap<int>::node node;
	FibHeap<int> queue;
	std::cout << "Original: ";
	std::vector<int> test = { 1, 4, 2 ,3, 9, 16, 10, 8, 7, 14, 5, 20, 18};
	std::vector<node*> node_list;
	for (auto i : test) {
		std::cout << i << ", ";
		node_list.push_back(queue.insert(i));
	}
	std::cout << "\n\n";
	std::cout << "Extract first 3 elements in order of priority: ";
	for (int i{ 0 }; i < 2; i++) std::cout << queue.extract_min()->key << ", ";
	std::cout << "\n";
	queue.inorder();
	std::cout << "\n";
	int idx = 9;
	std::cout << "Decrease key " << test[idx] << " to " << 0 << "\n";
	queue.decrease_key(node_list[idx], 0);
	queue.inorder();
	std::cout << "\n";
	std::cout << "Extract rest of elements in order of priority: ";
	int size = queue.size();
	for (int i{ 0 }; i < size; i++) std::cout << queue.extract_min()->key << ", ";
	std::cout << "\n\n";
}

void testGraph() {
	std::cout << "--- Graph\n";
	typedef UndiGraph::node node;
	UndiGraph graph(9);
	graph.addEdge(0, 1, 4);
	graph.addEdge(1, 2, 8);
	graph.addEdge(2, 3, 7);
	graph.addEdge(3, 4, 9);
	graph.addEdge(4, 5, 10);
	graph.addEdge(5, 6, 2);
	graph.addEdge(6, 7, 1);
	graph.addEdge(7, 8, 7);

	graph.addEdge(1, 7, 11);
	graph.addEdge(6, 8, 6);
	graph.addEdge(8, 2, 2);
	graph.addEdge(2, 5, 4);
	graph.addEdge(3, 5, 14);

std::vector<node*> path = graph.breadth_first(0, 5);
	std::cout << "Path (0, 5): ";
	for (auto i : path) std::cout << i->idx << "(dist=" << i->d << "), ";
	std::cout << "\n\n";
}

void testDisjForest() {
	std::cout << "--- Disjunt Forest\n";
	typedef DisjForest<int>::node node;
	DisjForest<int> sets;
	std::vector<node*> nodes;
	for (int i{ 0 }; i < 10; i++) {
		nodes.push_back(new node(i));
		sets.Make_set(nodes[i]);
	}
	std::cout << "Before Unions: ";
	for (auto i: sets.roots) {
		std::cout << "(rank=" << i->rank << ", key=" << i->disj_key << ")  ";
	}
	std::cout << "\n";
	for (int i{ 0 }; i < 5; i++) {
		sets.Union(nodes[2*i], nodes[2*i+1]);
	}
	for (int i{ 0 }; i < sets.roots.size()-1; i++) {
		sets.Union(sets.roots[i], sets.roots[i+1]);
	}
	std::cout << "After Unions: ";
	for (auto i: sets.roots) {
		std::cout << "(rank=" << i->rank << ", key=" << i->disj_key << ")  ";
	}
	std::cout << "\n";
	std::cout << "Root of node " << nodes[7]->disj_key << ": ";
	std::cout << sets.Find_set(nodes[7])->disj_key;
	std::cout << "\n\n";
}

void testMST() {
	std::cout << "--- Minimum Spanning Tree \n";
	typedef UndiGraph::node node;
	typedef UndiGraph::edge edge;
	UndiGraph graph(9);
	graph.addEdge(0, 1, 4);
	graph.addEdge(1, 2, 8);
	graph.addEdge(2, 3, 7);
	graph.addEdge(3, 4, 9);
	graph.addEdge(4, 5, 10);
	graph.addEdge(5, 6, 2);
	graph.addEdge(6, 7, 1);
	graph.addEdge(7, 8, 7);

	graph.addEdge(0, 7, 8);
	graph.addEdge(1, 7, 11);
	graph.addEdge(6, 8, 6);
	graph.addEdge(8, 2, 2);
	graph.addEdge(2, 5, 4);
	graph.addEdge(3, 5, 14);

	std::vector<edge> kurskal = Kruskal(graph);
	std::cout << "Kruskal: ";
	for (auto edge : kurskal) {
		std::cout << "(" << edge.u->idx << ", " << edge.v->idx << ")  ";
	}
	std::cout << "\n";
	std::vector<edge> prim = Prim(graph);
	std::cout << "Kruskal: ";
	for (auto edge : prim) {
		std::cout << "(" << edge.u->idx << ", " << edge.v->idx << ")  ";
	}
	std::cout << "\n\n";
}

int main()
{
	testLinkedList();
	testQueue();
	testHashTable();
	testBSTree();
	testRBTree();
	testBTree();
	testHeap();
	testFibonacci();
	testGraph();
	testDisjForest();
	testMST();
}
