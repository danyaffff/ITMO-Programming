#ifndef circle_hpp
#define circle_hpp
#define _USE_MATH_DEFINE
#include "interfaces.hpp"

class Circle: public Figure {
    string name = "Круг";
    double radius;
    double weight;
    CVector2D center;

public:
    Circle();
    
    Circle(CVector2D &, double, double);
    
    Circle(const Circle &);
    
    ~Circle();
    
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
