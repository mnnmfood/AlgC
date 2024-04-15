#ifndef TREE_H
#define TREE_H

template<typename T>
class BSNode
{
	typedef BSNode<T> node;
public:
	BSNode(T& val) :key { val } {}
	BSNode(node* le, node* ri, node*pa) 
		: left{ le }, right{ ri }, parent{ pa } {}
	
	node* left = 0, *right = 0, *parent = 0;
	T key;
};

template<typename T>
class BSTree
{
public:
	typedef BSNode<T> node;
	BSTree() {
	}

	// -- Tree traversal O(n)
	// Where V=visiting the node, and L, R = traversing the left or right
	// VLR: visit left right (preorder)
	// LVR: left visit right (inorder)
	// LRV: left right visit (postorder)
	// and all the combinations for example RVL, VRL...

	// Inorder: visit all the way left, print, then right. 
	void inorder(node* p) {
		if (p != 0) {
			inorder(p->left);
			// visit node
			std::cout << p->key << ", ";
			inorder(p->right);
		}
	}
	
	// -- Tree search 
	// O(h) where h==height of tree 
	// If the tree is balanced h = lg(n) so 
	// O(h) == O(logn)
	node* recursive_search(node* p, T& val) {
		if (p == 0 || p->key == val) {
			return p;
		}
		if (p->key > val) return recursive_search(p->left, val);
		else return recursive_search(p->right, val);
	}
	node* iter_search(T& val) {
		node* p = root;
		while (p != 0 || p->key != val) {
			if (p->key > val) p = p->left;
			else p = p->right;
		}
		return p;
	}
	// --- Minimum and maximum	O(h)
	node* min(node* p) {
		while (p->left != 0) {
			p = p->left;
		}
		return p;
	}
	node* max(node* p) {
		while (p->right != 0) {
			p = p->right;
		}
		return p;
	}

	// --- Successor and Predecessor O(h)
	// Successor: the node with the smallest key greater than p	
	// Predecessor: the node with the highest key smaller than p
	node* successor(node* p) {
		if (p->right != 0) {
			return min(p->right);
		}
		node* temp = p->parent;
		while (temp != 0 && p == temp->right) {
			p = temp;
			temp = p->parent;
		}
		return temp;
	}
	node* predecessor(node* p) {
		if (p->left != 0) {
			return max(p->left);
		}
		node* temp = p->parent;
		while (temp != 0 && p == temp->left) {
			p = temp;
			temp = p->parent;
		}
		return temp;
	}
	
	// --- Insertion O(h)
	void insert(T& val) {
		node* p = root;
		node* trail = 0; // trailing node
		while (p != 0) {
			trail = p;
			if (p->key > val) { p = p->left; }
			else p = p->right;
		}
		if (trail == 0) {
			root = new node(val); // tree is empty
		}
		else if (val < trail->key) { trail->left = new node(val); }
		else { trail->right = new node(val); }
	}
	// --- Deletion O(h)
	// node deletion is harder. It has 3 cases:
	//	1-p has no children: just set parent left/right to nill 
	//	2-p has 1 child: replace p with p's child
	//	3-p has 2 children: find succesor of p (must be in its right subtree):
	//		s=successor, r=right, l=left, x=s->right
	//		3.1 s==r: replace p by s and set l = s->l
	//		3.2 s!=r: replace s by x and p by s
	//  Helper function to replace node u with v
	void transplant(node* u, node* v) {
		if (u->parent == 0) { root = v; }
		else if (u == u->parent->left) { u->parent->left = v; }
		else if (u == u->parent->right) { u->parent->right = v; }
		if (v != 0) { v->parent = u->parent; }
	}

	void tdelete(node* p) {
		if (p->left == 0) { transplant(p, p->right); }
		else if (p->right == 0) { transplant(p, p->left); }
		else {
			node* s = min(p->right);
			if (s != p->right) {
				// 3.2
				transplant(s, s->right);
				s->right = p->right;
				p->right->parent = s;
			}
			// 3.1
			transplant(p, s);
			s->left = p->left;
			s->left->parent = s;
		}
		delete p;
	}
	node* root = 0;
};
#endif
