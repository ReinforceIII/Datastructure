#include "sparsematrix.h"

SparseMatrix::SparseMatrix(int size, int non_zero) {
	n = size;
	nElements = non_zero;
	capacity = nElements;
	smArray = new MatrixTerm[capacity];

}

SparseMatrix::SparseMatrix(const SparseMatrix &T) {
	n = T.n;
	nElements = T.nElements;
	capacity = T.nElements;
	smArray = new MatrixTerm[capacity];
	for (int i = 0; i < nElements; i++) {
		this->update(i, T.smArray[i].row, T.smArray[i].col, T.smArray[i].value);
	}
}

SparseMatrix::~SparseMatrix() { 
	if (smArray != NULL) delete[] smArray;
	smArray = NULL;
}

void SparseMatrix::update(int index, int r, int c, int v) {
	smArray[index].row = r;
	smArray[index].col = c;
	smArray[index].value = v;
}

//Transposing :: 강의 ppt의 Another Improved Algorithm으로 구현
SparseMatrix SparseMatrix::Transpose() {
	SparseMatrix temp(n, nElements);
	if (nElements > 0) {
		int *rowSize = new int[n];		
		int *rowStart = new int[n];		 
		for (int i = 0; i < n; i++) rowSize[i] = 0;

		//nElements중에서 각 col 개수를 rowSize에 저장함.
		for (int i = 0; i < nElements; i++) rowSize[smArray[i].col]++;
		
		//col이 시작하는 matrix index를 rowStart에 저장.
		rowStart[0] = 0;
		for (int i = 1; i < n; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

		//변환 시작.
		for (int i = 0; i < nElements; i++) {
			int j = rowStart[smArray[i].col];
			temp.smArray[j].row = smArray[j].col;
			temp.smArray[j].col = smArray[j].row;
			temp.smArray[j].value = smArray[j].value;
			rowStart[smArray[i].col]++;
		} //for (int i = 0; i < nElements; i++)

		delete rowSize;
		delete rowStart;
	} //if (nElements > 0)

	return temp;
}

void SparseMatrix::StoreSum(int sum, int r, int c) {
	if (sum != 0) {
		if (nElements == capacity) {
			if (capacity == 0) ChangeSize(capacity + 1);
			else ChangeSize(capacity * 2);
		}
		smArray[nElements].row = r;
		smArray[nElements].col = c;
		smArray[nElements++].value = sum;
	}
}

void SparseMatrix::ChangeSize(int newSize) {
	if (newSize < nElements) return;
	MatrixTerm *temp = new MatrixTerm[newSize];
	copy(smArray, smArray + nElements, temp);
	delete[] smArray;
	smArray = temp;
	capacity = newSize;
}

//Multiply :: 곱셈.
SparseMatrix SparseMatrix::Multiply(SparseMatrix ano_sm) {
	SparseMatrix ano_tr = ano_sm.Transpose();
	SparseMatrix result(n, 0);
	int currRowIndex = 0,
		currRowBegin = 0,
		currRowThis = smArray[0].row;
	
	//경계 조건 설정
	if (nElements == capacity) ChangeSize(nElements + 1);
	ano_tr.ChangeSize(nElements + 1);
	smArray[nElements].row = n;
	ano_tr.smArray[ano_tr.nElements].row = n;
	ano_tr.smArray[ano_tr.nElements].col = -1;
	int sum = 0;
	
	while (currRowIndex < nElements) {
		int currColAno = ano_tr.smArray[0].row;
		int currColIndex = 0;
		while (currColIndex <= ano_sm.nElements) {

			if (smArray[currRowIndex].row != currRowThis) {
				//currRowThis 행의 끝인 경우
				result.StoreSum(sum, currRowThis, currColAno);
				sum = 0;
				currRowIndex = currRowBegin;

				while (ano_tr.smArray[currColIndex].row == currColAno) currColIndex++;
				currColAno = ano_tr.smArray[currColIndex].row;
			}
			else if (ano_tr.smArray[currColIndex].row != currColAno) {
				//another matrix의 열 CurrcolAno의 끝
				result.StoreSum(sum, currRowThis, currColAno);
				sum = 0;
				currRowIndex = currRowBegin;
				currColAno = ano_tr.smArray[currColIndex].row;
			}
			else {
				if (smArray[currRowIndex].col < ano_tr.smArray[currColIndex].col)
					currRowIndex++;
				else if (smArray[currRowIndex].col == ano_tr.smArray[currColIndex].col) {
					sum += smArray[currRowIndex].value * ano_tr.smArray[currColIndex].value;
					currRowIndex++;
					currColIndex++;
				}
				else currColIndex++;
			}


		} //while (currColIndex <= ano_sm.nElements)
		while (smArray[currRowIndex].row == currRowThis) currRowIndex++;
		currRowBegin = currRowIndex;
		currRowThis = smArray[currRowIndex].row;

		
	} //while (currRowIndex < nElements)
	
	return result;
}

void SparseMatrix::PrintMatrix() {
	const char *outname = "1.out";
	FILE *fprin;
	fprin = fopen(outname, "w");
	fprintf(fprin, "%d\n", nElements);
	for (int i = 0; i < nElements; i++) {
		fprintf(fprin, "%d, %d, %d\n", smArray[i].row + 1, smArray[i].col + 1, smArray[i].value);
	}
	fclose(fprin);
	cout << "결과값이 " << outname << " 에 저장되었습니다" << endl;
}