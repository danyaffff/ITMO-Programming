#ifndef template_h
#define template_h
#include "exceptions.hpp"

template <class T>
class Matrix {
    vector<vector<T>> matrix;
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
        cout << "Введите элементы матрицы" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cin >> matrix[i][j];
            }
        }
        cout << endl;
    }
    
    void printTheCertainElement() {
        int x;
        int y;
        
        cout << "Введите, какой элемент хотите вывести" << endl;
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw Exception("Выход за границы массива!");
        }
        cout << matrix[y][x] << endl;
        cout << endl;
    }
    
    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

#endif
