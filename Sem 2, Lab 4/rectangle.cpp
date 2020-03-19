#include "rectangle.hpp"

Rectangle::Rectangle(): height(0), width(0), weight(0) {}

Rectangle::Rectangle(CVector2D & center, double height, double width, double weight): center(center), height(height), width(width), weight(weight) {}

Rectangle::Rectangle(const Rectangle & rectangle): center(rectangle.center), height(rectangle.height), width(rectangle.width), weight(rectangle.weight) {}

Rectangle::~Rectangle() = default;

void Rectangle::initFromDialog() {
    cout << "Введите местоположение центра прямоугольника" << endl;
    cout << "x: ";
    cin >> center.x;
    cout << "y: ";
    cin >> center.y;
    
    cout << "Введите ширину прямоугольника: ";
    cin >> width;
    
    cout << "Введите высоту прямоугольника: ";
    cin >> height;
    
    cout << "Введите массу прямоугольника: ";
    cin >> weight;
    cout << endl;
}

double Rectangle::square() {
    return height * width;
}

double Rectangle::perimeter() {
    return 2 * (height + width);
}

double Rectangle::mass() const {
    return weight;
}

CVector2D Rectangle::position() {
    return center;
}

bool Rectangle::operator==(const IPhysObject & rectangle) const {
    return mass() == rectangle.mass();
}

bool Rectangle::operator<(const IPhysObject & rectangle) const {
    return mass() < rectangle.mass();
}

void Rectangle::draw() {
    cout << "Площадь прямоугольника: " << square() << endl;
    
    cout << "Периметр прямоугольника: " << perimeter() << endl;

    cout << "Масса прямоугольника: " << mass() << endl;

    cout << "Координаты центра масс" << endl;
    cout << "x: " << position().x << endl;
    cout << "y: " << position().y << endl;
    cout << endl;
}

string Rectangle::classname() {
    return name;
}

unsigned int Rectangle::size() {
    return sizeof(*this);
}
