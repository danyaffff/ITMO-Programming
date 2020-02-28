// Лабораторная работа №2. Рассчет значения функции в данной точке.
// Разработайте программу, рассчитывающую значения двух указанных функций. Входные значения аргументов запросите с консоли. 
// Полученные значения функций выведите на консоль.

#include <stdio.h>
#include <stdio.h>
#include <math.h>

int main() {
    const double pi = 3.1415926535897932;
    double z1, z2, alpha;
    
    printf("Введите α\n");
    scanf("%lf", &alpha);
    
    z1 = 2 * pow(sin(3 * pi - 2 * alpha), 2) * pow(cos(5 * pi + 2 * alpha), 2);
    z2 = (double)1/4 - (double)1/4 * sin((double)5/2 * pi - 8 * alpha);
    
    printf("%lf\n%lf", z1, z2);
}
