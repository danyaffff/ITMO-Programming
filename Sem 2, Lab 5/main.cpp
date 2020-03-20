#include <vector>
#include "exceptions.hpp"
#include "template.hpp"
using namespace std;

void printDataTypes() {
    cout << "0. Целыми числами" << endl;
    cout << "1. Вещественными числами" << endl;
}

enum DataTypes {
    integers,
    doubles,
    chars,
};

void printCommands() {
    cout << "1. Вывести определнный элемент" << endl;
    cout << "2. Вывести матрицу" << endl;
    cout << "3. Ввести новую матрицу" << endl;
    cout << "0. Завершить программу" << endl;
}

enum Commands {
    stop,
    printTheCertainElement,
    print,
    newMatrx,
};

int main(int argc, const char * argv[]) {
    int width;
    int height;
    int dataType;
    int command;
    
    try {
        cout << "Введите ширину матрицы: ";
        cin >> width;
        cout << "Введите высоту матрицы: ";
        cin >> height;
        cout << endl;
        
        cout << "Какими элементами вы хотите заполнить матрицу?" << endl;
        printDataTypes();
        cout << "Тип данных: ";
        cin >> dataType;
        cout << endl;
        
        switch (dataType) {
            case integers: {
                Matrix<int> matrixWithIntegers(width, height);
                matrixWithIntegers.input();
                
                while (true) {
                    printCommands();
                    cout << "Введите команду: ";
                    cin >> command;
                
                    switch (command) {
                        case stop: {
                            return 0;
                        }
                            
                        case printTheCertainElement: {
                            matrixWithIntegers.printTheCertainElement();
                            break;
                        }
                            
                        case print: {
                            cout << "Матрица:" << endl;
                            matrixWithIntegers.print();
                            break;
                        }
                            
                        case newMatrx: {
                            cout << "Введите новые элементы матрицы" << endl;
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
                    cout << "Введите команду: ";
                    cin >> command;
                
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
                            cout << "Введите новые элементы матрицы" << endl;
                            matrixWithDoubles.input();
                            cout << endl;
                            break;
                        }
                    }
                }
                
                break;
            }
        }
    } catch (Exception & exception) {
        cerr << exception.what() << endl;
        return 1;
    }
}
