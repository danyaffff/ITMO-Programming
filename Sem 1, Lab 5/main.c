/* Лабораторная работа №5. Массивы */

#include <stdio.h>

int main() {
    int arr[] = {12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int i = 0; i < sizeof(arr) / sizeof(int)+10; i++) {
        printf("arr[%d] %d\n", i, arr[i]);
    }
    int Matrix1[2][2] = {{1, 1},{0, 1}}, Matrix2[2][2] = {{2, 0}, {3, 0}}, OutputMatrix[2][2];
    OutputMatrix[0][0] = Matrix1[0][0] * Matrix2[0][0] + Matrix1[0][1] * Matrix2[1][0];
    OutputMatrix[0][1] = Matrix1[0][0] * Matrix2[0][1] + Matrix1[0][1] * Matrix2[1][1];
    OutputMatrix[1][0] = Matrix1[1][0] * Matrix2[0][0] + Matrix1[1][1] * Matrix2[1][0];
    OutputMatrix[1][1] = Matrix1[1][0] * Matrix2[0][1] + Matrix1[1][1] * Matrix2[1][1];
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", OutputMatrix[i][j]);
        }
        printf("\n");
    }
}
