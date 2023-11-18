#pragma once

#include "MatrixException.h"
#include "Double.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Matrix {
	vector<vector<Double>> matrix;
	
public:

	static const size_t do_iterations = 20;
	void swapColumns(size_t col1, size_t col2);
	size_t find_maxInRow(size_t row, size_t start);

	istream& input(istream& in);
	ostream& output(ostream& out);

	explicit Matrix();
	explicit Matrix(size_t dim);
	Matrix(size_t row, size_t column);
	Matrix(Matrix const& m1) = default;
	Matrix(Matrix&& m1) = default;

	Matrix& generate(Double upper_bound) {
		for (size_t i = 0; i < rows(); i++)
		{
			for (size_t j = 0; j < columns(); j++) {
				matrix[i][j] = Double::generate_random(upper_bound);
			}
		}
		return *this;
	}
	Matrix& generate_diagDomination(Double upper_bound) {
		generate(upper_bound);
		for (size_t iter = 0; iter < rows(); iter++)
		{
			Double sum_row = Double::zero;
			Double sum_col = Double::zero;
			for (size_t ind = 0; ind < rows(); ind++) {
				sum_row += matrix[iter][ind].abs();
				sum_col += matrix[ind][iter].abs();
			}
			if (sum_row > sum_col)
			{
				matrix[iter][iter] = sum_row;
			}
			else
			{
				matrix[iter][iter] = sum_col;
			}
		}
		return *this;
	}

	Matrix& operator = (Matrix const& m1) = default;
	Matrix& operator = (Matrix && m1) = default;

	[[nodiscard]] inline size_t rows() const {
		return matrix.size();
	}
	[[nodiscard]] inline size_t columns() const {
		return matrix[0].size();
	}
	inline vector<Double>& operator[](size_t row_ind) {
		return matrix[row_ind];
	}
	inline Double scalar(void) {
		return matrix[0][0];
	}

	Matrix transpose();
	Double find_determinator() const;
	Matrix findReverse() const;
	Double norm_sphere();
	Matrix multiply_byNum(Double num) const;

	~Matrix() = default;
};


Matrix::Matrix() {
	matrix = vector<vector<Double>>();
}
Matrix::Matrix(size_t dim) {
	if (dim == 0)
	{
		throw MatrixException(MatrixException::construct_err);
	}
	else
	{
		matrix = vector<vector<Double>>(dim, vector<Double>(dim, Double::zero));
	}
}
Matrix::Matrix(size_t row, size_t column) {
	if (row == 0)
	{
        throw MatrixException(MatrixException::construct_err);
	}
	matrix = vector<vector<Double>>(row, vector<Double>(column, Double::zero));
}

istream& Matrix::input(istream& in) {
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			in >> matrix[i][j];
		}
	}
	return in;
}
ostream& Matrix::output(ostream& out) {
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			out << std::fixed << std::setprecision(2);
			out << std::setw(10) << matrix[i][j];
		}
		out << endl;
	}
	return out;
}


Matrix operator * (Matrix & m1, Matrix & m2)
{
	if (m1.columns() != m2.rows())
	{
        throw MatrixException(MatrixException::mult_dims);
	}
	Matrix res(m1.rows(), m2.columns());
	for (int i = 0; i < m1.rows(); i++)
	{
		for (int j = 0; j < m2.columns(); j++)
		{
			res[i][j] = Double::zero;
			for (int k = 0; k < m1.columns(); k++)
				res[i][j] += m1[i][k] * m2[k][j];
		}
	}
	return res;
}
Matrix operator * (Matrix && m1, Matrix & m2) {
	Matrix buf_m1(std::move(m1));
	return buf_m1 * m2;
}
Matrix operator * (Matrix && m1, Matrix && m2) {
	Matrix buf_m1(std::move(m1));
	Matrix buf_m2(std::move(m2));
	return buf_m1 * buf_m2;
}
Matrix operator + (Matrix & m1, Matrix & m2)
{
	if (m1.rows() != m2.rows() || m1.columns() != m2.columns())
	{
        throw MatrixException(MatrixException::sum_dims);
	}
	Matrix res(m1.rows(), m1.columns());
	for (int i = 0; i < m1.rows(); i++)
	{
		for (int j = 0; j < m1.columns(); j++)
		{
			res[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return res;
}
Matrix operator + (Matrix && m1, Matrix & m2) {
	Matrix buf_m1(std::move(m1));
	return buf_m1 + m2;
}
Matrix operator + (Matrix && m1, Matrix && m2) {
	Matrix buf_m1(std::move(m1));
	Matrix buf_m2(std::move(m2));
	return buf_m1 + buf_m2;
}
Matrix operator - (Matrix & m1, Matrix & m2)
{
	if (m1.rows() != m2.rows() || m1.columns() != m2.columns())
	{
		throw MatrixException(MatrixException::sum_dims);
	}
	Matrix res(m1.rows(), m1.columns());
	for (int i = 0; i < m1.rows(); i++)
	{
		for (int j = 0; j < m1.columns(); j++)
		{
			res[i][j] = m1[i][j] - m2[i][j];
		}
	}
	return res;
}
Matrix operator - (Matrix&& m1, Matrix & m2) {
	Matrix buf_m1(std::move(m1));
	return buf_m1 - m2;
}
Matrix operator - (Matrix& m1, Matrix&& m2) {
	Matrix buf_m2(std::move(m2));
	return m1 - buf_m2;
}
Matrix operator - (Matrix&& m1, Matrix&& m2) {
	Matrix buf_m1(std::move(m1));
	Matrix buf_m2(std::move(m2));
	return buf_m1 - buf_m2;
}


// Обмен столбцов
void Matrix::swapColumns(size_t col1, size_t col2) {
	for (size_t i = 0; i < rows(); i++)
	{
		swap(matrix[i][col1], matrix[i][col2]);
	}
}
// Максимум по остатку строки
size_t Matrix::find_maxInRow(size_t row, size_t start) {
	Double max(0);
	size_t ind = start;
	for (size_t j = start; j < rows(); j++)
	{
		Double maybemax = matrix[row][j].abs();
		if (maybemax > max)
		{
			max = maybemax;
			ind = j;
		}
	}
	return ind;
}

// Вспомогательные функции
void gauss_iteration(Matrix& A, Matrix& b, size_t iter)
{
	// Деление первой строки подматрицы
	Double row_divisor = A[iter][iter];
	for (size_t j = iter; j < A.columns(); j++)
	{
		A[iter][j] /= row_divisor;
	}
	for (size_t j = 0; j < b.columns(); j++)
	{
		b[iter][j] /= row_divisor;
	}

	for (size_t i = iter + 1; i < A.rows(); i++)
	{
		Double row_multiplier = A[i][iter];
		for (size_t j = 0; j < A.columns(); j++)
		{
			A[i][j] -= A[iter][j] * row_multiplier;
		}
		for (size_t j = 0; j < b.columns(); j++)
		{
			b[i][j] -= b[iter][j] * row_multiplier;
		}
	}
}
vector<Double> gauss_reverse_iteration(Matrix& A, Matrix& b, size_t rev_iter)
{
	vector<Double> res_row = b[rev_iter];
	for (int i = 0; i < res_row.size(); i++)
	{
		for (int j = A.rows() - 1; j > rev_iter; j--)
		{
			res_row[i] -= b[j][i] * A[rev_iter][j];
		}
	}
	return res_row;
}

// Метод Гаусса с выбором главного элемента по строке
Matrix solve_system_choiceMaxInLine(Matrix A, Matrix b) {

	vector<size_t> res_pos(b.rows());
	for (size_t i = 0; i < res_pos.size(); i++)
	{
		res_pos[i] = i;
	}

	for (size_t iter = 0; iter < A.rows(); iter++)
	{
		auto swapInd = A.find_maxInRow(iter, iter);
		if (swapInd != iter)
		{
			A.swapColumns(iter, swapInd);
			res_pos[iter] = swapInd;
			res_pos[swapInd] = iter;
		}

		// Проверка на det(m) = ноль
		if (A[iter][iter] == Double::zero)
		{
			throw MatrixException(MatrixException::div_zero);
		}
		
		gauss_iteration(A, b, iter);
	}

	Matrix res(b);
	for (int rev_iter = A.rows() - 1; rev_iter >= 0; rev_iter--)
	{
		res[rev_iter] = gauss_reverse_iteration(A, res, rev_iter);
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
// Метод отражений
Matrix solve_system_reflection(Matrix A, Matrix b)
{
	int one = 1;
	int zero = 0;
	for (size_t iter = 0; iter < A.rows() - 1; iter++)
	{
		Matrix s(one, A.columns());
		// формируем w
		s[zero] = A.transpose()[iter];
		for (size_t i = 0; i < iter; i++)
		{
			s[zero][i] = Double::zero;
		}
		Double alpha = s.norm_sphere();
		Matrix s_1(s);
		s_1[zero][iter] -= alpha;
		s_1 = s_1.transpose();
		Double k = (s * s_1).scalar() * Double::two;
		k = Double::one / Double::sqrt_(k);

		Matrix w(s_1.multiply_byNum(k)); // finally
		auto w_tr = w.transpose();

		// Резня по матрице
		auto m_minus = w_tr * A;
		m_minus = w * m_minus;
		A = A - m_minus.multiply_byNum(Double::two);

		// Резня по b
		auto b_minus = (w * w_tr) * b;
		b = b - b_minus.multiply_byNum(Double::two);
	}

	Matrix res(b);
	for (int rev_iter = A.rows() - 1; rev_iter >= 0; rev_iter--)
	{
		res[rev_iter] = gauss_reverse_iteration(A, res, rev_iter);
		for (size_t i = 0; i < res[rev_iter].size(); i++)
		{
			res[rev_iter][i] /= A[rev_iter][rev_iter];
		}
	}

	return res;
}
// Метод Зейделя (Гаусса - Зейделя)
Matrix solve_system_zeidel(Matrix A, Matrix b)
{
	Matrix x(b);
	Matrix C(A);
	Matrix d(b);
	int zero = 0;

	for (size_t i = 0; i < C.rows(); i++)
	{
		for (size_t j = 0; j < C.columns(); j++) {
			C[i][j] /= Double::zero - A[i][i];
		}
		d[i][zero] /= A[i][i];
		C[i][i] = Double::zero;
	}

	for (size_t iter = 0; iter < Matrix::do_iterations; iter++)
	{
		for (size_t i = 0; i < C.rows(); i++)
		{
			Double buf = Double::zero;
			for (size_t j = 0; j < C.columns(); j++)
			{
				buf += C[i][j] * x[j][zero];
			}
			buf += d[i][zero];
			x[i][zero] = buf;
		}
	}

	return x;
}
// Метод градиентного спуска
Matrix solve_system_gradient(Matrix A, Matrix b)
{
	//A = A.transpose() * A;
	//b = A.transpose() * b;
	Matrix x(b);

	for (size_t iter = 0; iter < Matrix::do_iterations; iter++)
	{
		auto r = (A * x) - b;
		auto r_t = r.transpose();
		auto t = (r_t * r).scalar() / (r_t * A * r).scalar();

		x = x - r.multiply_byNum(t);
	}

	return x;
}


// Транспонирование
Matrix Matrix::transpose() {
	Matrix mt(columns(), rows());
	for (size_t i = 0; i < rows(); i++)
	{
		for (size_t j = 0; j < columns(); j++)
		{
			mt[j][i] = matrix[i][j];
		}
	}
	return mt;
}
// Определитель
Double Matrix::find_determinator() const {
	Double det = Double::one;
	Matrix A(*this);
	for (size_t iter = 0; iter < A.rows(); iter++)
	{
		if (A[iter][iter] == Double::zero)
		{
			return Double::zero;
		}
		det *= A[iter][iter];
		Matrix b(1, 0);

		gauss_iteration(A, b, iter);
	}
	return det;
}
// Обратная матрица
Matrix Matrix::findReverse() const {

	Matrix b(rows());
	for (size_t i = 0; i < rows(); i++)
	{
		b[i][i] = Double::one;
	}
	
	Matrix A(*this);

	return solve_system_choiceMaxInLine(A, b);
}
// Сферическая норма
Double Matrix::norm_sphere() {
	Double norm = Double::zero;
	for (size_t i = 0; i < rows(); i++)
	{
		for (size_t j = 0; j < columns(); j++)
		{
			norm += matrix[i][j] * matrix[i][j];
		}
	}
	return Double::sqrt_(norm);
}
Matrix Matrix::multiply_byNum(Double num) const {
	auto res = *this;
	for (int i = 0; i < rows(); i++)
	{
		for (int j = 0; j < columns(); j++)
		{
			res.matrix[i][j] *= num;
		}
	}
	return res;
}


