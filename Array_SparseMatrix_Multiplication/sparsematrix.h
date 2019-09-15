#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

class MatrixTerm{
	friend class SparseMatrix;
private:
	int row, col;
	int value;
};

class SparseMatrix{
public :
	SparseMatrix(int size, int non_zero);				//생성자
	SparseMatrix(const SparseMatrix &T);
	~SparseMatrix();									//소멸자

	void update(int index, int r, int c, int v);		//입력받은 정보를 집어넣음.

	SparseMatrix Transpose();							//전치 행렬
	void StoreSum(int sum, int r, int c);
	void ChangeSize(int newSize);

	SparseMatrix Multiply(SparseMatrix ano_sm);			//곱셈

	void PrintMatrix();									//결과 출력

private :
	int n, nElements, capacity;					//문제에서 N x N 행렬의 곱셈이라 가정했기 때문에 row,col을 하나로 통합.
	MatrixTerm *smArray;						//생성할때 size를 리턴받은것을 이용해서 할당.
};
#endif