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
 
    smallCube() {
        color.resize(6);
    }
    
    ~smallCube() {
        color.clear();
    }
 
    void rotateZ() {  // Поворот на плоскости X0Y
        unsigned int tmp = color[5];
        color[5] = color[3];
        color[3] = color[4];
        color[4] = color[2];
        color[2] = tmp;
    }
 
    void rotateY() {  // поворот на плоскости X0Z
        unsigned int tmp = color[2];
        color[2] = color[1];
        color[1] = color[3];
        color[3] = color[0];
        color[0] = tmp;
    }
 
    void rotateX() {  // поворот на плоскости Y0Z
        unsigned int tmp = color[0];
        color[0] = color[4];
        color[4] = color[1];
        color[1] = color[5];
        color[5] = tmp;
    }
 
    void setColor(int i, int newColor) {  // Установка цвета
        color[i] = newColor;
    }
 
    // Разибиение цвета на 3 составляющие: Red (0xFF0000), Green (0x00FF00), Blue (0x0000FF)
    unsigned char * at(int i) {
        channel[0] = color[i] >> 16;
        channel[1] = color[i] >> 8;
        channel[2] = color[i];
        return channel;
    }
 
    void draw() {  // Рисование кубика
        glPushMatrix();  // Сохраняем координаты
        glBegin(GL_QUADS);  // Рисуем четырехугольные полигоны
 
        // Верхний полигон
        glColor3ubv(at(0));  // Цвет
        glNormal3f(0, 0, 1);  // Нормаль
        glVertex3f(size, size, size);
        glVertex3f(0, size, size);
        glVertex3f(0, 0, size);
        glVertex3f(size, 0, size);
 
        // Нижний полигон
        glColor3ubv(at(1));
        glNormal3f(0, 0, -1);
        glVertex3f(size, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, size, 0);
        glVertex3f(size, size, 0);
 
        // Передний полигон
        glColor3ubv(at(2));
        glNormal3f(0, -1, 0);
        glVertex3f(size, 0, size);
        glVertex3f(0, 0, size);
        glVertex3f(0, 0, 0);
        glVertex3f(size, 0, 0);
 
        // Задний полигон
        glColor3ubv(at(3));
        glNormal3f(0, 1, 0);
        glVertex3f(size, size, 0);
        glVertex3f(0, size, 0);
        glVertex3f(0, size, size);
        glVertex3f(size, size, size);
 
        // Левый полигон
        glColor3ubv(at(4));
        glNormal3f(-1, 0, 0);
        glVertex3f(0, size, size);
        glVertex3f(0, size, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, size);
 
        // Правый полигон
        glColor3ubv(at(5));
        glNormal3f(1, 0, 0);
        glVertex3f(size, size, 0);
        glVertex3f(size, size, size);
        glVertex3f(size, 0, size);
        glVertex3f(size, 0, 0);
 
        glEnd();  // Конец рисования четырехугольных полигонов
        glPopMatrix();  // Возвращаем старые координаты
    }
 
    void draw(double x, double y, double z) {  // Рисование куба со смещением (x, y, z)
        glPushMatrix();  // Сохраняем координаты
        glTranslated(x, y, z);  // Двигаем
        draw();  // Рисуем
        glPopMatrix();  // Возвращаем координаты
    }
};

#endif
