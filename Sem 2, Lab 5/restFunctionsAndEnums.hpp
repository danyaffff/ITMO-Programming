#ifndef restFunctionsAndEnums_hpp
#define restFunctionsAndEnums_hpp
#include <iostream>

void printDaraTypesForFunction() {
    std::cout << "0. Целое число" << std::endl;
    std::cout << "1. Вещественное число" << std::endl;
}

void printDataTypesForMatrix() {
    std::cout << "0. Целыми числами" << std::endl;
    std::cout << "1. Вещественными числами" << std::endl;
}

enum DataTypes {
    integers,
    doubles,
};

void printCommands() {
    std::cout << "1. Вывести определенный элемент" << std::endl;
    std::cout << "2. Вывести матрицу" << std::endl;
    std::cout << "3. Ввести новые элементы матрицы" << std::endl;
    std::cout << "0. Завершить программу" << std::endl;
}

enum Commands {
    stop,
    printTheCertainElement,
    print,
    newMatrx,
};

#endif
