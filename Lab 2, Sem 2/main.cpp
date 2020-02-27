#include <iostream>
#include "header.hpp"

int main() {
    double r, i;
    cout << "Введите вещественное число: ";
    cin >> r;
    complex re(r);
    cout << "Введите вещественную часть первого комплексного числа: ";
    cin >> r;
    cout << "Введите мнимую часть перовго комплексного числа: ";
    cin >> i;
    complex c1(r, i);
    cout << "Введите вещественную часть второго комплексного числа: ";
    cin >> r;
    cout << "Введите мнимую часть второго комплексного числа: ";
    cin >> i;
    cout << endl;
    
    complex c2(r, i);
    cout << "Умножение вещественного числа на первое комплексное число: ";
    complex result = re * c1;
    result.print();
    cout << endl;
    cout << "Сложение комплексных чисел: ";
    result = c1 + c2;
    result.print();
    cout << endl;
    cout << "Перемножение комплексных чисел: ";
    result = c1 * c2;
    result.print();
    cout << endl;
    cout << "Длина первого комплексного числа: ";
    result = c1.length();
    result.print();
    cout << endl;
}
