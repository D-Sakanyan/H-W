#include "complex.h"

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(double constant) const {
    return Complex(real_ * constant, imag_ * constant);
}

double Complex::absolute() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real_ << " + " << c.imag_ << "i";
    return os;
}

