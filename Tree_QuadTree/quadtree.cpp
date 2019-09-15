#include <iostream>
#include <sstream>
#include "quadtree.h"
#include <cmath>

using namespace std;
double getmax(double d1, double d2);
double getmin(double d1, double d2);

//quadtree 생성자 root를 생성/초기화 시킴.
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

//split point가 해당 node에 포함되는지를 check하는 함수
bool quadtree::contain(node *currNode, double break_x, double break_y) {
	return (break_x > currNode->data.x && break_y > currNode->data.y &&
		break_x < currNode->data.x + currNode->data.width &&
		break_y < currNode->data.y + currNode->data.height);			
}

//split point에 의해 나눠지는 node를 반환함.
node *quadtree::findBreakNode(node *_root, double break_x, double break_y) {
	if (_root == NULL) return NULL;
	node *currNode = _root;
	node *finalNode = NULL;

	//type = 'N' (이미 split된 상위 node이므로 이 node는 포함이 안되도록 하기 위함.
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

//node Insert. split되어 새로 생기는 node 4개를 한번에 insert 시킴.
bool quadtree::Insert(node *selected, double break_x, double break_y, char TL, char TR, char BR, char BL) {
	//점에 의해 나눠지면 분할되는 가로 세로를 새로 구함.
	double width_left = break_x - selected->data.x;
	double width_right = selected->data.width - width_left;
	double height_top = break_y - selected->data.y;
	double height_bot = selected->data.height - height_top;

	//1. 상단 좌측 x = x // y = y // w = width_left // h = height_top
	struct nodeData TL_data = { selected->data.x, selected->data.y, width_left, height_top, TL };
	node *TLnode = new node(TL_data);
	selected->topLeft = TLnode;

	//2. 상단 우측 x = x + width_left // y = y // w = width_right // h = height_top
	struct nodeData TR_data = { selected->data.x + width_left, selected->data.y, width_right, height_top, TR };
	node *TRnode = new node(TR_data);
	selected->topRight = TRnode;

	//3. 하단 우측 x = x + width_left // y = y + height_top // w = width_right // h = height_bot
	struct nodeData BR_data = { selected->data.x + width_left, selected->data.y + height_top, width_right, height_bot, BR };
	node *BRnode = new node(BR_data);
	selected->botRight = BRnode;

	//1. 하단 좌측 x = x // y = y + height_top // w = width_left // h = height_bot
	struct nodeData BL_data = { selected->data.x, selected->data.y + height_top, width_left, height_bot, BL };
	node *BLnode = new node(BL_data);
	selected->botLeft = BLnode;

	//쪼개진 사각형은 계산에서 제외하기위해 타입을 바꿔버림.
	selected->data.type = 'N';
	return true;
}

//두 사각형이 overlap 되는지 여부를 반환함.
bool quadtree::overlap(struct nodeData data1, struct nodeData data2) {
	if (data1.x > data2.x + data2.width) return false;
	if (data1.x + data1.width < data2.x) return false;
	if (data1.y > data2.y + data2.height) return false;
	if (data1.y + data1.height < data2.y) return false;

	return true;
}

//전체 node를 순회하면서 overlap되는 부분을 계산해서 합산한다. (순회 순서 TL -> TR -> parent -> BR -> BL)
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

//둘중 큰것을 반환
double getmax(double d1, double d2) {
	if (d1 <= d2) return d2;
	else return d1;
}

//둘중 작은 것을 반환
double getmin(double d1, double d2) {
	if (d1 >= d2) return d2;
	else return d1;
}