#include <iostream>
#include <sstream>
#include <fstream>
#include "quadtree.h"

using namespace std;

const char *ifile = "sample.inp";
const char *ofile = "sample.out";

void main() {
	ifstream inFile(ifile);

	//overlap 되는 사각형의 정보를 구하기위함.
	double q_x1, q_y1;	
	double q_x2, q_y2;
	char q_type;

	string currline;
	
	getline(inFile, currline);		//첫줄
	istringstream iss(currline);
	string token;

	for (int i = 0; i < 4; i++) {
		getline(iss, token, ',');
		switch (i) {
		case 0: q_x1 = stod(token); break;
		case 1: q_y1 = stod(token); break;
		case 2:	q_x2 = stod(token); break;
		case 3:	q_y2 = stod(token); break;
		}
	}
	iss.clear();

	getline(inFile, currline);
	q_type = currline[0];
	nodeData prob = { q_x1, q_y1, q_x2 - q_x1, q_y2 - q_y1, q_type };
	// 여기까지 overlap 사각형의 정보입력.

	quadtree *quadTree = new quadtree;

	getline(inFile, currline);
	int nElement = stoi(currline);

	//quadtree 구성
	for (int i = 0; i < nElement; ++i) {
		int progress=0;
		double break_x, break_y;
		char TL, TR, BR, BL;
		getline(inFile, currline);
		istringstream iss2(currline);

		while (getline(iss2, token, ',')) {
			switch (progress) {
			case 0: break_x = stod(token); break;
			case 1: break_y = 1 - stod(token); break;
			case 2: TL = token[1]; break;
			case 3: TR = token[1]; break;
			case 4: BR = token[1]; break;
			case 5: BL = token[1]; break;
			}
			progress++;
		}
		//split point가 포함되어있는 사각형을 찾음
		node *selected = quadTree->findBreakNode(quadTree->getRoot(), break_x, break_y);

		//찾은 사각형 node에 새로운 4개의 node를 집어넣음
		quadTree->Insert(selected, break_x, break_y, TL, TR, BR, BL);

	} //for (int i = 0; i < nElement; ++i)

	//QuadTree 확립됨.

	//넓이를 구함
	double result = quadTree->get_Overlapped_Area(quadTree->getRoot(),prob);

	ofstream outFile(ofile);
	outFile << result << endl;
	cout << "결과값 " << result << "이 " << ofile << "에 기록되었습니다." << endl;

}