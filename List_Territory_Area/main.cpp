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

	//�Է� ù���� string �迭�� �Է½�Ŵ.
	string *tokenArray = getInputs(100);

	//������ ������ü�� �о�鿩 linkedList�� �����Ѵ�.
	myList figureList = getFigure(15);

	//ù���� ó���ϸ鼭 ������ �������� ������ ������.
	setList(tokenArray,figureList,total_i);

	//��ü ���̸� ���Ѵ�
	double result = finalArea(figureList);

	ofstream outFile(ofile);
	outFile << result << endl;
	cout << "����� "<< result << "�� " << ofile << "�� ��ϵǾ����ϴ�." << endl;
}

//���� �Է��� ù���� �迭�� ����ִ´�.
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

//�Է��� ������(���� ��ü���� ����)�� LinkedList�� �����Ͽ� ��������� �̸� ��ȯ�Ѵ�.
myList getFigure(intptr_t sizeLimit) {

	ifstream inFile(ifile);

	//�Է��� ù���� ���� (�̹� ó���Ǿ���)
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

	//���Ŀ� �����Ǿ�� �� ���� �켱 initialize ���ѳ���
	bool isWater = false;

	while (!inFile.eof()) {
		//��ü �ϳ��� ���� (Format�� sample�� ���ؼ� �ľ���)
		string *tokenArray = new string[sizeLimit];
		string line;
		getline(inFile, line);
		istringstream iss(line);
		string token;
		
		//���� �̸�
		getline(iss, token, ' ');
		_name = token[0];
		
		// ( �� ����
		getline(iss, token, ' ');
		// ���� type
		getline(iss, token, ' ');
		_type = token[0];

		//���� ��ǥ �������� string�迭�� ����(��ȣ�� �������)
		while (getline(iss, token, ' ')) {
			if (token[0] == '(' || token[0] == ')') continue;
			tokenArray[figure_i++] = token;
		}
		
		//��ǥ�� �̿��� �� ��ü ���� -> ���� ��� -> linkedlist�� ����
		if (_type == 'R') { 
			x1 = stoi(tokenArray[0]);
			y1 = stoi(tokenArray[1]);
			x2 = stoi(tokenArray[2]);
			y2 = stoi(tokenArray[3]);

			figure *rect = new rectangle(x1, y1, x2, y2);
			double area = rect->Area();
			//list�� insert.
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
			//list�� insert.
			result.add(_name, isWater, area);
		}
		else if(_type == 'C') { 
			x1 = stoi(tokenArray[0]);
			y1 = stoi(tokenArray[1]);
			r = stoi(tokenArray[2]);

			figure *circ = new circle(x1, y1, r);
			double area = circ->Area();
			//list�� insert.
			result.add(_name, isWater, area);
		}

		figure_i = 0;
	}
	return result;
}

//ù���� ���� ��ü�� �������� ������ �Ǵ��ؼ� update ��Ŵ
void setList(string *tArray, myList fList, int t_index) {
	int figure_layer = 0;
	bool isWater = false;

	for (int i = 0; i < t_index; i++) {
		string token = tArray[i];

		//�� ��ū���� ����.
		if (token[0] == '(' || token[0] == ')') continue;
		// �����̸��� -�� �پ������� �� �����̹Ƿ� isWater = true�� ����
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

//���� ���̸� ����
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