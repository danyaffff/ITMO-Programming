/* Лабораторная работа №1. Передача значения по ссылке.
• Объявите (в отельном заголовочном файле) и реализуйте (в другом файле) процедуры (они не возвращают значений!) согласно варианту.
• Все процедуры должны быть написаны в двух вариантах — один вариант использует указатели, второй вариант — ссылки.
• Напишите программу, проверяющую и демонстрирующую правильность работы процедур.
Варианты:
1. Меняет значения двух входных переменных друг на друга.
2. Увеличение значения одной переменной на заданную величину (вторая переменная).
3. Изменяет большую из двух переменных на её остаток от деления на вторую переменную.
4. Отбрасывает от вещественного числа его дробную часть.
5. Отбрасывает от вещественного числа его целую часть.
6. Округляет вещественное число.
7. Меняют знак переменной (вещественной, целой).
8. Изменяют вещественную переменную на обратное к ней число.
9. Умножает комплексную переменную на второй аргумент процедуры — вещественное число.
10. Меняет комплексную переменную (см. вар. 9) на комплексно сопряженную к ней.
11. Уменьшает радиус окружности на заданное число.
12. Сдвигает окружность на заданный вектор.
13. Передвигает квадрат на заданный вектор.
14. Транспонирует квадратную матрицу 3x3.
15. Умножает матрицу 3x3 на вещественное число.
16. Меняет в матрице местами две указанные строчки. */

#include <iostream>
#include "header.hpp"

int main() {
    int in1, in2, *ptrin1 = &in1, *ptrin2 = &in2, itemp, itemp1;
    unsigned int uitemp;
    complex cn, *ptrcn = &cn, cntemp;
    point ptemp;
    vector v, *ptrv = &v;
    matrix m, *ptrm = &m, mtemp;
    double dn, *ptrdn = &dn, dtemp;
    circle c, *ptrc = &c;
    square s, *ptrs = &s, stemp;
    
    std::cout << "Задание 1" << std::endl;
    std::cout << "Введите 2 целочисленных числа, которые мы поменяем местами" << std::endl;
    std::cout << "a: ";
    std::cin >> in1;
    std::cout << "b: ";
    std::cin >> in2;
    itemp = in1;
    itemp1 = in2;
    swapReference(in1, in2);
    std::cout << "После обмена значениями через ссылки" << std::endl;
    std::cout << "a: " << in1 << std::endl;
    std::cout << "b: " << in2 << std::endl;
    in1 = itemp;
    in2 = itemp1;
    swapPointer(ptrin1, ptrin2);
    std::cout << "После обмена значениями через указатели" << std::endl;
    std::cout << "a: " << in1 << std::endl;
    std::cout << "b: " << in2 << std::endl;
    swapPointer(ptrin1, ptrin2);  // Возвращаем указатели на круги своя
    std::cout << std::endl;
    
    std::cout << "Задание 2" << std::endl;
    std::cout << "Введите 2 целочисленных числа" << std::endl;
    std::cout << "Переменная, которую будем увеличивать: ";
    std::cin >> in1;
    std::cout << "Переменная, на которую будем увеличивать: ";
    std::cin >> in2;
    itemp = in1;
    incrementReference(in1, in2);
    std::cout << "Значение первой переменной, после сложения через ссылки: " << in1 << std::endl;
    in1 = itemp;
    incrementPointer(ptrin1, ptrin2);
    std::cout << "Значение первой переменной, после сложения через указатели: " << in1 << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 3" << std::endl;
    std::cout << "Введите 2 целочисленных числа" << std::endl;
    std::cout << "a: ";
    std::cin >> in1;
    std::cout << "b: ";
    std::cin >> in2;
    if ((in1 != 0) && (in2 != 0)) {
        if (in1 >= in2) {
            itemp = in1;
            modReference(in1, in2);
            std::cout << "Значение наибольшей переменной изменилось с помощью ссылок на: " << in1 << std::endl;
            in1 = itemp;
            modPointer(ptrin1, ptrin2);
            std::cout << "Значение наибольшей переменной изменилось с помощью указателей на: " << in1;
        } else {
            itemp = in2;
            modReference(in2, in1);
            std::cout << "Значение наибольшей переменной изменилось с помощью ссылок на: " << in2 << std::endl;
            in2 = itemp;
            modPointer(ptrin2, ptrin1);
            std::cout << "Значение наибольшей переменной изменилось с помощью указателей на: " << in2 << std::endl;
        }
    } else {
        std::cout << "Скорее всего, тут произойдет деление на 0, так что это задание было пропущено" << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Задание 4" << std::endl;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    dtemp = dn;
    ceilingPartReference(dn);
    std::cout << "Целая часть числа, полученная с помощью ссылок: " << dn << std::endl;
    dn = dtemp;
    ceilingPartPointer(ptrdn);
    std::cout << "Целая часть числа, полученная с помощью указателей: " << dn << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 5" << std::endl;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    dtemp = dn;
    fractionalPartReference(dn);
    std::cout << "Дробная часть числа, полученная с помощью ссылок: " << dn << std::endl;
    dn = dtemp;
    fractionalPartPointer(ptrdn);
    std::cout << "Дробная часть числа, полученная с помощью указателей: " << dn << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 6" << std::endl;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    dtemp = dn;
    roundingReference(dn);
    std::cout << "Округление, полученное с помощью ссылок: " << dn << std::endl;
    dn = dtemp;
    roundingPointer(ptrdn);
    std::cout << "Округление, полученное с помощью указателей: " << dn << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 7" << std::endl;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    dtemp = dn;
    signChangerReference(dn);
    std::cout << "Число с противоположным знаком, полученное с помощью ссылок: " << dn << std::endl;
    dn = dtemp;
    signChangerPointer(ptrdn);
    std::cout << "Число с противоположным знаком, полученное с помощью указателей: " << dn << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 8" << std::endl;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    dtemp = dn;
    multiplicativeInverseReference(dn);
    std::cout << "Обратное число, полученное с помощью ссылок: " << dn << std::endl;
    dn = dtemp;
    multiplicativeInversePointer(ptrdn);
    std::cout << "Обратное число, полученное с помощью указателей: " << dn << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 9" << std::endl;
    std::cout << "Введите вещественную часть комплексного числа: ";
    std::cin >> cn.real;
    std::cout << "Введите мнимую часть комплексного числа: ";
    std::cin >> cn.imaginary;
    std::cout << "Введите вещественное число: ";
    std::cin >> dn;
    cntemp = cn;
    complexMultiplicationReference(cn, dn);
    std::cout << "Перемноженное с помощью ссылок комплексное число: " << cn.real;
    if (cn.imaginary >= 0) {
           std::cout << "+";
    }
    std::cout << cn.imaginary << "i" << std::endl;
    cn = cntemp;
    complexMultiplicationPointer(ptrcn, ptrdn);
    std::cout << "Перемноженное с помощью указателей комплексное число: " << cn.real;
    if (cn.imaginary >= 0) {
           std::cout << "+";
    }
    std::cout << cn.imaginary << "i" << std::endl;
    std::cout << std::endl;

    std::cout << "Задание 10" << std::endl;
    std::cout << "Введите вещественную часть комплексного числа: ";
    std::cin >> cn.real;
    std::cout << "Введите мнимую часть комплексного числа: ";
    std::cin >> cn.imaginary;
    cntemp = cn;
    complexConjugateReference(cn);
    std::cout << "Комплексно сопряженное число, полученное с помощью ссылок: " << cn.real;
    if (cn.imaginary >= 0) {
        std::cout << "+";
    }
    std::cout << cn.imaginary << "i" << std::endl;
    cn = cntemp;
    complexConjugatePointer(ptrcn);
    std::cout << "Комплексно сопряженное число, полученное с помощью указателей: " << cn.real;
    if (cn.imaginary >= 0) {
        std::cout << "+";
    }
    std::cout << cn.imaginary << "i" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 11" << std::endl;
    std::cout << "Введите радиус окружности: ";
    std::cin >> c.radius;
    std::cout << "Введите число, на которое будет уменьшен радиус: ";
    std::cin >> in1;
    uitemp = c.radius;
    radiusReductionReference(c, in1);
    std::cout << "Нынешний размер радиуса, полученный с помощью ссылок: " << c.radius << std::endl;
    c.radius = uitemp;
    radiusRedusctionPointer(ptrc, ptrin1);
    std::cout << "Нынешний размер радиуса, полученный с помощью указателей: " << c.radius << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 12" << std::endl;
    std::cout << "Введите координаты центра окружности" << std::endl;
    std::cout << "Координата x: ";
    std::cin >> c.center.x;
    std::cout << "Координата y: ";
    std::cin >> c.center.y;
    std::cout << "Введите начальную координату вектора: " << std::endl;
    std::cout << "x: ";
    std::cin >> v.a.x;
    std:: cout << "y: ";
    std::cin >> v.a.y;
    std::cout << "Введите конечную координату вектора: " << std::endl;
    std::cout << "x: ";
    std::cin >> v.b.x;
    std:: cout << "y: ";
    std::cin >> v.b.y;
    ptemp = c.center;
    circleShiftReference(c, v);
    std::cout << "Новые координаты центра окружности, полученные с помощью ссылок" << std::endl;
    std::cout << "x: " << c.center.x << std::endl;
    std::cout << "y: " << c.center.y << std::endl;
    c.center = ptemp;
    circleShiftPointer(ptrc, ptrv);
    std::cout << "Новые координаты центра окружности, полученные с помощью указателей" << std::endl;
    std::cout << "x: " << c.center.x << std::endl;
    std::cout << "y: " << c.center.y << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 13" << std::endl;
    std::cout << "Введите координаты левой нижней точки квадрата" << std::endl;;
    std::cout << "Координата x: ";
    std::cin >> s.d.x;
    std::cout << "Координата y: ";
    std::cin >> s.d.y;
    std::cout << "Введите длину ребра: ";
    std::cin >> s.edge;
    std::cout << "Введите начальную координату вектора" << std::endl;
    std::cout << "x: ";
    std::cin >> v.a.x;
    std:: cout << "y: ";
    std::cin >> v.a.y;
    std::cout << "Введите конечную координату вектора" << std::endl;
    std::cout << "x: ";
    std::cin >> v.b.x;
    std:: cout << "y: ";
    std::cin >> v.b.y;
    stemp = s;
    squareShiftReference(s, v);
    std::cout << "Новые координаты точки A, полученные с помощью ссылок" << std::endl;
    std::cout << "x: " << s.a.x << std::endl;
    std::cout << "y: " << s.a.y << std::endl;
    std::cout << "Новые координаты точки B, полученные с помощью ссылок" << std::endl;
    std::cout << "x: " << s.b.x << std::endl;
    std::cout << "y: " << s.b.y << std::endl;
    std::cout << "Новые координаты точки C, полученные с помощью ссылок" << std::endl;
    std::cout << "x: " << s.c.x << std::endl;
    std::cout << "y: " << s.c.y << std::endl;
    std::cout << "Новые координаты точки D, полученные с помощью ссылок" << std::endl;
    std::cout << "x: " << s.d.x << std::endl;
    std::cout << "y: " << s.d.y << std::endl;
    s = stemp;
    squareShiftPointer(ptrs, ptrv);
    std::cout << "Новые координаты точки A, полученные с помощью указателей" << std::endl;
    std::cout << "x: " << s.a.x << std::endl;
    std::cout << "y: " << s.a.y << std::endl;
    std::cout << "Новые координаты точки B, полученные с помощью указателей" << std::endl;
    std::cout << "x: " << s.b.x << std::endl;
    std::cout << "y: " << s.b.y << std::endl;
    std::cout << "Новые координаты точки C, полученные с помощью указателей" << std::endl;
    std::cout << "x: " << s.c.x << std::endl;
    std::cout << "y: " << s.c.y << std::endl;
    std::cout << "Новые координаты точки D, полученные с помощью указателей" << std::endl;
    std::cout << "x: " << s.d.x << std::endl;
    std::cout << "y: " << s.d.y << std::endl;
    std::cout << std::endl;
    
    std::cout << "Задание 14" << std::endl;
    std::cout << "Заполните матрицу 3x3" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> m[i][j];
            mtemp[i][j] = m[i][j];
        }
    }
    matrixTransposeReference(m);
    std::cout << "Матрица после транспонирования, сделанного с помощью ссылок" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[i][j] << " ";
            m[i][j] = mtemp[i][j];
        }
        std::cout << std::endl;
    }
    matrixTransposePointer(ptrm);
    std::cout << "Матрица после транспонирования, сделанного с помощью указателей" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Задание 15" << std::endl;
    std::cout << "Введите вещественное число, на которое будем умножать матрицу: ";
    std::cin >> dn;
    std::cout << "Заполните матрицу 3x3" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> m[i][j];
            mtemp[i][j] = m[i][j];
        }
    }
    matrixMultiplicationReference(m, dn);
    std::cout << "Матрица после умножения, сделанного с помощью ссылок" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[i][j] << " ";
            m[i][j] = mtemp[i][j];
        }
        std::cout << std::endl;
    }
    matrixMultiplicationPointer(ptrm, ptrdn);
    std::cout << "Матрица после умножения, сделанного с помощью указателей:" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Задание 16" << std::endl;
    std::cout << "Введите номера строк, которые мы будем менять местами" << std::endl;
    std::cout << "Перввый номер: ";
    std::cin >> in1;
    in1--;
    std::cout << "Второй номер: ";
    std::cin >> in2;
    in2--;
    std::cout << "Заполните матрицу 3x3" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> m[i][j];
            mtemp[i][j] = m[i][j];
        }
    }
    lineSwapReference(m, in1, in2);
    std::cout << "Матрица после перестановки строк, сделанной с помощью ссылок" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << m[i][j] << " ";
            m[i][j] = mtemp[i][j];
        }
        std::cout << std::endl;
    }
    lineSwapPointer(ptrm, ptrin1, ptrin2);
    std::cout << "Матрица после перестановки строк, сделанной с помощью указателей" << std::endl;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
