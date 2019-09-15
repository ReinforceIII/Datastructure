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
	SparseMatrix(int size, int non_zero);				//������
	SparseMatrix(const SparseMatrix &T);
	~SparseMatrix();									//�Ҹ���

	void update(int index, int r, int c, int v);		//�Է¹��� ������ �������.

	SparseMatrix Transpose();							//��ġ ���
	void StoreSum(int sum, int r, int c);
	void ChangeSize(int newSize);

	SparseMatrix Multiply(SparseMatrix ano_sm);			//����

	void PrintMatrix();									//��� ���

private :
	int n, nElements, capacity;					//�������� N x N ����� �����̶� �����߱� ������ row,col�� �ϳ��� ����.
	MatrixTerm *smArray;						//�����Ҷ� size�� ���Ϲ������� �̿��ؼ� �Ҵ�.
};
#endif