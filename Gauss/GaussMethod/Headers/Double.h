#pragma once

#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <random>

#include "RationalException.h"

class Double
{
public:
	double num;

	static size_t precision;
	static bool use_precision;

	static const Double zero;
	static const Double one;
	static const Double two;
	static const Double ten;

	static Double generate_random(Double up_low_bound) {
		std::random_device rd;  // Используется для получения случайного числа от аппаратного устройства
		std::mt19937 gen(rd()); // Генератор случайных чисел
		std::uniform_real_distribution<> dis(zero.num - up_low_bound.num, up_low_bound.num); // Равномерное распределение

		double num = dis(gen);
		if (use_precision)
		{
			roundToN(num, precision);
		}
		return Double(num);
	}
	static Double sqrt_(Double d) {
		return Double(sqrt(d.num));
	}

	static void set_type_precision(size_t prec) {
		precision = prec;
		use_precision = true;
	}
	static void turn_precision_off() {
		use_precision = false;
	}
	static double roundToN(double num, size_t n) {
		double scale = std::pow(10.0, n);
		return std::round(num * scale) / scale;
	}

	Double() = default;
	explicit Double(double _num);
	Double(Double const& r) = default;
	Double(Double&& r) = default;
	explicit Double(std::string const& str);

	std::string toString();
	[[nodiscard]] Double abs() const;

	friend std::istream& operator >> (std::istream& in, Double& r);
	friend std::ostream& operator << (std::ostream& out, Double& r);

	Double& operator = (Double const& r) = default;
	Double& operator += (Double const& r);
	Double& operator -= (Double const& r);
	Double& operator *= (Double const& r);
	Double& operator /= (Double const& r);

	friend Double operator + (Double const& r1, Double const& r2);
	friend Double operator - (Double const& r1, Double const& r2);
	friend Double operator * (Double const& r1, Double const& r2);
	friend Double operator / (Double const& r1, Double const& r2);

	bool operator < (Double const& r) const;
	bool operator <= (Double const& r) const;
	bool operator > (Double const& r) const;
	bool operator >= (Double const& r) const;
	bool operator == (Double const& r) const;
};

