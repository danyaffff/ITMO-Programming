#include <vector>
#include "restFunctionsAndEnums.hpp"
#include "exceptions.hpp"
#include "template.hpp"
#include "n-thPowerOfNumber.hpp"

int main(int argc, const char * argv[]) {
    int power;
    
    int width;
    int height;
    int dataType;
    int command;
    
    std::cout << "Введите, каким типом будет степень" << std::endl;
    printDaraTypesForFunction();
    std::cout << "Тип данных: ";
    std::cin >> dataType;
    
    switch (dataType) {
        case integers: {
            int base;
            std::cout << "Введите показатель: ";
            std::cin >> base;
            std::cout << "Введите степень: ";
            std::cin >> power;
            std::cout << base << "^" << power << " = " << pow(base, power) << std::endl;
            break;
        }
            
        case doubles: {
            double base;
            std::cout << "Введите показатель: ";
            std::cin >> base;
            std::cout << "Введите степень: ";
            std::cin >> power;
            std::cout << base << "^" << power << " = " << pow(base, power) << std::endl;
            break;
        }
    }
    
    std::cout << "Введите ширину матрицы: ";
    std::cin >> width;
    std::cout << "Введите высоту матрицы: ";
    std::cin >> height;
    std::cout << std::endl;
    
    std::cout << "Какими элементами вы хотите заполнить матрицу?" << std::endl;
    printDataTypesForMatrix();
    std::cout << "Тип данных: ";
    std::cin >> dataType;
    std::cout << std::endl;
    
    try {
        switch (dataType) {
            case integers: {
                Matrix<int> matrixWithIntegers(width, height);
                matrixWithIntegers.input();
                
                while (true) {
                    printCommands();
                    std::cout << "Введите команду: ";
                    std::cin >> command;
                
                    switch (command) {
                        case stop: {
                            return 0;
                        }
                            
                        case printTheCertainElement: {
                            matrixWithIntegers.printTheCertainElement();
                            break;
                        }
                            
                        case print: {
                            std::cout << "Матрица:" << std::endl;
                            matrixWithIntegers.print();
                            break;
                        }
                            
                        case newMatrx: {
                            matrixWithIntegers.input();
                            break;
                        }
                    }
                }
                
                break;
            }
                
            case doubles: {
                Matrix<double> matrixWithDoubles(width, height);
                matrixWithDoubles.input();
                
                while (true) {
                    printCommands();
                    std::cout << "Введите команду: ";
                    std::cin >> command;
                
                    switch (command) {
                        case stop: {
                            return 0;
                        }
                            
                        case printTheCertainElement: {
                            matrixWithDoubles.printTheCertainElement();
                            break;
                        }
                            
                        case print: {
                            matrixWithDoubles.print();
                            break;
                        }
                            
                        case newMatrx: {
                            matrixWithDoubles.input();
                            std::cout << std::endl;
                            break;
                        }
                    }
                }
                
                break;
            }
        }
    } catch (Exception & exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
}
