#pragma once

using namespace std;

//quadtree node�� ���ԵǾ���� data�� ����ü�� ����
struct nodeData {
	double x, y;			//������ ��ǥ
	double width, height;	//���μ��� ����
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
	//root node ������
	node() {
		topLeft = NULL;
		topRight = NULL;
		botRight = NULL;
		botLeft = NULL;
		data = {0,0,0,0,'a'};
	}
	//split�Ǿ ����� node ������
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