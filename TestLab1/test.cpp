#include "pch.h"
#include "gtest/gtest.h"
#include "..\Lab 1 real real\RedBlackTree.h"

TEST(Test_insert) {
	//When tree is empty
	RedBlackTree<int, int> tree1;
	tree1.insert(29, 7);
	ASSERT_EQ(tree1.root->key, 29);
	ASSERT_EQ(tree1.root->value, 7);

	RedBlackTree<int, int> tree2;
	tree2.insert(33, 1);
	tree2.insert(13, 2);
	tree2.insert(53, 3);
	tree2.insert(11, 4);

	Element_List<Element_RBT<int, int>*>* temp = tree2.allNodesbyDFT()->head;
	ASSERT_EQ(temp->data->key, 33);
	ASSERT_EQ(temp->data->value, 1);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 13);
	ASSERT_EQ(temp->data->value, 2);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 11);
	ASSERT_EQ(temp->data->value, 4);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 53);
	ASSERT_EQ(temp->data->value, 3);

	//Insert the same key
	ASSERT_THROW(tree2.insert(33, 5), logic_error);
}

TEST(Test_remove) {
	//When tree is empty
	RedBlackTree<int, int> tree1;
	ASSERT_THROW(tree1.remove(7), logic_error);

	RedBlackTree<int, int> tree2;
	tree2.insert(33, 1);
	tree2.insert(13, 2);
	tree2.insert(53, 3);
	tree2.insert(11, 4);
	tree2.insert(21, 5);
	tree2.remove(21);

	Element_List<Element_RBT<int, int>*>* temp = tree2.allNodesbyDFT()->head;
	ASSERT_EQ(temp->data->key, 33);
	ASSERT_EQ(temp->data->value, 1);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 13);
	ASSERT_EQ(temp->data->value, 2);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 11);
	ASSERT_EQ(temp->data->value, 4);
	temp = temp->next;
	ASSERT_EQ(temp->data->key, 53);
	ASSERT_EQ(temp->data->value, 3);

	//Remove nonexisting key
	ASSERT_THROW(tree2.remove(64), invalid_argument);
}

TEST(test_find) {
	//When tree is empty
	RedBlackTree<int, int> tree1;
	ASSERT_THROW(tree1.find(4), logic_error);

	RedBlackTree<int, int> tree2;
	tree2.insert(33, 1);
	tree2.insert(13, 2);
	tree2.insert(53, 3);
	tree2.insert(11, 4);

	ASSERT_EQ(tree2.find(53)->key, 53);
	ASSERT_EQ(tree2.find(53)->value, 3);

	//When key to find does not exist
	ASSERT_THROW(tree2.find(64), invalid_argument);
}

TEST(Test_getkeys) {
	RedBlackTree<int, int> tree;
	tree.insert(33, 1);
	tree.insert(13, 2);
	tree.insert(53, 3);
	tree.insert(11, 4);

	Element_List<int>* temp = tree.getkeys()->head;
	ASSERT_EQ(temp->data, 33);
	temp = temp->next;
	ASSERT_EQ(temp->data, 13);
	temp = temp->next;
	ASSERT_EQ(temp->data, 11);
	temp = temp->next;
	ASSERT_EQ(temp->data, 53);
}

TEST(Test_getvalues) {
	RedBlackTree<int, int> tree;
	tree.insert(33, 1);
	tree.insert(13, 2);
	tree.insert(53, 3);
	tree.insert(11, 4);

	Element_List<int>* temp = tree.getvalues()->head;
	ASSERT_EQ(temp->data, 1);
	temp = temp->next;
	ASSERT_EQ(temp->data, 2);
	temp = temp->next;
	ASSERT_EQ(temp->data, 4);
	temp = temp->next;
	ASSERT_EQ(temp->data, 3);
}

TEST(Test_clear) {
	RedBlackTree<int, int> tree;
	ASSERT_THROW(tree.clear(), logic_error);

	tree.insert(33, 1);
	tree.insert(13, 2);
	tree.insert(53, 3);
	tree.insert(11, 4);
	tree.clear();
	ASSERT_EQ(tree.root, tree.nil);
}