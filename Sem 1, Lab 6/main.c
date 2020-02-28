// Лабораторная работа №6. Указатели и динамическая память.
// 
// 1. Создать массив с использованием указателя. Заполнить созданный массив значениями согласно варианту. Для обращения к
// элементам массива при заполнении использовать индексы массива. Результат в виде таблицы значений массива вывести на
// консоль. Для обращения к элементам массива при выводе информации использовать указатели.
//
// 2. Создать массив в динамической памяти. Заполнить созданный массив значениями согласно варианту. Результат в виде таблицы
// значений массива вывести на консоль. После завершения работы с массивом освободить динамическую память.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int arraySize = 5;
    char array[arraySize];
    char *ptr = array;
    char *dynamicArray = (char*)malloc(arraySize * sizeof(char));
    
    array[0] = 'H';
    array[1] = 'e';
    array[2] = 'l';
    array[3] = 'l';
    array[4] = 'o';
    
    for (int i = 0; i < arraySize; i++) {
        printf("array[%d] = %c\n", i, *(ptr + i));
    }
    printf("\n");
    
    dynamicArray[0] = 'H';
    dynamicArray[1] = 'e';
    dynamicArray[2] = 'l';
    dynamicArray[3] = 'l';
    dynamicArray[4] = 'o';
    
    for (int i = 0; i < arraySize; i++) {
        printf("array[%d] = %c\n", i, dynamicArray[i]);
    }
    free(dynamicArray);
}
