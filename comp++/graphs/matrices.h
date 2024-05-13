#ifndef MATRICES_H
#define MATRICES_H

#include <cassert>

class SqMatrix
{
	int* data;
	int m_rows = 0;
public:
	SqMatrix(int n) :m_rows{ n } {
		resize(n);
	}

	int& operator()(int i, int j) { 
		assert((i < m_rows && j < m_rows) && "Exceded matrix dimensions\n");
		return data[i + m_rows * j];
	}

	int rows() { return m_rows; }
	
	SqMatrix& operator=(SqMatrix&& A) {
		return operator=(A);
	}

	SqMatrix& operator=(SqMatrix& A) {
		m_rows = A.rows();
		std::copy_n(A.data, m_rows * m_rows, data);
		return *this;
	}

	~SqMatrix() {
		delete [] data;
		m_rows = 0;
	}

private:
	void resize(int& n) {
		data = new int[n * n];
	}
};


#endif
