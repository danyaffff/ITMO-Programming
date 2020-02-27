#ifndef Complex_hpp
#define Complex_hpp
#include <iostream>
using namespace std;

class complex {
    double real;
    double imaginary;
    
public:
    complex();  // Конструктор по умолчанию
    complex(double);  // Конеструктор вещественного числа
    complex(double, double);  // Конструктор комплексного числа
    complex(const complex &);  // Конструктор копирования
    
    auto re() -> double;
    auto im() -> double;
    
    auto operator+ (complex &) -> complex;
    auto operator* (complex &) -> complex;
    
    auto length() -> complex;
    
    auto print() -> void;
};

#endif
