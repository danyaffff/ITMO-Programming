// Лабораторная работа №7. Типы данных определяемые пользователем.
//
// Использовать перечислимый тип для хранения названий дней недели (месяцев, названий организационно-правовых форм предприятий
// и т.п.). Вывести на консоль значение целого числа, соответствующее указанному в варианте задания элементу перечисления.
//
// Типы автомобилей (легковой, грузовой, автобус, гоночный и т.п.). Отобразить: автобус.
//
// Разработать структуру, описывающую координаты и другие требуемые параметры простейшей геометрической фигуры (отрезок прямой,
// прямоугольник, квадрат, треугольник, окружность) с расчётом одного из её параметров (периметра, площади, длины окружности и
// т.п.). Исходные данные для расчёта указать в тексте программы. Результат расчёта вывести на консоль.
//
// Квадрат.
//
// Разработать битовое поле, описывающее состояния элементов прибора. Ввести с консоли число в 16-ричной системе счисления, 
// преобразовать его в битовое поле за счёт использования объединения. Вывести на консоль состояния элементов прибора, 
// соответствующие состоянию битов во введённом числе.
//
// Лазерный принтер. Элементы: готов вкл/выкл, мало тонера вкл/выкл, повреждён барабан вкл/выкл, нет бумаги вкл/выкл.

#include <stdio.h>
#include <math.h>

enum TypesOfCars {
    passenger,
    truck,
    bus,
    racing
};

typedef struct point {
    double x;
    double y;
} point;

typedef struct square {
    double square;
    
    point a;
    point b;
    point c;
    point d;
} square;

union Device {
    unsigned short printer;
    
    struct Statment {
        unsigned short done: 1;
        unsigned short lowToner: 1;
        unsigned short drumDamaged: 1;
        unsigned short noPaper: 1;
    } Statement;
} Device;

int main() {
    printf("%d\n\n", bus);
    
    square square;
    square.a.x = 0;
    square.a.y = 0;
    square.b.x = 0;
    square.b.y = 2;
    square.c.x = 2;
    square.c.y = 2;
    square.d.x = 2;
    square.d.y = 0;
    square.square = ((sqrt(pow(square.a.x - square.c.x, 2) + pow(square.a.y - square.c.y, 2))) * (sqrt(pow(square.b.x - square.d.x, 2) + pow(square.b.y - square.d.y, 2)))) / 2;
    printf("Площадь %lf\n\n", square.square);
    
    scanf("%hu", &Device.printer);
    Device.Statement.done ? printf("Yes\n") : printf("No\n");
    Device.Statement.lowToner ? printf("Yes\n") : printf("No\n");
    Device.Statement.drumDamaged ? printf("Yes\n") : printf("No\n");
    Device.Statement.noPaper ? printf("Yes\n") : printf("No\n");
}
