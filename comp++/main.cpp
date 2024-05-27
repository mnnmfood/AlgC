#include <iostream>
#include <random>
#include <algorithm>
#include "timer.h"
#include "linked_list/linked_list.h"
#include "stacks_queues/queue.h"
#include "trees/binary_tree.h"
#include "trees/red_black_tree.h"
#include "hash_table/hash_table.h"
#include "trees/b_tree.h"
#include "trees/heaps.h"
#include "trees/fibonacci_heap.h"
#include "graphs/Graph.h"
#include "sets/DisjForest.h"
#include "graphs/MST.h"
#include "graphs/single_shortest.h"
#include "graphs/pairs_shortest.h"
#include "graphs/max_flow.h"
#include "sort/sort.h"
#include "sort/sort_linear.h"

inline std::random_device rd{};
inline std::mt19937 gen{rd()};

template<typename T>
void fill(T* arr, int len, int range=10) {
	std::uniform_int_distribution unif{ 0, range };
	for (int i{ 0 }; i < len; i++) {
		arr[i] = static_cast<T>(unif(gen));
	}
}


void testSort() {
	std::cout << "--- Sorting\n";
	int size = 20;
	std::vector<int> s(size);
	fill(s.data(), size);
	std::vector<int> s1 = s;
	std::vector<int> s2 = s;
	std::vector<int> s3 = s;
	std::cout << "Original array: ";
	for (auto i : s) std::cout << i << ", ";
	
	std::cout << "\n";
	std::sort(s.begin(), s.end());
	std::cout << "Sorted array: ";
	for (auto i : s) std::cout << i << ", ";
	std::cout << "\n";
	
	Quicksort(s1);
	std::cout << "Quicksort: ";
	for (auto i : s1) std::cout << i << ", ";
	std::cout << "\n";

	HeapSort(s2);
	std::cout << "Heapsort: ";
	for (auto i : s2) std::cout << i << ", ";
	std::cout << "\n";

	std::cout << "-Merge Sort: ";
	MergeSort(s3);
	for (auto i : s3) std::cout << i << ", ";
	std::cout << "\n\n";
}

void testSortLinear() {
	std::cout << "--- Sorting Linear Time\n";
	int size = 10;
	int range = 10;
	std::vector<int> test(size);
	fill(test.data(), size, range);
	std::vector<int> test1 = test;

	std::cout << "Original array: ";
	for (auto i : test) std::cout << i << ", ";
	std::cout << "\n";

	std::cout << "Sorted array: ";
	std::sort(test.begin(), test.end());
	for (auto i : test) std::cout << i << ", ";
	std::cout << "\n";

	std::vector<int> res;
	CountingSort(test1, range, res);
	std::cout << "-Counting Sort: ";
	for (auto i : res) std::cout << i << ", ";
	std::cout << "\n\n";
	
	std::vector<uint32_t> test2(size);
	range = std::numeric_limits<int>::max();
	fill(test2.data(), size, range);
	std::vector<uint32_t> test3 = test2;

	std::cout << "Original array: ";
	for (auto i : test2) std::cout << i << ", ";
	std::cout << "\n";

	std::cout << "Sorted array: ";
	std::sort(test2.begin(), test2.end());
	for (auto i : test2) std::cout << i << ", ";
	std::cout << "\n";

	int r = 8; 
	std::vector<uint32_t> res2;
	RadixSort(test3, r, res2);
	std::cout << "-Radix Sort (r=8): ";
	for (auto i : res2) std::cout << i << ", ";
	std::cout << "\n\n";

	size = 30;
	std::vector<float> test4(size);
	fill(test4.data(), size, 100);
	for (auto& i : test4) i /= 100;
	std::vector<float> test5 = test4;
	std::vector<float> test6 = test4;

	std::cout << "Original array: ";
	for (auto i : test5) std::cout << i << ", ";
	std::cout << "\n";

	std::cout << "Sorted array: ";
	std::sort(test4.begin(), test4.end());
	for (auto i : test4) std::cout << i << ", ";
	std::cout << "\n";

	std::cout << "-Bucket Sort: ";
	std::list<float> res3;
	BucketSort(test5, res3);
	for (auto i : res3) std::cout << i << ", ";
	std::cout << "\n\n";
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
	typedef Graph::node node;
	Graph graph(9);
	graph.addEdgeUndir(0, 1, 4);
	graph.addEdgeUndir(1, 2, 8);
	graph.addEdgeUndir(2, 3, 7);
	graph.addEdgeUndir(3, 4, 9);
	graph.addEdgeUndir(4, 5, 10);
	graph.addEdgeUndir(5, 6, 2);
	graph.addEdgeUndir(6, 7, 1);
	graph.addEdgeUndir(7, 8, 7);

	graph.addEdgeUndir(1, 7, 11);
	graph.addEdgeUndir(6, 8, 6);
	graph.addEdgeUndir(8, 2, 2);
	graph.addEdgeUndir(2, 5, 4);
	graph.addEdgeUndir(3, 5, 14);

	std::vector<node*> path = graph.breadth_first(0, 5);
	std::cout << "Path (0, 5): ";
	for (auto i : path) std::cout << i->idx << "(dist=" << i->d << "), ";
	std::cout << "\n\n";
}

void testDisjForest() {
	std::cout << "--- Disjoint Forest\n";
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
	typedef Graph::node node;
	typedef Graph::edge edge;
	Graph graph(9);
	graph.addEdgeUndir(0, 1, 4);
	graph.addEdgeUndir(1, 2, 8);
	graph.addEdgeUndir(2, 3, 7);
	graph.addEdgeUndir(3, 4, 9);
	graph.addEdgeUndir(4, 5, 10);
	graph.addEdgeUndir(5, 6, 2);
	graph.addEdgeUndir(6, 7, 1);
	graph.addEdgeUndir(7, 8, 7);

	graph.addEdgeUndir(0, 7, 8);
	graph.addEdgeUndir(1, 7, 11);
	graph.addEdgeUndir(6, 8, 6);
	graph.addEdgeUndir(8, 2, 2);
	graph.addEdgeUndir(2, 5, 4);
	graph.addEdgeUndir(3, 5, 14);

	std::vector<edge> kurskal = Kruskal(graph);
	std::sort(kurskal.begin(), kurskal.end(), [](edge x, edge y) {return x.u->idx < y.u->idx; });
	std::cout << "Kruskal: ";
	for (auto edge : kurskal) {
		std::cout << "(" << edge.u->idx << ", " << edge.v->idx << ")  ";
	}
	std::cout << "\n";
	std::vector<edge> prim = Prim(graph);
	std::sort(prim.begin(), prim.end(), [](edge x, edge y) {return x.v->idx < y.v->idx; });
	std::cout << "Prim: ";
	for (auto edge : prim) {
		std::cout << "(" << edge.u->idx << ", " << edge.v->idx << ")  ";
	}
	std::cout << "\n\n";
}

void testSingleShortest() {
	std::cout << "--- Single Source Shortest Path \n";
	typedef Graph::node node;
	typedef Graph::edge edge;
	Graph graph(9);
	graph.addEdgeUndir(0, 1, 4);
	graph.addEdgeUndir(1, 2, 8);
	graph.addEdgeUndir(2, 3, 7);
	graph.addEdgeUndir(3, 4, 9);
	graph.addEdgeUndir(4, 5, 10);
	graph.addEdgeUndir(5, 6, 2);
	graph.addEdgeUndir(6, 7, 1);
	graph.addEdgeUndir(7, 8, 7);

	graph.addEdgeUndir(0, 7, 8);
	graph.addEdgeUndir(1, 7, 11);
	graph.addEdgeUndir(6, 8, 6);
	graph.addEdgeUndir(8, 2, 2);
	graph.addEdgeUndir(2, 5, 4);
	graph.addEdgeUndir(3, 5, 14);

	std::vector<GNode*> res;
	std::cout << "- Path from " << graph.node_list[0]->idx << " to " << graph.node_list[4]->idx << "\n";
	int bad = Bellman_Ford(graph, graph.node_list[0], graph.node_list[4], res);
	std::cout << "Bellman-Ford: ";
	for (auto node : res) {
		std::cout << node->idx << ", ";
	}
	std::cout << "\n";
	std::vector<GNode*> res2 = Dijkstra(graph, graph.node_list[0], graph.node_list[4]);
	std::cout << "Dijkstra: ";
	for (auto node : res2) {
		std::cout << node->idx << ", ";
	}
	std::cout << "\n\n";
}

void testPairShortest() {
	std::cout << "--- All Pairs Shortest Path \n";
	Graph graph(9);
	graph.addEdgeUndir(0, 1, 4);
	graph.addEdgeUndir(1, 2, 8);
	graph.addEdgeUndir(2, 3, 7);
	graph.addEdgeUndir(3, 4, 9);
	graph.addEdgeUndir(4, 5, 10);
	graph.addEdgeUndir(5, 6, 2);
	graph.addEdgeUndir(6, 7, 1);
	graph.addEdgeUndir(7, 8, 7);

	graph.addEdgeUndir(0, 7, 8);
	graph.addEdgeUndir(1, 7, 11);
	graph.addEdgeUndir(6, 8, 6);
	graph.addEdgeUndir(8, 2, 2);
	graph.addEdgeUndir(2, 5, 4);
	graph.addEdgeUndir(3, 5, 14);
	
	SqMatrix<int> L(graph.Vn);
	slow_all_pairs(graph.W, L);
	std::cout << "-Slow all pairs\n";
	std::cout << "Shortest Distance matrix: \n";
	std::cout << L;
	SqMatrix<int> pi(graph.Vn);
	Floyd_Warshall(graph.W, L, pi);
	int n = pi.rows();
	std::cout << "-Floyd Warshall\n";
	std::cout << "Shortest Distance matrix: \n";
	std::cout << L;
	std::cout << "Predecessor matrix: \n";
	std::cout << pi;
	std::cout << "- Path from " << 0 << " to " << 4 << ": ";
	std::cout << 4 << ", ";
	int i = 4;
	while (pi(0, i) != -1) {
		std::cout << pi(0, i) << ", ";
		i = pi(0, i);
	}
	std::cout << "\n\n";
}

void testTransitiveClosure() {
	std::cout << "--- Transitive Closure \n";
	Graph graph(4);
	graph.addEdgeDir(1, 2, 8);
	graph.addEdgeDir(1, 3, 8);
	graph.addEdgeDir(2, 1, 7);
	graph.addEdgeDir(3, 0, 7);
	graph.addEdgeDir(3, 2, 7);

	SqMatrix<int> T(graph.Vn);
	TransitiveClosure(graph, T);
	std::cout << T;
	std::cout << "\n";
}

void testMaxFlow() {
	std::cout << "--- Maximum Flow \n";
	FGraph graph(6, 0, 3);
	graph.addEdge(0, 1, 16);
	graph.addEdge(0, 5, 13);
	graph.addEdge(1, 2, 12);
	graph.addEdge(2, 3, 20);
	graph.addEdge(2, 5, 9);
	graph.addEdge(4, 3, 4);
	graph.addEdge(4, 2, 7);
	graph.addEdge(5, 4, 14);
	graph.addEdge(5, 1, 4);
	std::cout << "- Ford Fulkerson algorith:\n";
	graph.Ford_Fulkerson();
	std::cout << graph.A;
	std::cout << "- Relabel-to-Front \n";
	graph.Relabel_to_front();
	std::cout << graph.A;
}
int main()
{
	testSort();
	testSortLinear();
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
	testSingleShortest();
	testPairShortest();
	testTransitiveClosure();
	testMaxFlow();
}
