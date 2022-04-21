#pragma once
#pragma once
#include <iostream>

using namespace std;

template<class T>
class Stack {
private:
	class Element_Stack {
	public:
		T data;
		Element_Stack* next;
	};

public:
	Element_Stack* top;
	size_t size;
	void push(T x) {
		if (isEmpty()) {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = NULL;
			top = Node;
		}
		else {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = top;
			top = Node;
		}
		size++;
	}

	T pop() {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			Element_Stack* temporary = top;
			if (top->next == NULL)
				top = NULL;
			else
				top = temporary->next;
			T popped = temporary->data;
			delete temporary;
			size--;
			return popped;
		}
	}

	bool isEmpty() {
		if (top == NULL)
			return true;
		else
			return false;
	}

	size_t getsize() { return size; }

	Stack() {
		top = NULL;
		size = 0;
	}

	~Stack() = default;
};