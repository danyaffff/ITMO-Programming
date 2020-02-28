/* Лабораторная работа №6. Указатели и динамическая память */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, n = 5;
    char Arr[n], *Array, *ptr; ptr = Arr;
    Arr[0] = 'H';
    Arr[1] = 'e';
    Arr[2] = 'l';
    Arr[3] = 'l';
    Arr[4] = 'o';
    for (i = 0; i < n; i++) {
        printf("Arr[%d] %c\n", i, *(ptr + i));
    }
    printf("\n");
    Array = (char*)malloc(n * sizeof(char));
    Array[0] = 'H';
    Array[1] = 'e';
    Array[2] = 'l';
    Array[3] = 'l';
    Array[4] = 'o';
    for (i = 0; i < n; i++) {
        printf("Array[%d] %c\n", i, Array[i]);
    }
    free(Array);
}
