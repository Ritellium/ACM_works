#include "Rational.h"

const Rational Rational::zero = Rational(0, 1);
const Rational Rational::one = Rational(1, 1);

Rational::Rational() : top(0), down(1) {}
Rational::Rational(long long _top) : top(_top), down(1) {}
Rational::Rational(long long _top, long long _down)
{
	if (_down == 0)
        throw RationalException(RationalException::div_zero);
	else {
		top = _top;
		down = _down;
	}
}

Rational::Rational(std::string const& str) {
	size_t i = str.find('/');
	if (i == -1)
	{
		i = str.length();
		down = 1;
	}
	else {
		down = stoll(str.substr(i + 1));
	}
	top = stoll(str.substr(0, i));

	normalize();
}

std::string Rational::toString() {
	normalize();
	if (down != 1)
		return std::to_string(top) + "/" + std::to_string(down);
	else
		return std::to_string(top);
}
Rational Rational::fromString(std::string const& str) {
	size_t i = str.find('/');
	if (i == -1)
	{
		i = str.length();
		down = 1;
	}
	else {
		down = stoll(str.substr(i + 1));
	}
	top = stoll(str.substr(0, i));

	normalize();
	return *this;
}
Rational Rational::abs() const {
	Rational res;
	res.top = std::abs(top);
	res.down = std::abs(down);
	return res;
}

std::istream& operator >> (std::istream& in, Rational& r) {
	std::string str;
	in >> str;
	r.fromString(str);
	return in;
}
std::ostream& operator << (std::ostream& out, Rational& r) {

	out << r.toString();
	return out;
}

Rational& Rational::inverse() {
	if (top == 0)
	{
        throw RationalException(RationalException::div_zero);
	}
	else {
		long long buf = top;
		top = down;
		down = buf;
	}
	return *this;
}
long long Rational::gcd(long long a, long long b) {
	while (b != 0) {
		long long temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
void Rational::normalize() {
	long long gcd = Rational::gcd(top, down);
	if (gcd == 0)
	{
		down = 1;
	}
	else
	{
		top /= gcd;
		down /= gcd;
	}
}

double Rational::toDouble() const {
	return double(top) / double(down);
}
Rational& Rational::fromDouble(double r, unsigned int pres) {
	if (pres > 18)
	{
        throw RationalException(RationalException::prec_err);
	}
	down = 1;
	int sub = 0;
	while (r > double(down))
	{
		down *= 10;
		sub++;
	}
	down = 1;
	for (size_t i = 0; i < pres - sub; i++)
	{
		down *= 10;
		r *= double(10);
	}
	top = (long long)r;
	normalize();
	return *this;
}

Rational& Rational::operator += (Rational const& r) {
	top = top * r.down + r.top * down;
	down *= r.down;
	normalize();
	return *this;
}
Rational& Rational::operator -= (Rational const& r) {
	top = top * r.down - r.top * down;
	down *= r.down;
	normalize();
	return *this;
}
Rational& Rational::operator *= (Rational const& r) {
	top *= r.top;
	down *= r.down;
	normalize();
	return *this;
}
Rational& Rational::operator /= (Rational const& r) {
	if (r.top == 0)
	{
        throw RationalException(RationalException::div_zero);
	}
	top *= r.down;
	down *= r.top;
	normalize();
	return *this;
}

Rational operator + (Rational const& r1, Rational const& r2) {
	Rational res;
	res.top = r1.top * r2.down + r2.top * r1.down;
	res.down = r1.down * r2.down;
	res.normalize();
	return res;
}
Rational operator - (Rational const& r1, Rational const& r2) {
	Rational res;
	res.top = r1.top * r2.down - r2.top * r1.down;
	res.down = r1.down * r2.down;
	res.normalize();
	return res;
}
Rational operator * (Rational const& r1, Rational const& r2) {
	Rational res;
	res.top = r1.top * r2.top;
	res.down = r1.down * r2.down;
	res.normalize();
	return res;
}
Rational operator / (Rational const& r1, Rational const& r2) {
	if (r2.top == 0)
	{
        throw RationalException(RationalException::div_zero);
	}
	Rational res;
	res.top = r1.top * r2.down;
	res.down = r1.down * r2.top;
	res.normalize();
	return res;
}

bool Rational::operator < (Rational const& r) const {
	return top * r.down - r.top * down < 0;
}
bool Rational::operator <= (Rational const& r) const {
	return top * r.down - r.top * down <= 0;
}
bool Rational::operator > (Rational const& r) const {
	return top * r.down - r.top * down > 0;
}
bool Rational::operator >= (Rational const& r) const {
	return top * r.down - r.top * down >= 0;
}
bool Rational::operator == (Rational const& r) const {
	return top * r.down - r.top * down == 0;
}