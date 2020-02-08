#include <cmath>
#include <utility>
#include <iostream>
#include "Procedure.hpp"

// 1 задание
void swapReference(int &x, int &y) {
    x = x + y;
    y = x - y;
    x = x - y;
}

void swapPointer(int *x, int *y) {
    int *temp = new int();
    *temp = *x;
    *x = *y;
    *y = *temp;
}

// 2 задание
void incrementReference(int &x, int &y) {
    x += y;
}
void incrementPointer(int *x, int *y) {
    *x += *y;
}

// 3 задание
void modReference(int &x, int &y) {
    x = x % y;
}

void modPointer(int *x, int *y) {
    *x = *x % *y;
}

// 4 задание
void ceilingPartReference(double &x) {
    x = floor(x);
}

void ceilingPartPointer(double *x) {
    *x = floor(*x);
}

// 5 задание
void fractionalPartReference(double &x) {
    int ceil = (int)x;
    x -= ceil;
}

void fractionalPartPointer(double *x) {
    int ceil = (int)*x;
    *x -= ceil;
}

// 6 задание
void roundingReference(double &x) {
    x = round(x);
}

void roundingPointer(double *x) {
    *x = round(*x);
}

// 7 задание
void signChangerReference(double &x) {
    x = -x;
}

void signChangerPointer(double *x) {
    *x = -*x;
}

// 8 задание
void multiplicativeInverseReference(double &x) {
    x = 1 / x;
}

void multiplicativeInversePointer(double *x) {
    *x = 1 / *x;
}

// 9 задание
void complexMultiplicationReference(complex &x, double &y) {
    x.real *= y;
    x.imaginary *= y;
}

void complexMultiplicationPointer(complex *x, double *y) {
    x->real *= *y;
    x->imaginary *= *y;
}

// 10 задание
void complexConjugateReference(complex &x) {
    x.imaginary = -x.imaginary;
}

void complexConjugatePointer(complex *x) {
    x->imaginary = -x->imaginary;
}

// 11 задание
void radiusReductionReference(circle &c, int &r) {
    c.radius -= r;
}

void radiusRedusctionPointer(circle *c, int *r) {
    c->radius -= *r;
}

// 12 задание
void circleShiftReference(circle &c, vector &v) {
    v.coordinates.x = v.b.x - v.a.x;
    v.coordinates.y = v.b.y - v.a.y;
    c.center.x += v.coordinates.x;
    c.center.y += v.coordinates.y;
}

void circleShiftPointer(circle *c, vector *v) {
    v->coordinates.x = v->b.x - v->a.x;
    v->coordinates.y = v->b.y - v->a.y;
    c->center.x += v->coordinates.x;
    c->center.y += v->coordinates.y;
}

// 13 задание
void squareShiftReference(square &s, vector &v) {
    v.coordinates.x = v.b.x - v.a.x;
    v.coordinates.y = v.b.y - v.a.y;
    s.a.x = s.d.x + v.coordinates.x;
    s.a.y = s.d.y + s.edge + v.coordinates.y;
    s.b.x = s.d.x + s.edge + v.coordinates.x;
    s.b.y = s.d.y + s.edge + v.coordinates.y;
    s.c.x = s.d.x + s.edge + v.coordinates.x;
    s.c.y = s.d.y + v.coordinates.y;
    s.d.x += v.coordinates.x;
    s.d.y += v.coordinates.y;
}

void squareShiftPointer(square *s, vector *v) {
    v->coordinates.x = v->b.x - v->a.x;
    v->coordinates.y = v->b.y - v->a.y;
    s->a.x = s->d.x + v->coordinates.x;
    s->a.y = s->d.y + s->edge + v->coordinates.y;
    s->b.x = s->d.x + s->edge + v->coordinates.x;
    s->b.y = s->d.y + s->edge + v->coordinates.y;
    s->c.x = s->d.x + s->edge + v->coordinates.x;
    s->c.y = s->d.y + v->coordinates.y;
    s->d.x += v->coordinates.x;
    s->d.y += v->coordinates.y;
}

// 14 задание
void matrixTransposeReference(matrix &m) {
    double temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}

void matrixTransposePointer(matrix *m) {
    double temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            temp = (*m)[i][j];
            (*m)[i][j] = (*m)[j][i];
            (*m)[j][i] = temp;
        }
    }
}

// 15 задание
void matrixMultiplicationReference(matrix &m, double &x) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] *= x;
        }
    }
}

void matrixMultiplicationPointer(matrix *m, double *x) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*m)[i][j] *= *x;
        }
    }
}

// 16 задание
void lineSwapReference(matrix &m, int &x, int &y) {
    std::swap(m[x], m[y]);
}

void lineSwapPointer(matrix *m, int *x, int *y) {
    std::swap((*m)[*x], (*m)[*y]);
}
