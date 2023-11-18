#include "../Headers/Double.h"

size_t Double::precision = 0;
bool Double::use_precision = false;
const Double Double::zero = Double(0);
const Double Double::one = Double(1);
const Double Double::two = Double(2);
const Double Double::ten = Double(10);

Double::Double(double _num) : num(_num) {}

Double::Double(std::string const& str) {
	num = stod(str);
}

std::string Double::toString() {
	return std::to_string(num);
}

Double Double::abs() const {
	return Double(std::abs(num));
}

std::istream& operator >> (std::istream& in, Double& r) {
	std::string str;
	in >> r.num;
	return in;
}
std::ostream& operator << (std::ostream& out, Double& r) {
	out << r.num;
	return out;
}

Double& Double::operator += (Double const& r) {
	num += r.num;
	if (use_precision)
	{
		roundToN(num, precision);
	}
	return *this;
}
Double& Double::operator -= (Double const& r) {
	num -= r.num;
	if (use_precision)
	{
		roundToN(num, precision);
	}
	return *this;
}
Double& Double::operator *= (Double const& r) {
	num *= r.num;
	if (use_precision)
	{
		roundToN(num, precision);
	}
	return *this;
}
Double& Double::operator /= (Double const& r) {
	num /= r.num;
	if (use_precision)
	{
		roundToN(num, precision);
	}
	return *this;
}

Double operator + (Double const& r1, Double const& r2) {
	Double res;
	res.num = r1.num + r2.num;
	if (Double::use_precision)
	{
		res.num = Double::roundToN(res.num, Double::precision);
	}
	return res;
}
Double operator - (Double const& r1, Double const& r2) {
	Double res;
	res.num = r1.num - r2.num;
	if (Double::use_precision)
	{
		res.num = Double::roundToN(res.num, Double::precision);
	}
	return res;
}
Double operator * (Double const& r1, Double const& r2) {
	Double res;
	res.num = r1.num * r2.num;
	if (Double::use_precision)
	{
		res.num = Double::roundToN(res.num, Double::precision);
	}
	return res;
}
Double operator / (Double const& r1, Double const& r2) {
	Double res;
	res.num = r1.num / r2.num;
	if (Double::use_precision)
	{
		res.num = Double::roundToN(res.num, Double::precision);
	}
	return res;
}

bool Double::operator < (Double const& r) const {
	return num < r.num;
}
bool Double::operator <= (Double const& r) const {
	return num <= r.num;
}
bool Double::operator > (Double const& r) const {
	return num > r.num;
}
bool Double::operator >= (Double const& r) const {
	return num >= r.num;
}
bool Double::operator == (Double const& r) const {
	return num == r.num;
}