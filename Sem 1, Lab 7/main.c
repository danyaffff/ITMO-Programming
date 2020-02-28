/* Лабораторная работа №7. Типы данных определяемые пользователем. */

#include <stdio.h>
#include <math.h>

enum TypesOfCars {
    Passenger,
    Truck,
    Bus,
    Racing
};

typedef struct point {
    double x;
    double y;
} point;

typedef struct Square {
    point a;
    point b;
    point c;
    point d;
    
    double Square;
} Square;

union Device {
    unsigned short Printer;
    struct Statment {
        unsigned short Done: 1;
        unsigned short LowToner: 1;
        unsigned short DrumDamaged: 1;
        unsigned short NoPaper: 1;
    } Statement;
} Device;

int main() {
    printf("%d\n\n", Bus);
    
    Square Sq;
    Sq.a.x = 0;
    Sq.a.y = 0;
    Sq.b.x = 0;
    Sq.b.y = 2;
    Sq.c.x = 2;
    Sq.c.y = 2;
    Sq.d.x = 2;
    Sq.d.y = 0;
    Sq.Square = ((sqrt(pow(Sq.a.x - Sq.c.x, 2) + pow(Sq.a.y - Sq.c.y, 2))) * (sqrt(pow(Sq.b.x - Sq.d.x, 2) + pow(Sq.b.y - Sq.d.y, 2)))) / 2;
    printf("Площадь %f\n", Sq.Square);
    
    scanf("%hu", &Device.Printer);
    Device.Statement.Done ? printf("Yes\n") : printf("No\n");
    Device.Statement.LowToner ? printf("Yes\n") : printf("No\n");
    Device.Statement.DrumDamaged ? printf("Yes\n") : printf("No\n");
    Device.Statement.NoPaper ? printf("Yes\n") : printf("No\n");
}
