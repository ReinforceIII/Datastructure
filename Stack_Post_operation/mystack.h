#ifndef MYSTACK_H
#define MYSTACK_H

using namespace std;

//make stack for string value
class mystack {
public:
	mystack(int initialCapacity=20);
	~mystack();

	bool empty();
	string top();
	void push(string item);
	void pop();

private :
	string *stack;
	int _top;
	int capacity;	
};

#endif