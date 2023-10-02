#pragma once

#include <iostream>
#include <utility>

class RationalException : public std::exception {
private:
    std::string message;
public:
    RationalException()= default;
    RationalException(const RationalException&) noexcept = default;
    [[maybe_unused]] explicit RationalException(std::string message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
	static const RationalException div_zero;
	static const RationalException prec_err;
};