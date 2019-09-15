#include <iostream>
#include <string>
#include "mystack.h"
using namespace std;

//constructor. initialcapacity is 20
mystack::mystack(int initialCapacity) : capacity(initialCapacity) {
	if (capacity < 1) throw "stack capacity는 0보다 커야합니다";
	stack = new string[capacity];
	_top = -1;
}

//destructor
mystack::~mystack() {
	if (stack != NULL) delete[] stack;
	stack = NULL;
}

bool mystack::empty() {
	if (_top == -1) return true;
	else return false;
}

string mystack::top() {
	if (empty()) throw "Stack is empty";
	return stack[_top];
}

void mystack::push(string item) {
	//if stack is full -> changeSize
	if (_top == capacity - 1) {
		string *temp = new string[capacity * 2];
		copy(stack, stack + capacity - 1, temp);
		delete[] stack;
		stack = temp;
		capacity *= 2;
	}

	stack[++_top] = item;
}

void mystack::pop() {
	if (empty()) throw "stack is empty. cannot delete";
	stack[_top--] = "";
}
