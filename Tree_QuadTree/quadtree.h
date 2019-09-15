#pragma once

using namespace std;

//quadtree node에 포함되어야할 data를 구조체로 설정
struct nodeData {
	double x, y;			//왼쪽위 좌표
	double width, height;	//가로세로 길이
	char type;			//a or b
};

class node {
	friend class quadtree;

private:
	node *topLeft;
	node *topRight;
	node *botRight;
	node *botLeft;
	nodeData data;

public:
	//root node 생성자
	node() {
		topLeft = NULL;
		topRight = NULL;
		botRight = NULL;
		botLeft = NULL;
		data = {0,0,0,0,'a'};
	}
	//split되어서 생기는 node 생성자
	node(struct nodeData _data) {
		topLeft = NULL;
		topRight = NULL;
		botRight = NULL;
		botLeft = NULL;
		data = _data;
	}
};

class quadtree {
public :
	quadtree();
	~quadtree();
	node *getRoot();
	bool contain(node *_currNode, double break_x, double break_y);
	node *findBreakNode(node *_root, double break_x, double break_y);
	bool Insert(node *selected, double break_x, double break_y, char TL, char TR, char BR, char BL);

	bool quadtree::overlap(struct nodeData data1, struct nodeData data2);
	double get_Overlapped_Area(node *currNode, struct nodeData prob_rect);

private:
	node *root;
};