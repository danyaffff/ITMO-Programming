#include "smallCube.hpp"

smallCube::smallCube() {
    color.resize(6);
}

smallCube::~smallCube() {
    color.clear();
}

void smallCube::rotateZ() {
    unsigned int tmp = color[5];
    color[5] = color[3];
    color[3] = color[4];
    color[4] = color[2];
    color[2] = tmp;
}

void smallCube::rotateY() {
    unsigned int tmp = color[2];
    color[2] = color[1];
    color[1] = color[3];
    color[3] = color[0];
    color[0] = tmp;
}

void smallCube::rotateX() {
    unsigned int tmp = color[0];
    color[0] = color[4];
    color[4] = color[1];
    color[1] = color[5];
    color[5] = tmp;
}

void smallCube::setColor(int i, int newColor) {
    color[i] = newColor;
}

unsigned char * smallCube::at(int i) {
    channel[0] = color[i] >> 16;
    channel[1] = color[i] >> 8;
    channel[2] = color[i];
    return channel;
}

void smallCube::draw() {
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

void smallCube::draw(double x, double y, double z) {
    glPushMatrix();  // Сохраняем координаты
    glTranslated(x, y, z);  // Двигаем
    draw();  // Рисуем
    glPopMatrix();  // Возвращаем координаты
}
