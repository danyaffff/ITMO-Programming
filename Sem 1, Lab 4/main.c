/* Лабораторная работа №3. Логические операторы. */
#include <stdio.h>

int main() {
    int min, max, num, num2, bit = 0; min = 21; max = 45;
    printf("Введите десятиеричное число\n");
    scanf("%d", &num);
    printf("%s\n", num <= max && num >= min ? "Число входит в диапазон" : "Число не входит в диапазон");
    printf("Введите число в десятичном формате\n");
    scanf("%d", &num2);
    printf("%d\n", 1 & (num2 >> 14));
    for (int i = 0; i <= 14; i++) {
        bit = 0;
        bit = num2 % 2;
        num2 /= 2;
    }
    printf("%d", bit);
}
