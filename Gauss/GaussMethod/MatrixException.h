#pragma once

#include <iostream>
#include <utility>
class MatrixException : public std::exception
{
private:
    std::string message;
public:
    MatrixException()= default;
    MatrixException(const MatrixException&) noexcept = default;

    [[maybe_unused]] explicit MatrixException(std::string message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }

    static const MatrixException construct_err;
    static const MatrixException div_zero;
	static const MatrixException mult_dims;
	static const MatrixException sum_dims;
};

const MatrixException MatrixException::construct_err("dims must be >= 1!");
const MatrixException MatrixException::div_zero("division by zero!");
const MatrixException MatrixException::mult_dims("wrong dims for multiplication!");
const MatrixException MatrixException::sum_dims("wrong dims for addition!");