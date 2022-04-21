#include <iostream>
#include "RedBlackTree.h"

using namespace std;

int main() {
	RedBlackTree<int, int> tree;

	tree.insert(33, 1);
	tree.insert(13, 2);
	tree.insert(53, 3);
	tree.insert(11, 4);
	tree.insert(21, 5);
	tree.insert(41, 6);
	tree.insert(61, 7);
	tree.insert(15, 8);
	tree.insert(31, 9);
	tree.insert(20, 10);

	cout << "Red Black Tree:\n";
	tree.printtree();

	cout << "\nList of keys: ";
	Element_List<int>* temp = tree.getkeys()->head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;

	cout << "\nList of values: ";
	temp = tree.getvalues()->head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;

	cout << "\nTree after remove 20 and 33:\n";
	tree.remove(20);
	tree.remove(33);
	tree.printtree();

	tree.clear();
}