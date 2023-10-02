#pragma once

#include <vector>
#include <cmath>
#include <numeric>
#include <string>

#include "RationalException.h"

class Rational
{
public:
	long long top;
	long long down;

	static const Rational zero;
	static const Rational one;

	Rational();
	explicit Rational(long long _top);
	Rational(long long _top, long long _down);
	Rational(Rational const& r) = default;
	Rational(Rational&& r) = default;
	explicit Rational(std::string const& str);

	std::string toString();
	Rational fromString(std::string const& str);
	[[nodiscard]] Rational abs() const;

	friend std::istream& operator >> (std::istream& in, Rational& r);
	friend std::ostream& operator << (std::ostream& out, Rational& r);

	Rational& fromDouble(double r, unsigned int pres);
	[[nodiscard]] double toDouble() const;

	void normalize();
	static long long gcd(long long a, long long b);
	Rational& inverse();

	Rational& operator = (Rational const& r) = default;
	Rational& operator += (Rational const& r);
	Rational& operator -= (Rational const& r);
	Rational& operator *= (Rational const& r);
	Rational& operator /= (Rational const& r);

	friend Rational operator + (Rational const& r1, Rational const& r2);
	friend Rational operator - (Rational const& r1, Rational const& r2);
	friend Rational operator * (Rational const& r1, Rational const& r2);
	friend Rational operator / (Rational const& r1, Rational const& r2);

	bool operator < (Rational const& r) const;
	bool operator <= (Rational const& r) const;
	bool operator > (Rational const& r) const;
	bool operator >= (Rational const& r) const;
	bool operator == (Rational const& r) const;
};
