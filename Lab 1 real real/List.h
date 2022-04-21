#pragma once
#include <iostream>
using namespace std;

template<class T>
class Element_List {
public:
	T data;
	Element_List* prev;
	Element_List* next;

	Element_List() {
		this->data = 0;
		this->prev = NULL;
		this->next = NULL;
	}
};

template<class T>
class List {
public:
	Element_List<T>* head;
	Element_List<T>* tail;

	List() {
		this->head = NULL;
		this->tail = NULL;
	}

	bool isEmpty() {
		if (head == NULL && tail == NULL)
			return true;
		else if (head != NULL && tail != NULL)
			return false;
		else
			throw logic_error("Error");
	}

	void pushback(T data) {
		if (isEmpty()) {
			Element_List<T>* Node = new Element_List<T>();
			Node->data = data;
			head = Node;
			tail = Node;
		}
		else {
			Element_List<T>* Node = new Element_List<T>();
			Node->data = data;
			tail->next = Node;
			Node->prev = tail;
			tail = Node;
		}
	}

	void pushfront(T data) {
		if (isEmpty()) {
			Element_List<T>* Node = new Element_List<T>();
			Node->data = data;
			head = Node;
			tail = Node;
		}
		else {
			Element_List<T>* Node = new Element_List<T>();
			Node->data = data;
			head->prev = Node;
			Node->next = head;
			head = Node;
		}
	}

	void popback() {
		if (isEmpty())
			throw logic_error("List is empty.");
		else {
			if (tail->prev != NULL) {
				tail = tail->prev;
				delete tail->next;
				tail->next = NULL;
			}
			else {
				delete tail;
				head = NULL;
				tail = NULL;
			}
		}
	}

	void popfront() {
		if (isEmpty())
			throw logic_error("List is empty.");
		else {
			if (head->next != NULL) {
				head = head->next;
				delete head->prev;
				head->prev = NULL;
			}
			else {
				delete head;
				head = NULL;
				tail = NULL;
			}
		}
	}

	void clear() {
		Element_List<T>* Node = head;
		while (Node != NULL) {
			Node = Node->next;
			delete head;
			head = Node;
		}
	}
};