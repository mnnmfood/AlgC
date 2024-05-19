#ifndef MATRICES_H
#define MATRICES_H

#include <cassert>

template<typename T>
class SqMatrix
{
	T* data;
	int m_rows = 0;
public:
	SqMatrix(int n) :m_rows{ n } {
		resize(n);
	}

	SqMatrix(const SqMatrix<T>& A) {
		m_rows = A.rows();
		std::copy_n(A.data, m_rows * m_rows, data);
	}

	T& operator()(int i, int j) { 
		assert((i < m_rows && j < m_rows) && "Exceded matrix dimensions\n");
		return data[i + m_rows * j];
	}

	const T& operator()(int i, int j) const { 
		assert((i < m_rows && j < m_rows) && "Exceded matrix dimensions\n");
		return data[i + m_rows * j];
	}

	int rows() const { return m_rows; }
	
	void setConstant(int c) {
		memset(data, c, m_rows * m_rows * sizeof(T));
	}

	SqMatrix<T>& operator=(const SqMatrix&& A) {
		return operator=(A);
	}

	SqMatrix<T>& operator=(const SqMatrix& A) {
		m_rows = A.rows();
		std::copy_n(A.data, m_rows * m_rows, data);
		return *this;
	}

	~SqMatrix() {
		delete [] data;
		m_rows = 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const SqMatrix<T>& A);

private:
	void resize(int& n) {
		data = new T[n * n];
	}
};

std::ostream& operator<<(std::ostream& out, const SqMatrix<int>& A) {
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


#endif
