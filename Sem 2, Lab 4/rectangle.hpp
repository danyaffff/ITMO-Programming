#ifndef rectangle_hpp
#define rectangle_hpp
#include "interfaces.hpp"

class Rectangle: public Figure {
    string name = "Прямоугольник";
    CVector2D center;
    double height;
    double width;
    double weight;
    
public:
    Rectangle();
    
    Rectangle(CVector2D &, double, double, double);
    
    Rectangle(const Rectangle &);
    
    ~Rectangle();
    
    void initFromDialog() override;
    
    double square() override;

    double perimeter() override;

    double mass() const override;

    CVector2D position() override;

    bool operator==(const IPhysObject &) const override;
    
    bool operator<(const IPhysObject &) const override;

    void draw() override;
    
    string classname() override;
    
    unsigned int size() override;
};

#endif
