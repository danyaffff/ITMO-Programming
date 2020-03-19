#include "circle.hpp"

Circle::Circle(): radius(0), weight(0) {}

Circle::Circle(CVector2D & center, double radius, double weight): center(center), radius(radius), weight(weight) {}

Circle::Circle(const Circle & circle): center(circle.center), radius(circle.radius), weight(circle.weight) {}

Circle::~Circle() = default;

void Circle::initFromDialog(){
    cout << "Введите местоположение круга" << endl;
    cout << "x: ";
    cin >> center.x;
    cout << "y: ";
    cin >> center.y;
    
    cout << "Введите радиус: ";
    cin >> radius;
    
    cout << "Введите массу: ";
    cin >> weight;
    
    cout << endl;
}

double Circle::square() {
    return M_PI * pow(radius, 2);
}

double Circle::perimeter() {
    return 2 * M_PI * radius;
}

double Circle::mass() const {
    return weight;
}

CVector2D Circle::position() {
    return center;
}

bool Circle::operator==(const IPhysObject & circle) const {
    return mass() == circle.mass();
}

bool Circle::operator<(const IPhysObject & circle) const {
    return mass() < circle.mass();
}

void Circle::draw() {
    cout << "Площадь круга: " << square() << endl;
    
    cout << "Периметр круга: " << perimeter() << endl;

    cout << "Масса круга: " << mass() << endl;

    cout << "Координаты центра масс" << endl;
    cout << "x: " << position().x << endl;
    cout << "y: " << position().y << endl;
    cout << endl;
}

string Circle::classname() {
    return name;
}

unsigned int Circle::size() {
    return sizeof(*this);
}
