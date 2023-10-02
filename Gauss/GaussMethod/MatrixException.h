#pragma once

#include <iostream>
class MatrixException : public std::exception
{
public:
	MatrixException(const char* message) : std::exception(message) {}

	static const MatrixException div_zero;
	static const MatrixException construct_err;
	static const MatrixException mult_dims;
	static const MatrixException sum_dims;
};

const MatrixException MatrixException::div_zero("division by zero!");
const MatrixException MatrixException::construct_err("dims must be >= 1!");
const MatrixException MatrixException::mult_dims("wrong dims for multiplication!");
const MatrixException MatrixException::sum_dims("wrong dims for addition!");