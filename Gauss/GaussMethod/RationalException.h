#pragma once

#include <iostream>

class RationalException : public std::exception {
public:
	RationalException(const char* message) : std::exception(message) {}

	static const RationalException div_zero;
	static const RationalException prec_err;
};
