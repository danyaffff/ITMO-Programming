#include <cmath>
#include <iostream>
#include "header.hpp"

complex::complex(): real(0), imaginary(0) {}
complex::complex(double real): real(real), imaginary(0) {}
complex::complex(double real, double imaginary): real(real), imaginary(imaginary) {}
complex::complex(const complex &c): real(c.real), imaginary(c.imaginary) {}

double complex::re() {
    return this->real;
}

double complex::im() {
    return this->imaginary;
}

complex complex::operator+ (complex &c) {
    return complex(this->re() + c.re(), this->im() + c.im());
}

complex complex::operator* (complex &c) {
    return complex(this->re() * c.re() - this->im() * c.im(), this->re() * c.im() + this->im() * c.re());
}

complex complex::length() {
    return complex(sqrt(pow(re(), 2) + pow(im(), 2)));
}

void complex::print() {
    cout << re();
    if (im() != 0) {
        if (im() > 0) {
            cout << " + " << im() << "i";
        } else {
            cout << " - " << -im() << "i";
        }
    }
}
