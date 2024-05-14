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

	SqMatrix(const SqMatrix& A) {
		m_rows = A.rows();
		std::copy_n(A.data, m_rows * m_rows, data);
	}

	int& operator()(int i, int j) { 
		assert((i < m_rows && j < m_rows) && "Exceded matrix dimensions\n");
		return data[i + m_rows * j];
	}

	const int& operator()(int i, int j) const { 
		assert((i < m_rows && j < m_rows) && "Exceded matrix dimensions\n");
		return data[i + m_rows * j];
	}

	int rows() const { return m_rows; }
	
	SqMatrix& operator=(const SqMatrix&& A) {
		return operator=(A);
	}

	SqMatrix& operator=(const SqMatrix& A) {
		m_rows = A.rows();
		std::copy_n(A.data, m_rows * m_rows, data);
		return *this;
	}

	~SqMatrix() {
		delete [] data;
		m_rows = 0;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const SqMatrix& A) {
		int rows = A.rows();
		for (int i{ 0 }; i < rows; i++) {
			for (int j{ 0 }; j < rows; j++) {
				out << A(i, j) << ", ";
			}
			out << "\n";
		}
		out << "\n";
		return out;
	}

private:
	void resize(int& n) {
		data = new int[n * n];
	}
};


#endif
