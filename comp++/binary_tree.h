#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template<typename T>
class BSTNode
{
public:
	BSTNode() { left = right = 0; }
	BSTNode(const T& e, BSTNode<T>* le = 0, BSTNode<T>* ri = 0)
		:el{ e }, left{ le }, rithgt{ ri }
	{}
	T el;
	BSTNode<T>* left, * right;
};

template<typename T>
class BSTree
{
public:
	BSTree() { node = 0; }
	T* search(node* p, const T& el) {
		while (p != 0) {
			if (p->el == el) return &(p->el);
			else if (el < p->el) p = p->left;
			else p = p->right;
		}
		return 0;
	}
private:
	typedef BSTNode<T> node;
	node* root;
};

#endif
