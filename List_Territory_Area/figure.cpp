#include <iostream>
#include <string>
#include <cmath>
#include "figure.h"

//rectangle ������ : �� ��ǥ�κ��� ���� ���� ���̸� ���Ѵ�.
rectangle::rectangle(int x1, int y1, int x2, int y2) {
	int w = abs(x2 - x1);
	int h = abs(y2 - y1);

	width = w;
	height = h;
}

//rectangle Area : ���� ���θ� ���ؼ� ���̸� ���Ѵ�
double rectangle::Area() {
	double result = width*height;
	return result;
}

//triangle ������ : �� ��ǥ�κ��� ������ ���̸� ���Ѵ�.
triangle::triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	double s1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	double s2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
	double s3 = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));

	side1 = s1;
	side2 = s2;
	side3 = s3;
}

//triangle Area : ����� ������ ����Ѵ�.
double triangle::Area() {
	double s = (side1 + side2 + side3) / 2;
	double result = sqrt(s * (s - side1) * (s - side2) * (s - side3));
	return result;
}

//circle ������ �������� ����ִ´�.
circle::circle(int x1, int y1, int r) {
	radius = r;
}

//circle Area : ������*������*PI
double circle::Area() {
	double result = radius * radius * 3.14;
	return result;
}

//LinkedList ������
myList::myList() {
	head->next = NULL;
	count = 0;
}

myList::~myList() {
	
	node *tmpNode = head;

	while (tmpNode)	{
		node *next = tmpNode->next;
		delete tmpNode;
		tmpNode = next;
	}
	count = 0;
	head = NULL;

}

//LinkedList�� node ����.
void myList::add(char name, bool isWater, double area) {
	node* newNode = new node;
	//data �ֱ�	
	newNode->name = name;
	newNode->isWater = isWater;
	newNode->area = area;
	newNode->next = NULL;

	if (head->next == NULL)	head->next = newNode;
	else {
		node* temp = head;
		while (temp->next != NULL) temp = temp->next;
		temp->next = newNode;
	}
	count++;
}

node *myList::getHead() { return head; }
int myList::getCount() { return count; }

//LinkedList Ž��.(�̸����� Ž��.)
node *myList::search(node *head, char _name) {
	node *temp = head;
	while (temp != NULL) {
		char temp_name = temp->name;
		if (temp_name == _name) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void myList::set(char _name, bool isWater) {
	node *temp = getHead()->next;
	node *target = search(temp, _name);
	target->isWater = isWater;
}