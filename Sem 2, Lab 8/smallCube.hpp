#ifndef smallCube_hpp
#define smallCube_hpp
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cstring>

class smallCube {
    unsigned char channel[3];
    
public:
    std::vector<unsigned int> color;
    
    double size = 0.0;
 
    smallCube();
    
    ~smallCube();
 
    // Поворот на плоскости X0Y
    void rotateZ();
 
    // Поворот на плоскости X0Z
    void rotateY();
 
    // Поворот на плоскости Y0Z
    void rotateX();
 
    // Установка цвета
    void setColor(int, int);
 
    // Разибиение цвета на 3 составляющие: Red (0xFF0000), Green (0x00FF00), Blue (0x0000FF)
    unsigned char * at(int);
 
    // Рисование кубика
    void draw();
 
    // Рисование куба со смещением (x, y, z)
    void draw(double, double, double);
};

#endif
