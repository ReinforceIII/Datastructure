#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;
string ifile = "sample.inp";
string ofile = "sample.out";


struct EdgeNode {
	int adjVertex;
	int time;
	EdgeNode *next;
};

struct VertexNode {
	int name;
	int indegree;	//해당 vertex로 들어오는 edge 개수
	EdgeNode *first;
};

struct Snode {
	VertexNode ver;
	Snode *next;
	Snode *pre;
};

class Slist {
private:
	Snode *base;
	Snode *top;

public:
	Slist() {
		base = NULL;
		top = NULL;
	}

	void Init() {
		base = new Snode;
		if (!base) exit(1);
		base->next = NULL;
		base->pre = NULL;
		top = base;
	}

	bool Empty() {
		if (top == base) return true;
		else return false;
	}

	void push(VertexNode *graph, int i) {
		Snode *newNode = new Snode;
		newNode->next = NULL;
		newNode->pre = top;
		newNode->ver = graph[i];
		top->next = newNode;
		top = newNode;
	}

	int pop() {
		Snode *selNode;
		if (Empty()) exit(1);
		int result = top->ver.name;
		selNode = top;
		top = top->pre;
		top->next = NULL;
		delete selNode;
		return result;
	}
};

class AdjList {
	friend class Slist;
private:
	VertexNode *graph;
	int nVertex;
	int nEdge;

public:
	AdjList(int vexnum) {
		graph = new VertexNode[vexnum];
	}

	~AdjList() {
		for (int i = 0; i < nVertex; i++) {
			EdgeNode *temp;
			EdgeNode *curr = graph[i].first;
			while (curr !=NULL) {
				temp = curr->next;
				delete curr;
				curr = temp;
			}
			graph->first = NULL;
		}
		delete[] graph;
	}

	//그래프 생성
	void CreateGraph(int vexnum, int edgenum, int &from, int &to) {

		ifstream inFile(ifile);
		string currline;
		for (int i = 0; i < 2; i++) {
			getline(inFile, currline);
		}
		int begin, end, spentime;
		EdgeNode * currEdge;
		nVertex = vexnum;
		nEdge = edgenum;

		//vertex 개수만큼 각 vertex list 초기화.
		for (int i = 0; i < nVertex; i++) {
			graph[i].name = i;
			graph[i].indegree = 0;
			graph[i].first = NULL;
		}

		for (int e = 0; e < nEdge; e++) {
			getline(inFile, currline);
			istringstream iss(currline);
			string token;

			int progress = 0;
			while (getline(iss, token, ',')) {
				switch (progress) {
				case 0: begin = stoi(token); break;
				case 1: end = stoi(token); break;
				case 2: spentime = stoi(token); break;
				}
				progress++;
			}
			currEdge = new EdgeNode;
			currEdge->adjVertex = end - 1;
			currEdge->time = spentime;
			graph[end - 1].indegree++;
			currEdge->next = graph[begin - 1].first;
			graph[begin - 1].first = currEdge;
		} //for (int e = 0; e < nEdge; e++)

		getline(inFile, currline);
		istringstream iss2(currline);
		string token;
		int progress2 = 0;
		while (getline(iss2, token, ',')) {
			switch (progress2) {
			case 0: from = stoi(token); break;
			case 1: to = stoi(token); break;
			}
			progress2++;
		}

	}

	bool TopologicalOrder(Slist &T, int *&vexEarly, int &totaltime) {
		EdgeNode *currEdge;

		int currV = -1, dest = 0, count = 0;
		T.Init();
		Slist nList;
		nList.Init();
		for (int i = 0; i < nVertex; i++) {
			vexEarly[i] = 0;
			if (graph[i].indegree == 0) nList.push(graph, i);
		}

		while (!nList.Empty()) {
			currV = nList.pop();
			T.push(graph, currV);
			++count;
			for (currEdge = graph[currV].first; currEdge; currEdge = currEdge->next) {
				dest = currEdge->adjVertex;
				if (--graph[dest].indegree == 0) nList.push(graph, dest);
				if (vexEarly[currV] + currEdge->time > vexEarly[dest]) vexEarly[dest] = vexEarly[currV] + currEdge->time;
				totaltime = vexEarly[dest];
			}
		} //while (!nList.Empty())

		if (count < nVertex) return false;
		else return true;
	}

	bool CriticalPath(Slist &T,int from, int to) {
		int currV = -1;
		int dest = -1;
		int spentime = 0;
		int ee, el, totaltime = 0;
		bool match;
		EdgeNode *currEdge;
		int *verEarly = new int[nVertex];
		int *verLate = new int[nVertex];
		if (!TopologicalOrder(T, verEarly, totaltime)) return false;

		for (int i = 0; i < nVertex; i++) verLate[i] = totaltime;

		while (!T.Empty()) {
			for (currV = T.pop(), currEdge = graph[currV].first; currEdge; currEdge = currEdge->next) {
				dest = currEdge->adjVertex;
				spentime = currEdge->time;
				if (verLate[dest] - spentime < verLate[currV]) verLate[currV] = verLate[dest] - spentime;
			}
		}

		int *rs = new int[nVertex];
		int rs_i = 0;
		int f_i;
		for (f_i = 0; f_i < nVertex; f_i++) {
			for (currEdge = graph[f_i].first; currEdge; currEdge = currEdge->next) {
				dest = currEdge->adjVertex;
				spentime = currEdge->time;
				ee = verEarly[f_i];
				el = verLate[dest] - spentime;
				match = (ee == el) ? true : false;
				if (match == true) {
					rs[rs_i] = f_i + 1;
					rs_i++;
				}
			}
		} //for (int i = 0; i < nVertex; i++)
		rs[rs_i] = to;
		rs_i++;

		ofstream outFile(ofile);
		
		outFile << totaltime << ": (";
		for (int kk = 0; kk < rs_i; kk++) {
			if (kk != rs_i - 1) outFile << rs[kk] << ", ";
			else outFile << rs[kk];
		}
		outFile << ")" << endl;
		return true;
	}

};

void main() {
	bool status;
	int numVertex, numEdge, totaltime = 0;
	int from=0, to=0;
	Slist T;
	
	ifstream inFile(ifile);
	string line;
	getline(inFile, line);
	numVertex = stoi(line);

	getline(inFile, line);
	numEdge = stoi(line);
	
	AdjList *graphList = new AdjList(numVertex);
	graphList->CreateGraph(numVertex, numEdge, from, to);
	status = graphList->CriticalPath(T, from, to);

	if (!status) cout << "no path" << endl;


}