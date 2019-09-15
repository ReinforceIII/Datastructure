//////////////////////////////////////////////////////////////////
//																//
// Data Structure Assignment 1: Sparse Matrix Multiplication	//
//																//
//////////////////////////////////////////////////////////////////

#include "sparsematrix.h"
void main() {

	//ready to data parsing
	FILE *fp;
	fp = fopen("1.inp", "r");
	int matrixSize = 0;		//Matrix Size
	int K1 = 0, K2 = 0;		//�� SparseMatrix�� non-zero element ����
	int i_row, i_col, i_val;
	//get MatrixSize
	fscanf(fp, "%d", &matrixSize);
	
	//get first matrix
	fscanf(fp, "%d", &K1);
	SparseMatrix a(matrixSize, K1);

	//set first matrix value
	//input�� index�� 1���� �����ϱ⶧���� row,column�� 1�� ���ҽ��� ���� ����.
	for (int i = 0; i < K1; i++) {
		fscanf(fp, "%d, %d, %d", &i_row, &i_col, &i_val);
		a.update(i, i_row - 1, i_col - 1, i_val);
	}
	
	//get second matrix
	fscanf(fp, "%d", &K2);
	SparseMatrix b(matrixSize, K2);

	//get second matrix value
	//input�� index�� 1���� �����ϱ⶧���� row,column�� 1�� ���ҽ��� ���� ����.
	for (int i = 0; i < K2; i++) {
		fscanf(fp, "%d, %d, %d", &i_row, &i_col, &i_val);
		b.update(i, i_row - 1, i_col - 1, i_val);
	}

	//Multiply
	SparseMatrix c(a.Multiply(b));

	//print output
	//�Լ� ������ �ٽ� row & column ���� 1�� �������� ���� ����Ѵ�.
	c.PrintMatrix();
	
	fclose(fp);
}
