#pragma once

#include "MatrixException.h"
#include "Rational.h"

#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include <string>
#include <iomanip>

using namespace std;

template <class T>
class Matrix {
	vector<vector<T>> matrix;

public:

	void swapRows(size_t row1, size_t row2);
	void swapColumns(size_t col1, size_t col2);
	size_t findMaxInColumn(size_t i);
	std::pair<size_t, size_t> findMaxInMatrix(size_t i);

	istream& input(istream& in);
	ostream& output(ostream& out);

	Matrix(size_t dim);
	Matrix(size_t row, size_t column);
	Matrix(Matrix const& m1) = default;
	Matrix(Matrix&& m1) noexcept {
		matrix = m1.matrix;
	}

	Matrix& operator = (Matrix& m1) = default;
	Matrix& operator = (Matrix&& m1) = default;

	inline size_t rows() const {
		return matrix.size();
	}
	inline size_t columns() const {
		return matrix[0].size();
	}
	inline vector<T>& operator[](size_t i) {
		return matrix[i];
	}

	Matrix operator * (Matrix& m);
	Matrix operator + (Matrix& m);

	template<class T>
	friend vector<T> mult_row(vector<T>& row, T num, size_t start);
	template<class T>
	friend vector<T> div_row(vector<T>& row, T num, size_t start);
	template<class T>
	friend vector<T> add_row(vector<T>& row1, vector<T>& row2, size_t start);
	template<class T>
	friend vector<T> sub_row(vector<T>& row1, vector<T>& row2, size_t start);

	template<class T>
	friend Matrix<T> solveSystemSED(Matrix<T> m, Matrix<T> b);
	template<class T>
	friend Matrix<T> solveSystemColumn(Matrix<T> m, Matrix<T> b);
	template<class T>
	friend Matrix<T> solveSystemFullMatr(Matrix<T> m, Matrix<T> b);

	T findDeterminator();
	Matrix findReverse();

	~Matrix() = default;
};

template<class T>
Matrix<T>::Matrix(size_t dim) {
	if (dim == 0)
	{
		throw MatrixException::construct_err;
	}
	matrix = vector<vector<T>>(dim, vector<T>(dim, T::zero));
}
template<class T>
Matrix<T>::Matrix(size_t row, size_t column) {
	if (row == 0 || column == 0)
	{
		throw MatrixException::construct_err;
	}
	matrix = vector<vector<T>>(row, vector<T>(column, T::zero));
}

template<class T>
istream& Matrix<T>::input(istream& in) {
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			in >> matrix[i][j];
		}
	}
	return in;
}
template<class T>
ostream& Matrix<T>::output(ostream& out) {
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			out << std::fixed << std::setprecision(4);
			out << std::setw(10) << matrix[i][j];
		}
		out << endl;
	}
	return out;
}

template<class T>
Matrix<T> Matrix<T>::operator * (Matrix<T>& m)
{
	if (columns() != m.rows())
	{
		throw MatrixException::mult_dims;
	}
	Matrix<T> res(rows(), m.columns());
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < m.columns(); j++)
		{
			res[i][j] = T::zero;
			for (int k = 0; k < columns(); k++)
				res[i][j] += matrix[i][k] * m[k][j];
		}
	}
	return res;
}
template<class T>
Matrix<T> Matrix<T>::operator + (Matrix<T>& m)
{
	if (rows() != m.rows() || columns() != m.columns())
	{
		throw MatrixException::sum_dims;
	}
	Matrix<T> res(rows(), columns());
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			res[i][j] = matrix[i][j] + m[i][j];
		}
	}
	return res;
}

template<class T>
vector<T> mult_row(vector<T>& row, T num, size_t start = 0) {
	vector<T> res = row;
	for (size_t i = start; i < row.size(); i++)
	{
		res[i] *= num;
	}
	return res;
}
template<class T>
vector<T> div_row(vector<T>& row, T num, size_t start = 0) {
	vector<T> res = row;
	for (size_t i = start; i < row.size(); i++)
	{
		res[i] /= num;
	}
	return res;
}
template<class T>
vector<T> add_row(vector<T>& row1, vector<T>& row2, size_t start = 0) {
	vector<T> res = row1;
	for (size_t i = start; i < row1.size(); i++)
	{
		res[i] += row2[i];
	}
	return res;
}
template<class T>
vector<T> sub_row(vector<T>& row1, vector<T>& row2, size_t start = 0) {
	vector<T> res = row1;
	for (size_t i = start; i < row1.size(); i++)
	{
		res[i] -= row2[i];
	}
	return res;
}

template<class T>
void Matrix<T>::swapRows(size_t row1, size_t row2) {
	swap(matrix[row1], matrix[row2]);
}
template<class T>
void Matrix<T>::swapColumns(size_t col1, size_t col2) {
	for (size_t i = 0; i < rows(); i++)
	{
		swap(matrix[i][col1], matrix[i][col2]);
	}
}
template<class T>
size_t Matrix<T>::findMaxInColumn(size_t start) {
	T max(0);
	size_t ind = start;
	for (size_t j = start; j < rows(); j++)
	{
		T maybemax = matrix[j][start].abs();
		if (maybemax > max)
		{
			max = maybemax;
			ind = j;
		}
	}
	return ind;
}
template<class T>
std::pair<size_t, size_t> Matrix<T>::findMaxInMatrix(size_t start) {
	T max(0);
	std::pair<size_t, size_t> ind;
	for (size_t i = start; i < rows(); i++)
	{
		for (size_t j = start; j < columns(); j++)
		{
			T maybemax = matrix[i][j].abs();
			if (maybemax > max)
			{
				max = maybemax;
				ind.first = i;
				ind.second = j;
			}
		}
	}
	return ind;
}

template<class T>
Matrix<T> solveSystemSED(Matrix<T> m, Matrix<T> b)
{
	for (size_t i = 0; i < m.rows(); i++) // прямой ход
	{
		if (m.matrix[i][i] == T::zero)
		{
			throw MatrixException::div_zero;
		}
		b[i] = div_row(b[i], m.matrix[i][i]);
		m[i] = div_row(m[i], m.matrix[i][i], i);
		for (size_t j = i + 1; j < m.rows(); j++)
		{
			b[j] = div_row(b[j], m.matrix[j][i]);
			b[j] = sub_row(b[j], b[i]);
			m[j] = div_row(m[j], m.matrix[j][i], i);
			m[j] = sub_row(m[j], m[i], i);
		}
	}

	Matrix<T> res(b.rows(), b.columns());
	for (int i = m.rows() - 1; i >= 0; i--) // обратный ход
	{
		res[i] = b[i];
		for (int j = m.rows() - 1; j > i; j--)
		{
			vector<T> buf = mult_row(res[j], m.matrix[i][j]);
			res[i] = sub_row(res[i], buf);
		}
	}

	return res;
}
template<class T>
Matrix<T> solveSystemColumn(Matrix<T> m, Matrix<T> b)
{
	for (size_t i = 0; i < m.rows(); i++) // прямой ход
	{
		int swapRow = m.findMaxInColumn(i);
		m.swapRows(i, swapRow);
		b.swapRows(i, swapRow);

		if (m.matrix[i][i] == T::zero)
		{
			throw MatrixException::div_zero;
		}
		b[i] = div_row(b[i], m.matrix[i][i]);
		m[i] = div_row(m[i], m.matrix[i][i], i);
		for (size_t j = i + 1; j < m.rows(); j++)
		{
			b[j] = div_row(b[j], m.matrix[j][i]);
			b[j] = sub_row(b[j], b[i]);
			m[j] = div_row(m[j], m.matrix[j][i], i);
			m[j] = sub_row(m[j], m[i], i);
		}
	}

	Matrix<T> res(b.rows(), b.columns());
	for (int i = m.rows() - 1; i >= 0; i--) // обратный ход
	{
		res[i] = b[i];
		for (int j = m.rows() - 1; j > i; j--)
		{
			vector<T> buf = mult_row(res[j], m.matrix[i][j]);
			res[i] = sub_row(res[i], buf);
		}
	}

	return res;
}
template<class T>
Matrix<T> solveSystemFullMatr(Matrix<T> m, Matrix<T> b) {
	vector<size_t> res_pos(b.rows());
	for (size_t i = 0; i < res_pos.size(); i++)
	{
		res_pos[i] = i;
	}

	for (size_t i = 0; i < m.rows(); i++) // прямой ход
	{
		auto swapInd = m.findMaxInMatrix(i);
		m.swapRows(i, swapInd.first);
		b.swapRows(i, swapInd.first);
		m.swapColumns(i, swapInd.second);
		swap(res_pos[i], res_pos[swapInd.second]);

		if (m.matrix[i][i] == T::zero)
		{
			throw MatrixException::div_zero;
		}
		b[i] = div_row(b[i], m.matrix[i][i]);
		m[i] = div_row(m[i], m.matrix[i][i], i);
		for (size_t j = i + 1; j < m.rows(); j++)
		{
			b[j] = div_row(b[j], m.matrix[j][i]);
			b[j] = sub_row(b[j], b[i]);
			m[j] = div_row(m[j], m.matrix[j][i], i);
			m[j] = sub_row(m[j], m[i], i);
		}
	}

	Matrix<T> res(b.rows(), b.columns());
	for (int i = m.rows() - 1; i >= 0; i--) // обратный ход
	{
		res[i] = b[i];
		for (int j = m.rows() - 1; j > i; j--)
		{
			vector<T> buf = mult_row(res[j], m.matrix[i][j]);
			res[i] = sub_row(res[i], buf);
		}
	}

	for (size_t i = 0; i < res_pos.size(); i++)
	{
		size_t realInd = res_pos[i];
		if (i != realInd)
		{
			swap(res[realInd], res[i]);
		}
	}

	return res;
}

template<class T>
T Matrix<T>::findDeterminator() {
	T det = T::one;
	Matrix<T> m(*this);
	for (size_t i = 0; i < m.rows(); i++) // прямой ход
	{
		int swapRow = m.findMaxInColumn(i);
		m.swapRows(i, swapRow);

		if (m.matrix[i][i] == T::zero)
		{
			return T::zero;
		}
		det *= m.matrix[i][i];
		m[i] = div_row(m[i], m.matrix[i][i], i);
		for (size_t j = i + 1; j < m.rows(); j++)
		{
			det *= m.matrix[j][i];
			m[j] = div_row(m[j], m.matrix[j][i], i);
			m[j] = sub_row(m[j], m[i], i);
		}
	}
	return det;
}
template<class T>
Matrix<T> Matrix<T>::findReverse() {
	Matrix<T> b(rows());
	for (size_t i = 0; i < rows(); i++) // прямой ход
	{
		for (size_t j = 0; j < columns(); j++)
		{
			if (i == j)
			{
				b[i][j] = T::one;
			}
			else
			{
				b[i][j] = T::zero;
			}
		}
	}

	Matrix<T> m(*this);
	for (size_t i = 0; i < m.rows(); i++) // прямой ход
	{
		int swapRow = m.findMaxInColumn(i);
		m.swapRows(i, swapRow);
		b.swapRows(i, swapRow);

		if (m.matrix[i][i] == T::zero)
		{
			throw MatrixException::div_zero;
		}
		b[i] = div_row(b[i], m.matrix[i][i]);
		m[i] = div_row(m[i], m.matrix[i][i], i);
		for (size_t j = i + 1; j < m.rows(); j++)
		{
			b[j] = div_row(b[j], m.matrix[j][i]);
			b[j] = sub_row(b[j], b[i]);
			m[j] = div_row(m[j], m.matrix[j][i], i);
			m[j] = sub_row(m[j], m[i], i);
		}
	}

	Matrix<T> res(rows());
	for (int i = m.rows() - 1; i >= 0; i--) // обратный ход
	{
		res[i] = b[i];
		for (int j = m.rows() - 1; j > i; j--)
		{
			vector<T> buf = mult_row(res[j], m.matrix[i][j]);
			res[i] = sub_row(res[i], buf);
		}
	}

	return res;
}

