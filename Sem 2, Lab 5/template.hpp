#ifndef template_h
#define template_h
#include "exceptions.hpp"

template <class T>
class Matrix {
    std::vector<std::vector<T>> matrix;
    int width;
    int height;
    
public:
    Matrix(int width, int height): width(width), height(height) {
        matrix.resize(height);
        for (int i = 0; i < height; i++) {
            matrix[i].resize(width);
        }
    }
    
    ~Matrix() {
        for (int i = 0; i < height; i++) {
            matrix[i].clear();
        }
        matrix.clear();
    }
    
    void input() {
        std::cout << "Введите элементы матрицы" << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cin >> matrix[i][j];
            }
        }
        std::cout << std::endl;
    }
    
    void printTheCertainElement() {
        int x;
        int y;
        
        std::cout << "Введите, какой элемент хотите вывести" << std::endl;
        std::cout << "x: ";
        std::cin >> x;
        std::cout << "y: ";
        std::cin >> y;
        if (x < 1 || x > width || y < 1 || y > height) {
            throw Exception("Выход за границы массива!");
        }
        std::cout << "Элемент: " << matrix[y - 1][x - 1] << std::endl;
        std::cout << std::endl;
    }
    
    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif
