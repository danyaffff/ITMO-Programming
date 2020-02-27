#include "Square.hpp"
#include <cmath>
#include <iostream>

square::square(point p, double e, double a): a(p), rib(e), angle(a) {}

double square::getX() {
    return this->a.x;
}

double square::getY() {
    return this->a.y;
}

bool square::operator== (square &s) {
    double square1 = pow(this->rib, 2), square2 = pow(s.rib, 2);
    if (square1 == square2) {
        return true;
    } else {
        return false;
    }
}

bool square::operator!= (square &s) {
    double square1 = pow(this->rib, 2), square2 = pow(s.rib, 2);
    if (square1 == square2) {
        return false;
    } else {
        return true;
    }
}

bool square::operator< (square &s) {
    double square1 = pow(this->rib, 2), square2 = pow(s.rib, 2);
    if (square1 < square2) {
        return true;
    } else {
        return false;
    }
}

bool square::operator> (square &s) {
    double square1 = pow(this->rib, 2), square2 = pow(s.rib, 2);
    if (square1 > square2) {
        return true;
    } else {
        return false;
    }
}

double square::operator* (double &n) {
    this->rib *= n;
    return this->rib;
}

point square::operator+ (vector &v) {
    v.difference.x = v.end.x - v.start.x;
    v.difference.y = v.end.y - v.start.y;
    this->a.x += v.difference.x;
    this->a.y += v.difference.y;
    return this->a;
}

array::array(): size(0), data(nullptr) {}

array::array(int size): size(size) {
    this->data = new int[size];
}

array::array(const array &a): size(a.size) {
    this->data = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        this->data[i] = a.data[i];
    }
}

array::~array() {
    delete []data;
}

void array::set() {
    for (int i = 0; i < this->size; i++) {
        std::cout << "array[" << i << "] = ";
        std::cin >> this->data[i];
    }
}

void array::showArr() {
    for (int i = 0; i < this->size; i++) {
        std::cout << "array[" << i << "] = " << this->data[i] << std::endl;
    }
}

array array::operator+ (array &a) {
    array temp(this->size + a.size);
    int i = 0;
    for (; i < this->size; i++) {
        temp.data[i] = this->data[i];
    }
    for (; i < temp.size; i++) {
        temp.data[i] = a.data[i - size];
    }
    return temp;
}

bool array::operator== (array &a) {
    if (this->size == a.size) {
        return true;
    } else {
        return false;
    }
}

bool array::operator!= (array &a) {
    if (this->size != a.size) {
        return true;
    } else {
        return false;
    }
}

bool array::operator< (array &a) {
    if (this->size < a.size) {
        return true;
    } else {
        return false;
    }
}

bool array::operator> (array &a) {
    if (this->size > a.size) {
        return true;
    } else {
        return false;
    }
}
