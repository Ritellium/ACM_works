#pragma once

#include <iostream>
#include <utility>

class NumberException : public std::exception {
private:
    std::string message;
public:
    NumberException()= default;
    NumberException(const NumberException&) noexcept = default;
    [[maybe_unused]] explicit NumberException(std::string message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
	static const NumberException div_zero;
	static const NumberException prec_err;
};