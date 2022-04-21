#pragma once
#include<iostream>
#include "List.h"
#include "Stack.h"

using namespace std;

enum class Color {
	RED,
	BLACK
};

template<class T1, class T2>
class Element_RBT {
public:
	Color color;
	T1 key;
	T2 value;
	Element_RBT* parent;
	Element_RBT* left;
	Element_RBT* right;

	Element_RBT() {
		this->color = Color::RED;
		this->key = 0;
		this->value = 0;
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
	}
};

template<class T1, class T2>
class RedBlackTree {
public:
	Element_RBT<T1, T2>* root;
	Element_RBT<T1, T2>* nil;

	RedBlackTree() {
		nil = new Element_RBT<T1, T2>();
		nil->color = Color::BLACK;
		root = nil;
		root->left = nil;
		root->right = nil;
	}

	void leftturn(Element_RBT<T1, T2>* X) {
		Element_RBT<T1, T2>* Y = X->right;
		Element_RBT<T1, T2>* B = Y->left;
		X->right = B;
		if (B != nil)
			B->parent = X;
		Element_RBT<T1, T2>* P = X->parent;
		Y->parent = P;
		if (P == NULL) 
			root = Y;
		else {
			if (P->left == X)
				P->left = Y;
			else if (P->right == X)
				P->right = Y;
		}
		Y->left = X;
		X->parent = Y;
	}

	void rightturn(Element_RBT<T1, T2>* Y) {
		Element_RBT<T1, T2>* X = Y->left;
		Element_RBT<T1, T2>* B = X->right;
		Y->left = B;
		if (B != nil)
			B->parent = Y;
		Element_RBT<T1, T2>* P = Y->parent;
		X->parent = P;
		if (P == NULL)
			root = X;
		else {
			if (P->left == Y)
				P->left = X;
			else if (P->right == Y)
				P->right = X;
		}
		X->right = Y;
		Y->parent = X;
	}

	void insert(T1 key, T2 value) {
		if (root == nil) {
			Element_RBT<T1, T2>* Node = new Element_RBT<T1, T2>;
			Node->key = key;
			Node->value = value;
			Node->color = Color::BLACK;
			Node->left = nil;
			Node->right = nil;
			root = Node;
		}
		else {
			Element_RBT<T1, T2>* Node = root;
			while (Node->left != nil || Node->right != nil) {
				if (key == Node->key)
					throw logic_error("This key is exist.");
				else if (key < Node->key) {
					if (Node->left != nil)
						Node = Node->left;
					else break;
				}
				else {
					if (Node->right != nil)
						Node = Node->right;
					else break;
				}
			}
			Element_RBT<T1, T2>* newNode = new Element_RBT<T1, T2>;
			newNode->key = key;
			newNode->value = value;
			newNode->left = nil;
			newNode->right = nil;
			newNode->parent = Node;
			if (newNode->key > Node->key)
				Node->right = newNode;
			else
				Node->left = newNode;
			newNode->color = Color::RED;
			fixtreeinsert(newNode);
		}
	}

	void fixtreeinsert(Element_RBT<T1, T2>* Node) {
		while (Node->parent->color == Color::RED) {
			Element_RBT<T1, T2>* Parent = Node->parent;
			Element_RBT<T1, T2>* GrandParent = Parent->parent;
			if (GrandParent->left == Parent) {
				if (GrandParent->right->color == Color::RED) {
					GrandParent->left->color = Color::BLACK;
					GrandParent->right->color = Color::BLACK;
					GrandParent->color = Color::RED;
					Node = GrandParent;
				}
				else {
					if (Parent->right == Node) {
						Node = Parent;
						leftturn(Node);
						Parent = Node->parent;
						GrandParent = Parent->parent;
					}
					Parent->color = Color::BLACK;
					GrandParent->color = Color::RED;
					rightturn(GrandParent);
				}
			}
			else if (GrandParent->right == Parent) {
				if (GrandParent->left->color == Color::RED) {
					GrandParent->left->color = Color::BLACK;
					GrandParent->right->color = Color::BLACK;
					GrandParent->color = Color::RED;
					Node = GrandParent;
				}
				else {
					if (Parent->left == Node) {
						Node = Parent;
						rightturn(Node);
						Parent = Node->parent;
						GrandParent = Parent->parent;
					}
					Parent->color = Color::BLACK;
					GrandParent->color = Color::RED;
					leftturn(GrandParent);
				}
			}
			if (Node == root)
				break;
		}
		root->color = Color::BLACK;
	}

	Element_RBT<T1, T2>* find(T1 key) {
		if (root == nil) {
			throw logic_error("Tree is empty.");
		}
		else {
			Element_RBT<T1, T2>* Node = root;
			bool check = 0;
			while (Node != nil) {
				if (key == Node->key) {
					check = 1;
					break;
				}
				else if (key < Node->key)
					Node = Node->left;
				else
					Node = Node->right;
			}
			if (check == 0)
				throw invalid_argument("Key does not exist in the tree.");
			else
				return Node;
		}
	}

	void remove(T1 key) {
		if (root == nil)
			throw logic_error("Tree is empty.");
		else {
			Element_RBT<T1, T2>* Node = find(key);
			Element_RBT<T1, T2>* x;
			Color originalColor = Node->color;
			if (Node->left == nil) {
				delete Node->left;
				x = Node->right;
				if (Node->parent->left == Node)
					Node->parent->left = x;
				else if (Node->parent->right == Node)
					Node->parent->right = x;
				x->parent = Node->parent;
			}
			else if (Node->right == nil) {
				delete Node->right;
				x = Node->left;
				if (Node->parent->left == Node)
					Node->parent->left = x;
				else if (Node->parent->right == Node)
					Node->parent->right = x;
				x->parent = Node->parent;
			}
			else {
				Element_RBT<T1, T2>* y = Node->right;
				while (y->left != nil)
					y = y->left;
				if (y == Node->right)
					originalColor = Node->color;
				else 
					originalColor = y->color;
				x = y->right;
				if (y->parent == Node) {
					x->parent = y;
					y->left = Node->left;
					y->right = x;
				}
				else {
					if (y->parent->right == y)
						y->parent->right = x;
					else if (y->parent->left == y)
						y->parent->left = x;
					y->left = Node->left;
					y->right = Node->right;
				}
				if (Node->parent->right == Node)
					Node->parent->right = y;
				else if (Node->parent->left == Node)
					Node->parent->left = y;
				y->parent = Node->parent;
				y->color = originalColor;
			}
			if (originalColor == Color::BLACK)
				fixtreeremove(x);
			delete Node;
		}
	}

	void fixtreeremove(Element_RBT<T1, T2>* Node) {
		Element_RBT<T1, T2>* w;
		while (Node != root && Node->color != Color::BLACK) {
			if (Node->parent->left = Node) {
				w = Node->parent->right;
				if (w->color == Color::RED) {
					w->color = Color::BLACK;
					Node->parent->color = Color::RED;
					leftturn(Node->parent);
					w = Node->parent->right;
				}
				else if (w->left->color == Color::BLACK && w->right->color == Color::BLACK){
					w->color = Color::RED;
					Node = Node->parent;
				}
				else if (w->right->color == Color::BLACK) {
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					rightturn(w);
					w = Node->parent->right;
				}
				else {
					w->color = Node->parent->color;
					Node->parent->color = Color::BLACK;
					w->right->color = Color::BLACK;
					leftturn(Node->parent);
					Node = root;
				}
			}
			else if (Node->parent->right = Node) {
				w = Node->parent->left;
				if (w->color == Color::RED) {
					w->color = Color::BLACK;
					Node->parent->color = Color::RED;
					rightturn(Node->parent);
					w = Node->parent->left;
				}
				else if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
					w->color = Color::RED;
					Node = Node->parent;
				}
				else if (w->left->color == Color::BLACK) {
					w->right->color = Color::BLACK;
					w->color = Color::RED;
					leftturn(w);
					w = Node->parent->left;
				}
				else {
					w->color = Node->parent->color;
					Node->parent->color = Color::BLACK;
					w->left->color = Color::BLACK;
					rightturn(Node->parent);
					Node = root;
				}
			}
			Node->color = Color::BLACK;
		}
	}

	List<Element_RBT<T1, T2>*>* allNodesbyDFT() {
		List<Element_RBT<T1, T2>*>* list = new List<Element_RBT<T1, T2>*>;
		Stack<Element_RBT<T1, T2>*>* stack = new Stack<Element_RBT<T1, T2>*>;
		Element_RBT<T1, T2>* temp = root;
		while (temp != nil) {
			list->pushback(temp);
			if (temp->right != nil)
				stack->push(temp->right);
			if (temp->left != nil)
				temp = temp->left;
			else {
				if (!stack->isEmpty())
					temp = stack->pop();
				else
					temp = nil;
			}
		}
		return list;
	}

	void printtree() {
		if (root == nil)
			cout << "Tree is empty.";
		else {
			List<Element_RBT<T1, T2>*>* listNode = allNodesbyDFT();
			while (listNode->head != NULL) {
				cout << "(Key: " << listNode->head->data->key << ", Value: " << listNode->head->data->value << ")\n";
				listNode->popfront();
			}
		}
	}

	List<T1>* getkeys() {
		List<T1>* listKey = new List<T1>;
		List<Element_RBT<T1, T2>*>* listNode = allNodesbyDFT();
		Element_List<Element_RBT<T1, T2>*>* temp = listNode->head;
		while (temp != NULL) {
			listKey->pushback(temp->data->key);
			temp = temp->next;
		}
		return listKey;
	}

	List<T2>* getvalues() {
		List<T2>* listValue = new List<T2>;
		List<Element_RBT<T1, T2>*>* listNode = allNodesbyDFT();
		Element_List<Element_RBT<T1, T2>*>* temp = listNode->head;
		while (temp != NULL) {
			listValue->pushback(temp->data->value);
			temp = temp->next;
		}
		return listValue;
	}

	void clear() {
		if (root == nil)
			throw logic_error("The tree is already empty.");
		else {
			Element_RBT<T1, T2>* current = root;
			Stack<Element_RBT<T1, T2>*>* stack = new Stack<Element_RBT<T1, T2>*>;
			while (current != nil) {
				if (current->right != nil)
					stack->push(current->right);
				if (current->left != nil) {
					Element_RBT<T1, T2>* temp = current->left;
					delete current;
					current = temp;
				}
				else if (!stack->isEmpty()) {
					delete current;
					current = stack->pop();
				}
				else {
					delete current;
					current = nil;
				}
			}
			root = current;
		}
	}
};