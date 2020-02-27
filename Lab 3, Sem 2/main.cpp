/* Лабораторная работа №3. Перегрузка операторов.
Согласно варианту описать указанные типы данных и поместить их в отдельный
заголовочный файл, в нем же описать операторы, указанные в варианте. Реализацию
функций поместить с отдельный cpp файл.
Написать программу, проверяющую правильность работы — для наглядности и лучшего
усвоения материала использовать как явный, так и не явный метод вызова функций
операторов.

1. Тип данных: Квадрат на плоскости. Задается координатой левого верхнего угла,
стороной квадрата и углом, на который квадрат повернут относительно оси OX.
Операторы: равенство площадей квадратов (перегрузите операции ==, !=, <, >),
умножение квадрата на вещественное число (увеличивает сторону квадрата),
прибавление к квадрату вектора (смещение квадрата на указанный вектор).
 
2. Тип данных: Массив целых чисел (длина не более 100).
Операторы: объединение двух массивов в один (operator+), сравнение длин массивов
(==, >, < !=). */
#include <iostream>
#include "Square.hpp"

int main() {
    point p;
    double rib;
    double angle;
    std::cout << "Введите координату верхней левой точки первого квадрата" << std::endl;
    std::cout << "x: ";
    std::cin >> p.x;
    std::cout << "y: ";
    std::cin >> p.y;
    std::cout << "Введите длину ребра первого квадрата: ";
    std::cin >> rib;
    std::cout << "Введите угол поворота первого квадрата: ";
    std::cin >> angle;
    square s1(p, rib, angle);
    std::cout << "Введите координату верхней левой точки второго квадрата" << std::endl;
    std::cout << "x: ";
    std::cin >> p.x;
    std::cout << "y: ";
    std::cin >> p.y;
    std::cout << "Введите длину ребра второго квадрата: ";
    std::cin >> rib;
    std::cout << "Введите угол поворота второго квадрата: ";
    std::cin >> angle;
    square s2(p, rib, angle);

    std::cout << "Площади равны (явный вызов): ";
    if (s1.operator==(s2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Площади равны (неявный вызов): ";
    if (s1 == s2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Площади не равны (явный вызов): ";
    if (s1.operator!=(s2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Площади не равны (неявный вызов): ";
    if (s1 != s2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Площадь первого больше площади второго (явный вызов): ";
    if (s1.operator>(s2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Площадь первого больше площади второго (неявный вызов): ";
    if (s1 > s2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Площадь второго больше площади первого (явный вызов): ";
    if (s1.operator<(s2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Площадь второго больше площади первого (неявный вызов): ";
    if (s1 < s2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Увеличение стороны квадрата в n раз" << std::endl;
    double n;
    std::cout << "Введите вещественное число: ";
    std::cin >> n;
    std::cout << "Теперь сторона квадрата равна (явный вызов): " << s1.operator*(n) << std::endl;
    std::cout << "Теперь сторона квадрата равна (неявный вызов): " << s1 * n << std::endl;

    std::cout << "Смещение квадрата на вектор" << std::endl;
    vector v;
    std::cout << "Введите начальную координату вектора" << std::endl;
    std::cout << "x: ";
    std::cin >> v.start.x;
    std::cout << "y: ";
    std::cin >> v.start.y;
    std::cout << "Введите конечную координату вектора" << std::endl;
    std::cout << "x: ";
    std::cin >> v.end.x;
    std::cout << "y: ";
    std::cin >> v.end.y;
    std::cout << "Точка после смещения (явный вызов)" << std::endl;
    s1.operator+(v);
    std::cout << "x: " << s1.getX() << std::endl;
    std::cout << "y: " << s1.getY() << std::endl;
    std::cout << "Точка после смещения (неявный вызов)" << std::endl;
    s1 + v;
    std::cout << "x: " << s1.getX() << std::endl;
    std::cout << "y: " << s1.getY() << std::endl;
    
    std::cout << "Введите размер первого массива: ";
    int size;
    std::cin >> size;
    array a1(size);
    std::cout << "Заполните массив" << std::endl;
    a1.set();
    std::cout << "Введите размер второго массива: ";
    std::cin >> size;
    array a2(size);
    std::cout << "Заполните массив" << std::endl;
    a2.set();
    std::cout << "Результат" << std::endl;
    array result = a1 + a2;
    result.showArr();
    
    std::cout << "Сравнение перовго и второго массивов" << std::endl;
    std::cout << "Длины равны (явный вызов): ";
    if (a1.operator==(a2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Длины равны (неявный вызов): ";
    if (a1 == a2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    
    std::cout << "Длины неравны (явный вызов): ";
    if (a1.operator!=(a2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Длины неравны (неявный вызов): ";
    if (a1 != a2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    
    std::cout << "Длина первого массива больше (явный вызов): ";
    if (a1.operator>(a2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Длина первого массива больше (неявный вызов): ";
    if (a1 > a2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    
    std::cout << "Длина второго массива больше (явный вызов): ";
    if (a1.operator<(a2)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << "Длина второго массива больше (неявный вызов): ";
    if (a1 < a2) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
}
