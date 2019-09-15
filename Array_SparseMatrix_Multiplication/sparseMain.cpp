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
	int K1 = 0, K2 = 0;		//각 SparseMatrix의 non-zero element 개수
	int i_row, i_col, i_val;
	//get MatrixSize
	fscanf(fp, "%d", &matrixSize);
	
	//get first matrix
	fscanf(fp, "%d", &K1);
	SparseMatrix a(matrixSize, K1);

	//set first matrix value
	//input의 index가 1부터 시작하기때문에 row,column을 1씩 감소시켜 값을 넣음.
	for (int i = 0; i < K1; i++) {
		fscanf(fp, "%d, %d, %d", &i_row, &i_col, &i_val);
		a.update(i, i_row - 1, i_col - 1, i_val);
	}
	
	//get second matrix
	fscanf(fp, "%d", &K2);
	SparseMatrix b(matrixSize, K2);

	//get second matrix value
	//input의 index가 1부터 시작하기때문에 row,column을 1씩 감소시켜 값을 넣음.
	for (int i = 0; i < K2; i++) {
		fscanf(fp, "%d, %d, %d", &i_row, &i_col, &i_val);
		b.update(i, i_row - 1, i_col - 1, i_val);
	}

	//Multiply
	SparseMatrix c(a.Multiply(b));

	//print output
	//함수 내에서 다시 row & column 값을 1씩 증가시켜 값을 출력한다.
	c.PrintMatrix();
	
	fclose(fp);
}
