// Лабораторная работа №5. Массивы.
//
// 1. Заполнить массив значениями согласно варианту. Результат в виде таблицы значений массива вывести на консоль.
//
// 2. Реализовать перемножение двух матриц 2х2 на основании данных варианта задания. Результат в виде таблицы значений 
// элементов результирующей матрицы вывести на консоль.

#include <stdio.h>

int main() {
    int array[] = {12, 13, 14, 15, 16, 17, 18, 19, 20};
    
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    int matrix1[2][2] = {{1, 1}, {0, 1}};
    int matrix2[2][2] = {{2, 0}, {3, 0}};
    int outputMatrix[2][2];
    
    outputMatrix[0][0] = matrix1[0][0] * matrix2[0][0] + matrix1[0][1] * matrix2[1][0];
    outputMatrix[0][1] = matrix1[0][0] * matrix2[0][1] + matrix1[0][1] * matrix2[1][1];
    outputMatrix[1][0] = matrix1[1][0] * matrix2[0][0] + matrix1[1][1] * matrix2[1][0];
    outputMatrix[1][1] = matrix1[1][0] * matrix2[0][1] + matrix1[1][1] * matrix2[1][1];
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", outputMatrix[i][j]);
        }
        printf("\n");
    }
}
