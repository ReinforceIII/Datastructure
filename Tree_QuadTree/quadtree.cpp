#include <iostream>
#include <sstream>
#include "quadtree.h"
#include <cmath>

using namespace std;
double getmax(double d1, double d2);
double getmin(double d1, double d2);

//quadtree ������ root�� ����/�ʱ�ȭ ��Ŵ.
quadtree::quadtree() {
	root = new node;

	root->data.x = 0;
	root->data.y = 0;
	root->data.height = 1;
	root->data.width = 1;
	root->data.type = 'a';
}

quadtree::~quadtree() {
	
}

node *quadtree::getRoot() {
	return root;
}

//split point�� �ش� node�� ���ԵǴ����� check�ϴ� �Լ�
bool quadtree::contain(node *currNode, double break_x, double break_y) {
	return (break_x > currNode->data.x && break_y > currNode->data.y &&
		break_x < currNode->data.x + currNode->data.width &&
		break_y < currNode->data.y + currNode->data.height);			
}

//split point�� ���� �������� node�� ��ȯ��.
node *quadtree::findBreakNode(node *_root, double break_x, double break_y) {
	if (_root == NULL) return NULL;
	node *currNode = _root;
	node *finalNode = NULL;

	//type = 'N' (�̹� split�� ���� node�̹Ƿ� �� node�� ������ �ȵǵ��� �ϱ� ����.
	if (currNode->data.type != 'N' && contain(currNode, break_x, break_y)) return currNode;
		else {	//Recursive
			finalNode = findBreakNode(currNode->topLeft, break_x, break_y);
			if (finalNode != NULL) return finalNode;
			finalNode = findBreakNode(currNode->topRight, break_x, break_y);
			if (finalNode != NULL) return finalNode;
			finalNode = findBreakNode(currNode->botRight, break_x, break_y);
			if (finalNode != NULL) return finalNode;
			finalNode = findBreakNode(currNode->botLeft, break_x, break_y);
			if (finalNode != NULL) return finalNode;
		}	

	return finalNode;
}

//node Insert. split�Ǿ� ���� ����� node 4���� �ѹ��� insert ��Ŵ.
bool quadtree::Insert(node *selected, double break_x, double break_y, char TL, char TR, char BR, char BL) {
	//���� ���� �������� ���ҵǴ� ���� ���θ� ���� ����.
	double width_left = break_x - selected->data.x;
	double width_right = selected->data.width - width_left;
	double height_top = break_y - selected->data.y;
	double height_bot = selected->data.height - height_top;

	//1. ��� ���� x = x // y = y // w = width_left // h = height_top
	struct nodeData TL_data = { selected->data.x, selected->data.y, width_left, height_top, TL };
	node *TLnode = new node(TL_data);
	selected->topLeft = TLnode;

	//2. ��� ���� x = x + width_left // y = y // w = width_right // h = height_top
	struct nodeData TR_data = { selected->data.x + width_left, selected->data.y, width_right, height_top, TR };
	node *TRnode = new node(TR_data);
	selected->topRight = TRnode;

	//3. �ϴ� ���� x = x + width_left // y = y + height_top // w = width_right // h = height_bot
	struct nodeData BR_data = { selected->data.x + width_left, selected->data.y + height_top, width_right, height_bot, BR };
	node *BRnode = new node(BR_data);
	selected->botRight = BRnode;

	//1. �ϴ� ���� x = x // y = y + height_top // w = width_left // h = height_bot
	struct nodeData BL_data = { selected->data.x, selected->data.y + height_top, width_left, height_bot, BL };
	node *BLnode = new node(BL_data);
	selected->botLeft = BLnode;

	//�ɰ��� �簢���� ��꿡�� �����ϱ����� Ÿ���� �ٲ����.
	selected->data.type = 'N';
	return true;
}

//�� �簢���� overlap �Ǵ��� ���θ� ��ȯ��.
bool quadtree::overlap(struct nodeData data1, struct nodeData data2) {
	if (data1.x > data2.x + data2.width) return false;
	if (data1.x + data1.width < data2.x) return false;
	if (data1.y > data2.y + data2.height) return false;
	if (data1.y + data1.height < data2.y) return false;

	return true;
}

//��ü node�� ��ȸ�ϸ鼭 overlap�Ǵ� �κ��� ����ؼ� �ջ��Ѵ�. (��ȸ ���� TL -> TR -> parent -> BR -> BL)
double quadtree::get_Overlapped_Area(node *currNode, struct nodeData prob_rect) {
	static double result = 0;
	if (currNode) {
		get_Overlapped_Area(currNode->topLeft,prob_rect);
		get_Overlapped_Area(currNode->topRight,prob_rect);

		if (currNode->data.type == prob_rect.type) {
			if (overlap(currNode->data, prob_rect)) {
				double temp_x = getmax(currNode->data.x, prob_rect.x);
				double temp_y = getmax(currNode->data.y, prob_rect.y);
				double temp_w = getmin(currNode->data.x + currNode->data.width, prob_rect.x + prob_rect.width) - temp_x;
				double temp_h = getmin(currNode->data.y + currNode->data.height, prob_rect.y + prob_rect.height) - temp_y;

				double temp_area = temp_w * temp_h;
				
				result += temp_area;
			}	
		}
		get_Overlapped_Area(currNode->botRight, prob_rect);
		get_Overlapped_Area(currNode->botLeft, prob_rect);
	}
	return result;
}

//���� ū���� ��ȯ
double getmax(double d1, double d2) {
	if (d1 <= d2) return d2;
	else return d1;
}

//���� ���� ���� ��ȯ
double getmin(double d1, double d2) {
	if (d1 >= d2) return d2;
	else return d1;
}