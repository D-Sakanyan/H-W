#include "Complex.h"

ComplexNumber::ComplexNumber(double r, double i) : real(r), imag(i) {}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imag + other.imag);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imag - other.imag);
}

ComplexNumber ComplexNumber::operator*(double scalar) const {
    return ComplexNumber(real * scalar, imag * scalar);
}

double ComplexNumber::absolute() const {
    return std::sqrt(real * real + imag * imag);
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn) {
    os << cn.real << " + " << cn.imag << "i";
    return os;
}
