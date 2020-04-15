/* Лабораторная работа №4. Виртуальные функции.
Реализовать все указанные интерфейсы (абстрактные базовые классы) для
классов. */

#include <vector>
#include <algorithm>
#include "interfaces.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

void printCommands() {
    cout << "1. Добавить новую фигуру;" << endl;
    cout << "2. Вывести площадь текущей фигуры;" << endl;
    cout << "3. Вывести периметр текущей фигуры;" << endl;
    cout << "4. Вывести массу текущей фигуры;" << endl;
    cout << "5. Вывести метоположение фигуры;" << endl;
    cout << "6. Массы равны?;" << endl;
    cout << "7. Масса слева больше?;" << endl;
    cout << "8. Вывести полную информацию об объекте;" << endl;
    cout << "9. Вывести название объекта;" << endl;
    cout << "10. Вывести занимаемый в памяти размер объекта;" << endl;
    cout << "11. Вывести полную информацию обо всех фигурах;" << endl;
    cout << "12. Вывести суммарную площадь фигур;" << endl;
    cout << "13. Вывести суммарный периметр фигур;" << endl;
    cout << "14. Вывести цетр масс системы;" << endl;
    cout << "15. Вывести занимаемую память памяти;" << endl;
    cout << "16. Сортировать объекты по массе;" << endl;
    cout << "0. Завершить программу." << endl;
    cout << endl;
}

enum Commands {
    finishInput,
    createNewShape,
    printTheSquareOfTheCurrentShape,
    printThePerimeterOfTheCurrentShape,
    printTheMassOfTheCurrentShape,
    printThePositionOfTheCurrentShape,
    areTheMassesEqual,
    doesTheCurrentMassLess,
    printTheFullInformationAboutCurrentShape,
    printTheNameOfTheCurrentShape,
    printTheSizeOfTheCurrentShapeInMemory,
    printTheFullInformationAboutAllShapes,
    printTheTotalSquareOfTheShapes,
    printTheTotalPerimeterOfTheShapes,
    printTheMassCenterOfTheSystem,
    printTheSizeInMemory,
    sortShapesByMass,
};

enum Shape {
    circle,
    rectangle,
};

void processTheCommand() {
    vector<Figure *> figures;
    int figureNumber = 0;
    int command;
    int shape;
    
    while (true) {
        cout << "Введите команду: ";
        cin >> command;
        cout << endl;
        int index;
        switch (command) {
            case finishInput: {
                return;
            }
                
            case createNewShape: {
                cout << "Какую фигуру создать?" << endl;
                cout << "0. Круг" << endl;
                cout << "1. Прямоугольник" << endl;
                cout << "Фигура: ";
                cin >> shape;
                shape == circle ? figures.push_back(new Circle) : figures.push_back(new Rectangle);
                cout << endl;
                break;
            }
                
            case printTheSquareOfTheCurrentShape: {
                cout << "Площадь текущей фиугры: " << figures[figureNumber - 1]->square() << endl;
                cout << endl;
                break;
            }
                
            case printThePerimeterOfTheCurrentShape: {
                cout << "Периметр текущей фигуры: " << figures[figureNumber - 1]->perimeter() << endl;
                cout << endl;
                break;
            }
            
            case printTheMassOfTheCurrentShape: {
                cout << "Масса текущей фигуры: " << figures[figureNumber - 1]->mass() << endl;
                cout << endl;
                break;
            }
                
            case printThePositionOfTheCurrentShape: {
                cout << "Местоположение фигуры" << endl;
                cout << "x: " << figures[figureNumber - 1]->position().x << endl;
                cout << "y: " << figures[figureNumber - 1]->position().y << endl;
                cout << endl;
                break;
            }
                
            case areTheMassesEqual: {
                cout << "Введите индекс фигуры, с которой будем сравнивать: ";
                cin >> index;
                figures[figureNumber - 1] == figures[index] ? cout << "Массы равны" << endl : cout << "Массы не равны" << endl;
                cout << endl;
                break;
            }
                
            case doesTheCurrentMassLess: {
                cout << "Введите индекс фигуры, с которой будем сравнивать: ";
                cin >> index;
                figures[figureNumber - 1] < figures[index] ? cout << "Масса текущей фигуры меньше" << endl : cout << "Масса текущей фигуры больше" << endl;
                cout << endl;
                break;
            }
                
            case printTheFullInformationAboutCurrentShape: {
                figures[figureNumber - 1]->draw();
                break;
            }
                
            case printTheNameOfTheCurrentShape: {
                cout << "Название последней фигруы: " << figures[figureNumber - 1]->classname() << endl;
                cout << endl;
                break;
            }
                
            case printTheSizeOfTheCurrentShapeInMemory: {
                cout << "Размер занимаемой памяти последней фигруой: " << figures[figureNumber - 1]->size() << endl;
                cout << endl;
                break;
            }
                
            case printTheFullInformationAboutAllShapes: {
                for (Figure *& figure : figures) {
                    cout << figure << ": " << figure->classname() << endl;
                    figure->draw();
                    cout << endl;
                }
                break;
            }
                
            case printTheTotalSquareOfTheShapes: {
                int totalSquare = 0;
                for (Figure *& figure : figures) {
                    totalSquare += figure->square();
                }
                cout << "Общая площадь фигрур: " << totalSquare << endl;
                cout << endl;
                break;
            }
                
            case printTheTotalPerimeterOfTheShapes: {
                int totalPerimeter = 0;
                for (Figure *& figure : figures) {
                    totalPerimeter += figure->perimeter();
                }
                cout << "Общий периметр фигур: " << totalPerimeter << endl;
                cout << endl;
                break;
            }
                
            case printTheMassCenterOfTheSystem: {
                CVector2D massCenter;
                double massSum = 0;
                for (Figure *& figure : figures) {
                    massSum += figure->mass();
                    massCenter.x += figure->mass() * figure->position().x;
                    massCenter.y += figure->mass() * figure->position().y;
                }
                massCenter.x /= massSum;
                massCenter.y /= massSum;
                cout << "Центр масс: {" << massCenter.x << ", " << massCenter.y << "}" << endl;
                cout << endl;
                break;
            }
                
            case printTheSizeInMemory: {
                unsigned int size = 0;
                for (Figure *& figure : figures) {
                    size += figure->size();
                }
                cout << "Размер памяти, занимаемый фигурами: " << size << endl;
                cout << endl;
                break;
            }
                
            case sortShapesByMass: {
                sort(figures.begin(), figures.end(), [](Figure * a, Figure * b) {
                    return a->mass() < b->mass();
                });
                cout << "Фигуры отсортированы" << endl;
                cout << endl;
                break;
            }
        }
        if (command == 1) {
            figures[figureNumber]->initFromDialog();
            figureNumber++;
        }
    }
}

int main() {
    cout << "Команды: " << endl;
    printCommands();
    
    processTheCommand();
    
    cout << "Ввод фигур закончен!" << endl;
}
