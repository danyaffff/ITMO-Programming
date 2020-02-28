/* Лабораторная работа №8. Работа со строками. */

#include <stdio.h>
#include <string.h>

int main() {
    char Line1[50], Line2[50];
    int N;
    
    printf("Введите первую строку\n");
    scanf("%s", Line1);
    printf("Введите вторую строку\n");
    scanf("%s", Line2);
    printf("Сложение 1 и 2 строк \n");
    strcat(Line1, Line2);
    printf("%s\n", Line1);
    printf("Введите, сколько символов будут сравниваться: ");
    scanf("%d", &N);
    printf("Сравниваем первые %d символов: %d", N, strncmp(Line1, Line2, N));
    printf("Длина 1 строки равна %lu\n", strlen(Line1));
    printf("Место первого вхожнения символа из 2 строки в 1 строке: %s\n", strpbrk(Line1, Line2));
    printf("Длина сегмента без вхождений эелементов 2 строки: %lu", strcspn(Line1, Line2));
}
