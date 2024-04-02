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
	// we need to take into account that recursive implementations 
	// use the runtime stack and it can be easily overflowed by large
	// trees. User stacks can aliviate this problem, but they are harder
	// to program and understand.
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
	// There are some algorithms thay modify the tree while traversing it 
	// like the Morris traversal
	void MorrisInorder() {
		node* p = root, * tmp;
		while (p != 0)
			if (p->left == 0) {
				visit(p);
				p = p->right;
			}
			else {
				tmp = p->left;
				while (tmp->right != 0 && // go to the rightmost node
					tmp->right != p) // of the left subtree or
					tmp = tmp->right; // to the temporary parent
				if (tmp->right == 0) { // of p; if 'true'
					tmp->right = p; // rightmost node was
					p = p->left; // reached, make it a
				} // temporary parent of the
				else { // current root, else
					// a temporary parent has
					visit(p); // been found; visit node p
					tmp->right = 0; // and then cut the right
					// pointer of the current
					p = p->right; // parent, whereby it
				} // ceases to be a parent;
			}
	}
	// insertions are easy. Just like searchs.
	void insert(const T& el) {
		node* p = root, prev = 0;
		while (p != 0) {
			prev = p;
			if (el < p->el) p = p->left;
			else p = p->right;
		}
		if (root = 0) root = new node(el);
		if (el < prev->el) prev->left = new node(el);
		else prev->right = new node(el);
	}
	// -- Deletions are hard the more children a node has. If it has 2 children we
	// the parent's left or right pointer cannot point to both children.

	// Delete by merging: we combine the left and right subtrees of the deleted node.
	// We attach the right subtree with the node of the left subtree with the highest value.
	// This is necessarily the rightmost node of the left subtree. That is the first node with
	// no right child
	void deleteMerge(node* Node) {
		node* temp = Node;
		if (Node != 0) {
			if (!Node->right) {
				Node = Node->left;
			}
			else if (!Node->left) {
				Node = Node->right;
			}
			else
			{
				Node = Node->left;
				while (Node->right != 0) {
					Node = Node->right;
				}
				Node->right = temp->right;
				Node = temp;
				Node = Node->left;
			}
			delete temp;
		}
	}
	void findAndDeleteMerge(const T& el) {
		node* p = root, *prev = 0;
		while (p != 0) {
			if (p->el == el) break;
			prev = p;
			if (el < p->el) p = p->left;
			else p = p->right;
		}
		if (p != 0 && p->el == el) {
			deleteMerge(p);
		}
		else if (root != 0) std::cout << "el is not in the tree\n";
		else std::cout << "tree is empty\n";
	}
	// the obvious drawback is that the height increases with each deletion
	// makign the tree more unbalanced. The more unbalanced the tree the more
	// searching it aproaches O(n)

	// Delete by copy: we simply replace the value of the node with the value of 
	// the inmediate predecesor of the node, that is, the rightmost node of the left subtree
	// then delete said node
	void deleteCopy(node* Node) {
		node* temp = Node, * prev;
		if (Node != 0) {
			if (!Node->right) {
				Node = Node->left;
			}
			else if (!Node->left) {
				Node = Node->right;
			}
			else
			{
				temp = Node->left;
				prev = Node;
				while (temp->right != 0) {
					prev = temp;
					temp = temp->right;
				}
				Node->el = temp->el;
				if (prev == Node) prev->left = temp->left;
				else prev->right = temp->left;
			}
			delete temp;
		}
		// this method leaves the tree structure intact but it also has a drawback: 
		// it always deletes nodes from the left subtree leaving the right one untouched, 
		// so the tree can become unbalanced. This is fixed simply by alternating between 
		// the inmediate predecesor of the node to delete(rightmost node in left subtree)
		// and the inmediate successor (leftmost node in the right subtree).
		// If we do it symetrically the average search time is O(lgn) and if we do it
		// assymetrically it tends towards O(sqrt(n))
		
		// -- Tree balancing: unbalanced trees tend to O(n) (linked lists) so it is important
		// to keep them balanced. 
	}

private:
	typedef BSTNode<T> node;
	node* root;
};

#endif
