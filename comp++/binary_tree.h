#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "queue.h"
#include "stack.h"

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

	// -- Traversals
	// Breath-first: top-down and lef-right
	void breadthFirst() {
		Queue<node*> queue;
		node* p = root;
		while (p != 0) {
			queue.enqueue(p);
			while (!queue.isEmpty()) {
				p = queue.dequeue();
				// visit(p)
				if (p->left != 0) queue.enqueue(p->left);
				if (p->right != 0) queue.enqueue(p->right);
			}
		}
	}
	// Depth-first: proceeds all the way to the left then backs up to 
	// the first intersection and chooses the other side if it exists
	// and goes all the way again. Types:
	// VLR: visit left right (preorder)
	// LVR: left visit right (inorder)
	// LRV: left right visit (postorder)
	// and all the combinations for example RVL, VRL...
	// Where V=visiting the node, and L, R = traversing the left or right
	// subtree

	// Recursive implementation
	void inorder(node* p) {
		if (p != 0) {
			inorder(p->left);
			// visit(p);
			inorder(p->right);
		}
	}
	void preorder(node* p) {
		if (p != 0) {
			//visit(p);
			preorder(p->left);
			preorder(p->right);
		}
	}
	void postorder(node* p) {
		if (p != 0) {
			postorder(p->left);
			postorder(p->right);
			//visit(p);
		}
	}
	// Stack implementation
	void inorder() {
		node* p = root;
		Stack<node*> stack;
		while (p != 0) {
			while (p != 0) {
				if(p->right!=0)
					stack.push(p->right);
				stack.push(p);
				p = p->left;
			}
			p = stack.pop(); // first node with no left 
			while (p != 0 && p->right == 0) {
				// visit(p);
				p = stack.pop();
			}
			// first node with a right
			// visit(p)
			if (!stack.isEmpty()) {
				p = stack.pop();
			}
			else p = 0;
		}
	}

private:
	typedef BSTNode<T> node;
	node* root;
};

#endif
