#ifndef THREADED_TREE_H
#define THREADED_TREE_H

// For ordinary binary trees we need to use a stack
// in order to traeverse it. Threaded tress inorporate the stack as part
// of the tree. 
template<class T>
class ThreadedNode {
public:
	ThreadedNode() {
		left = right = 0;
	}
	ThreadedNode(const T& e, ThreadedNode* l = 0, ThreadedNode* r = 0) {
		el = e; left = l; right = r; successor = 0;
	}
	T el;
	ThreadedNode* left, * right;
	unsigned int successor : 1;
};
template<class T>
class ThreadedTree {
public:
	ThreadedTree() {
		root = 0;
	}
	void insert(const T&){
		ThreadedNode<T>* p, * prev = 0, * newNode;
		newNode = new ThreadedNode<T>(el);
		if (root == 0) { // tree is empty;
			root = newNode;
			return;
		}
		p = root; // find a place to insert newNode;
		while (p != 0) {
			prev = p;
			if (p->el > el)
				p = p->left;
			else if (p->successor == 0) // go to the right node only if it
				p = p->right; // is a descendant, not a successor;
			else break; // don’t follow successor link;
		}
		if (prev->el > el) { // if newNode is left child of
			prev->left = newNode; // its parent, the parent
			newNode->successor = 1; // also becomes its successor;
			newNode->right = prev;
		}
		else if (prev->successor == 1) {// if the parent of newNode
			newNode->successor = 1; // is not the rightmost node,
			prev->successor = 0; // make parent’s successor
			newNode->right = prev->right; // newNode’s successor,
			prev->right = newNode;
		}
		else prev->right = newNode; // otherwise it has no successor;
	}

	void inorder() {
		node* p = root;
		if (p != 0) { // process only nonempty trees;
			while (p->left != 0) // go to the leftmost node;
				p = p->left;
			while (p != 0) {
				visit(p);
				prev = p;
				p = p->right; // go to the right node and only
				if (p != 0 && prev->successor == 0) // if it is a
					while (p->left != 0)// descendant go to the
						p = p->left; // leftmost node, otherwise
			} // visit the successor;
		}
	}
protected:
	typedef ThreadNode node;
	node* root;
};
#endif