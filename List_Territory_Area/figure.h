#ifndef FIGURE_H
#define FIGURE_H

//도형 클래스
class figure {
public:
	virtual double Area() = 0;

};

class rectangle : public figure {
private:
	int width;
	int height;

public:
	rectangle(int x1, int y1, int x2, int y2);
	virtual double Area();
};

class triangle : public figure {
private:
	double side1;
	double side2;
	double side3;

public:
	triangle(int x1, int y1, int x2, int y2, int x3, int y3);
	virtual double Area();
};

class circle : public figure {
private:
	int radius;

public:
	circle(int x1, int y1, int r);
	virtual double Area();
};

// List 클래스
class node {
	friend class myList;
public:
	char name;
	bool isWater;
	double area;
	node *next;
};

class myList {
private :
	int count;
	node *head = new node;

public:
	myList();
	~myList();
	node *getHead();
	int getCount();
	void add(char name, bool isWater, double Area);
	node *search(node *head, char _name);
	void set(char name, bool isWater);
};

#endif