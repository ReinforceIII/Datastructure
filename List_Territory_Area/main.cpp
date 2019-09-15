#include <iostream>
#include <string>
#include "figure.h"
#include <sstream>
#include <fstream>

using namespace std;
string *getInputs(intptr_t sizeLimit);
myList getFigure(intptr_t sizeLimit);
void setList(string *tArray, myList fList,int t_index);
double finalArea(myList list);

int total_i = 0;
string ifile = "sample.inp";
string ofile = "sample.out";

void main() {

	//입력 첫줄을 string 배열에 입력시킴.
	string *tokenArray = getInputs(100);

	//각각의 도형객체를 읽어들여 linkedList에 저장한다.
	myList figureList = getFigure(15);

	//첫줄을 처리하면서 도형이 지면인지 물인지 세팅함.
	setList(tokenArray,figureList,total_i);

	//전체 넓이를 구한다
	double result = finalArea(figureList);

	ofstream outFile(ofile);
	outFile << result << endl;
	cout << "결과값 "<< result << "이 " << ofile << "에 기록되었습니다." << endl;
}

//파일 입력의 첫줄을 배열에 집어넣는다.
string *getInputs(intptr_t sizeLimit) {

	ifstream inFile(ifile);

	string *tokenArray = new string[sizeLimit];
	string line;
	getline(inFile, line);
	istringstream iss(line);
	string token;

	while (getline(iss, token, ' ')) {
		tokenArray[total_i++] = token;
		if (total_i >= sizeLimit) break;
	}

	return tokenArray;
}

//입력의 나머지(도형 객체들의 정보)를 LinkedList에 가공하여 집어넣은뒤 이를 반환한다.
myList getFigure(intptr_t sizeLimit) {

	ifstream inFile(ifile);

	//입력의 첫줄을 버림 (이미 처리되었음)
	string removeline;
	getline(inFile, removeline);

	myList result;
	int figure_i = 0;
	char _name;
	char _type;
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int r;

	//이후에 수정되어야 할 값을 우선 initialize 시켜놓음
	bool isWater = false;

	while (!inFile.eof()) {
		//객체 하나씩 읽음 (Format은 sample을 통해서 파악함)
		string *tokenArray = new string[sizeLimit];
		string line;
		getline(inFile, line);
		istringstream iss(line);
		string token;
		
		//도형 이름
		getline(iss, token, ' ');
		_name = token[0];
		
		// ( 를 제거
		getline(iss, token, ' ');
		// 도형 type
		getline(iss, token, ' ');
		_type = token[0];

		//남은 좌표 정보들을 string배열에 저장(괄호를 저장안함)
		while (getline(iss, token, ' ')) {
			if (token[0] == '(' || token[0] == ')') continue;
			tokenArray[figure_i++] = token;
		}
		
		//좌표를 이용해 각 객체 생성 -> 넓이 계산 -> linkedlist에 저장
		if (_type == 'R') { 
			x1 = stoi(tokenArray[0]);
			y1 = stoi(tokenArray[1]);
			x2 = stoi(tokenArray[2]);
			y2 = stoi(tokenArray[3]);

			figure *rect = new rectangle(x1, y1, x2, y2);
			double area = rect->Area();
			//list에 insert.
			result.add(_name, isWater, area);
		}
		else if (_type == 'T') { 
			x1 = stoi(tokenArray[0]);
			y1 = stoi(tokenArray[1]);
			x2 = stoi(tokenArray[2]);
			y2 = stoi(tokenArray[3]);
			x3 = stoi(tokenArray[4]);
			y3 = stoi(tokenArray[5]);

			figure *tria = new triangle(x1, y1, x2, y2, x3, y3);
			double area = tria->Area();
			//list에 insert.
			result.add(_name, isWater, area);
		}
		else if(_type == 'C') { 
			x1 = stoi(tokenArray[0]);
			y1 = stoi(tokenArray[1]);
			r = stoi(tokenArray[2]);

			figure *circ = new circle(x1, y1, r);
			double area = circ->Area();
			//list에 insert.
			result.add(_name, isWater, area);
		}

		figure_i = 0;
	}
	return result;
}

//첫줄을 보고 객체가 지면인지 물인지 판단해서 update 시킴
void setList(string *tArray, myList fList, int t_index) {
	int figure_layer = 0;
	bool isWater = false;

	for (int i = 0; i < t_index; i++) {
		string token = tArray[i];

		//각 토큰별로 수행.
		if (token[0] == '(' || token[0] == ')') continue;
		// 도형이름에 -가 붙어있으면 물 영역이므로 isWater = true로 만듬
		else if (token[0] == '-') {
			isWater = true;
			fList.set(token[1], isWater);
		}
		else if (token[0] >= 'A' && token[0] <= 'Z') {
			isWater = false;
			fList.set(token[0], isWater);
		}

	}

}

//최종 넓이를 구함
double finalArea(myList list) {
	int listSize = list.getCount();
	node *now = list.getHead();
	double result = 0;
	for (int i = 0; i < listSize + 1; i++) {
		double now_result = now->area;
		if (now->isWater == false) result += now_result;
		else if (now->isWater == true) result -= now_result;

		now = now->next;
	}

	return result;
}