#ifndef Procedure_hpp
#define Procedure_hpp

// Создаем новый тип данных: комплексное число
typedef struct complex {
    double real;
    double imaginary;
} complex;

// Создаем новый тип данных: матрица 3х3
typedef double matrix[3][3];

// Создаем новый тип данных: точка
typedef struct point {
    int x;
    int y;
} point;

// Создаем новый тип данных: вектор
typedef struct vector {
    point a;
    point b;
    point coordinates;
} vector;

// Создаем новый тип данных: окружность
typedef struct circle {
    unsigned int radius;
    point center;
} circle;

// Создаем новый тип данных: квадрат
typedef struct square {
    int edge;
    point a;
    point b;
    point c;
    point d;
} square;

// 1 задание
/// Меняет значения двух входных переменных друг на друга.
void swapReference(int &x, int &y);
void swapPointer(int *x, int *y);

// 2 задание
/// Увеличение значения одной переменной на заданную величину (вторая переменная).
void incrementReference(int &x, int &y);
void incrementPointer(int *x, int *y);

// 3 задание
/// Изменяет большую из двух переменных на её остаток от деления на вторую переменную.
void modReference(int &x, int &y);
void modPointer(int *x, int *y);

// 4 задание
/// Отбрасывает от вещественного числа его дробную часть.
void ceilingPartReference(double &x);
void ceilingPartPointer(double *x);

// 5 задание
/// Отбрасывает от вещественного числа его целую часть.
void fractionalPartReference(double &x);
void fractionalPartPointer(double *x);

// 6 задание
/// Округляет вещественное число.
void roundingReference(double &x);
void roundingPointer(double *x);

// 7 задание
/// Меняют знак переменной (вещественной, целой).
void signChangerReference(double &x);
void signChangerPointer(double *x);

// 8 задание
/// Изменяют вещественную переменную на обратное к ней число.
void multiplicativeInverseReference(double &x);
void multiplicativeInversePointer(double *x);

// 9 задание
/// Умножает комплексную переменную на второй аргумент процедуры — вещественное число.
void complexMultiplicationReference(complex &x, double &y);
void complexMultiplicationPointer(complex *x, double *y);

// 10 задание
/// Меняет комплексную переменную на комплексно сопряженную к ней.
void complexConjugateReference(complex &x);
void complexConjugatePointer(complex *x);

// 11 задание
/// Уменьшает радиус окружности на заданное число.
void radiusReductionReference(circle &c, int &r);
void radiusRedusctionPointer(circle *c, int *r);

// 12 задание
/// Сдвигает окружность на заданный вектор.
void circleShiftReference(circle &c, vector &v);
void circleShiftPointer(circle *c, vector *v);

// 13 задание
/// Передвигает квадрат на заданный вектор.
void squareShiftReference(square &s, vector &v);
void squareShiftPointer(square *s, vector *v);

// 14 задание
/// Транспонирует квадратную матрицу 3x3.
void matrixTransposeReference(matrix &m);
void matrixTransposePointer(matrix *m);

// 15 задание
/// Умножает матрицу 3x3 на вещественное число.
void matrixMultiplicationReference(matrix &m, double &x);
void matrixMultiplicationPointer(matrix *m, double *x);

// 16 задание
/// Меняет в матрице местами две указанные строчки.
void lineSwapReference(matrix &m, int &x, int &y);
void lineSwapPointer(matrix *m, int *x, int *y);

#endif 
