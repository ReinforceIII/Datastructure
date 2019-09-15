#include <iostream>
#include <string>
#include "mystack.h"
#include <sstream>

using namespace std;

string *getInputs(intptr_t sizeLimit);
bool getPriority(string op1, string op2);
int getWeight(string op);
bool isOperator(string C);

string calculation(string operation, int op1, int op2);

//length of expression
int total_i = 0;

void main() {

	cout << "Expression \n";
	//save token into Array using Function
	string *inputs = getInputs(100);
	///////////////////////////1. Infix -> Postfix conversion

	mystack S;
	//Postfix Array
	//total_i was changed by getInputs.
	string *result = new string[total_i];

	//index for result Array
	int result_i = 0;

	for (int i = 0; i < total_i; ++i) {

		string token = inputs[i];
		// check if token is operator
		if (isOperator(token)) {
			while (!S.empty() && S.top() != "(" && getPriority(S.top(), token)) {
				result[result_i] = S.top();
				result_i++;
				S.pop();
			}
			S.push(token);
		}
		// check if token is '(' or ')'
		else if (token == "(") {
			S.push(token);
		}
		else if (token == ")") {
			while (!S.empty() && S.top() != "(") {
				result[result_i] = S.top();
				result_i++;
				S.pop();
			}
			//remove '(' in stack
			S.pop();
		}
		//if token is not operator, '(' or ')' then token is operand
		else {
			result[result_i] = token;
			result_i++;
		}
	} //for (int i = 0; i < total_i; ++i)
	
	//append all in the rest of stack
	while (!S.empty()) {
		result[result_i] = S.top();
		result_i++;
		S.pop();
	} //end of conversion

	//(1) output
	cout << endl << "Postfix = ";
	for (int i = 0; i < result_i; ++i) {
		cout << result[i] << " ";
	}
	cout << endl;
	delete[] inputs;

	///////////////////////////2. Calculation

	mystack S2;

	//We have postfix array -> result
	for (int i = 0; i < result_i; ++i) {
		if (isOperator(result[i])) { // check if token is operator
			//calculation
			int op2 = stoi(S2.top()); S2.pop();
			int op1 = stoi(S2.top()); S2.pop();
			string c_result = calculation(result[i], op1, op2);

			S2.push(c_result);
		}
		else S2.push(result[i]);
	}
	int final_result = stoi(S2.top());
	//(2) output
	cout << "The answer = " << final_result << endl;
}

string *getInputs(intptr_t sizeLimit)
{
	string *tokenArray = new string[sizeLimit];
	string line;
	getline(cin, line);
	istringstream iss(line);
	string token;

	while (getline(iss, token, ' ')) {
		if (token == "=") break;

		tokenArray[total_i] = token;
		total_i++;

		if (total_i >= sizeLimit) break;
	}
	return tokenArray;
}


bool isOperator(string C) {
	if (C == "+" || C == "-" || C == "*" || C == "/") return true;

	return false;
}

int getWeight(string op) {
	int weight = -1;

	if (op == "+" || op == "-") weight = 1;
	else if (op == "*" || op == "/") weight = 2;
	
	return weight;
}

bool getPriority(string op1, string op2)
{
	int op1Weight = getWeight(op1);
	int op2Weight = getWeight(op2);

	if (op1Weight == op2Weight)	return true;

	return op1Weight > op2Weight ? true : false;
}

string calculation(string operation, int op1, int op2) {
	
	int result = 0;
	if (operation == "+") result = op1 + op2;
	else if (operation == "-") result = op1 - op2;
	else if (operation == "*") result = op1 * op2;
	else if (operation == "/") {
		if (op2 == 0) throw "cannot calculate";
		result = op1 / op2;
	}
	//convert integer to string (to save)
	stringstream ss;
	ss << result;
	string str_result = ss.str();

	return str_result;
}