/* Основная идея:
 · У нас есть 27 маленьких кубиков (26 цветных, 20 движущихся).
 · Каждый кубик кодируется четырьмя параметрами: [i][j][k] — координата маленького кубика и .color[x] — направление, определяемое
   гранью. Другими словами, cube[i][j][k].color[0][1][2].color[4] — это маленкьий кубик с координатами [0][1][2] (средний кубик
   между красной и белой гранями), но так как кубик имеет 6 граней, мы должны выбрать направление. .color[4] говорит нам, что мы
   должны выбрать направление с цветом 4 (красный), то есть мы выбираем грань маленького кубика, которая смотрит туда же, куда и
   красная грань. */
#include <ctime>
#include <cstdlib>
#include <regex>
#include <random>
#include "cube.hpp"
 
#define CUBE_SIZE 20
#define TIMER 1

unsigned int colors[6] = {0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 0xFF8000};
 
GLfloat lightPosition[4] = {100, -30, 0, 1};  // Координаты лампы

int xRot = 25;
int yRot = 35;
int zRot = 0;  // Проекции угла поворота камеры

double translateZ = -60.0;  // Отдаление

Cube cube;  // Кубик

std::mt19937 randomNumber(static_cast<unsigned int>(time(nullptr)));
bool isRandom = false;  // Флаг самостоятельного вращения кубика

std::string inputFilename;  // Имя входного файла
std::string outputFilename;  // Имя выходного файла

double shift = 0;

bool isUp = true;
 
void display() {
    glPushMatrix();  // Сохраняем координаты
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Используем двухбуферное отображения (говорят, оно быстрее)
    glColor3f(0, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);  // Выставляем свет
    glTranslatef(0, 0, translateZ);  // Сдвигаем куб
    glRotatef(xRot, 1, 0, 0);  // Нужно для вращения
    glRotatef(yRot, 0, 1, 0);  // Нужно для вращения
    glTranslatef(CUBE_SIZE / -2, CUBE_SIZE / -2, CUBE_SIZE / -2);  // Сдвигаем куб
    cube.draw();
    glPopMatrix();  // Восстанавливаем координаты
    glutSwapBuffers();  // Меняем местами глубокий и цветной буфферы
}
 
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
    gluPerspective(60, aspect, 30, 70);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void init() {
    float reflection[4] = {0.6, 0.6, 0.6, 0};
    float diffuseLight[4] = {0.2, 0.2, 0.2, 1};
    float ambientLight[4] = {0.5, 0.5, 0.5, 1.0};
    
    glShadeModel(GL_SMOOTH);  // Отображение перехода цветов
    glMaterialfv(GL_FRONT, GL_SPECULAR, reflection);  // Настройка бликов
    glMateriali(GL_FRONT, GL_SHININESS, 128);  // Более плвное и правильное взаимодействие с освещением
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);  // Правильное отображение рассеянного света
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);  // Правильное взаимодействие с рассейнным светом
    glEnable(GL_LIGHT0);  // Включаем источник освещения
    glEnable(GL_COLOR_MATERIAL);  // Включаем взаимодействие света с объектом
    glColorMaterial(GL_FRONT, GL_AMBIENT);  // Еще одна настройка взаимодействия с рассеянным светом
    glEnable(GL_DEPTH_TEST);  // Это чтобы не видеть внутренности куба
    glEnable(GL_LIGHTING);  // Для более реалистичного взаимодействия
    cube.clear(CUBE_SIZE, colors);
}
 
void specialKeys(int key, int, int) {
    if (key == GLUT_KEY_DOWN) {
        xRot += 5;
        if (xRot >= 360) {
            xRot -= 360;
        }
        glutPostRedisplay();
    }
 
    if (key == GLUT_KEY_UP) {
        xRot -= 5;
        if (xRot < 0) {
            xRot += 360;
        }
        glutPostRedisplay();
    }
 
    if (key == GLUT_KEY_RIGHT) {
        yRot += 5;
        if (yRot >= 360) {
            yRot -= 360;
        }
        glutPostRedisplay();
    }
 
    if (key == GLUT_KEY_LEFT) {
        yRot -= 5;
        if (yRot < 0) {
            yRot += 360;
        }
        glutPostRedisplay();
    }
    
    if (key == GLUT_KEY_F1) {
        cube.clear(CUBE_SIZE, colors);
        glutPostRedisplay();
    }
    
    if (key == GLUT_KEY_F2) {
        cube.solve(colors);
        glutPostRedisplay();
    }
}

void input() {
    std::regex regular("[^\\.]+[^\\>]*\\.(ppm){1}$");
    std::cmatch inputFile;
    
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    
    if (!inputFilename.empty() && !std::regex_match(inputFilename.c_str(), inputFile, regular)) {
        throw Exception("Введено некорректное имя/формат входного файла!");
    }
    
    if (!inputFilename.empty()) {
        fin.open(inputFilename, std::ifstream::binary);
        cube.input(fin);
    }
    
    if (fin.is_open()) {
        fin.close();
    }
    glutPostRedisplay();
}

void output() {
    std::regex regular("[^\\.]+[^\\>]*\\.(ppm){1}$");
    std::cmatch outputFile;
    
    std::ofstream fout;
    fout.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    if (!outputFilename.empty() && !std::regex_match(outputFilename.c_str(), outputFile, regular)) {
        std::cerr << "Введено некорректное имя/формат выходного файла" << std::endl;
        return;
    }
    if (!outputFilename.empty()) {
        fout.open(outputFilename);
        cube.print(fout);
    }
    if (fout.is_open()) {
        fout.close();
    }
}
 
void keys(unsigned char key, int, int) {
    if (cube.current == -1 && key >= '0' && key < '6') {
        cube.rotate(key - '0', cube.isClockwise, true);
        display();
    } else if (key == 'z') {
        cube.isClockwise = 1 - cube.isClockwise;
    } else if (key == 'r' && !inputFilename.empty()) {
        input();
    } else if (key == 'w' && !outputFilename.empty()) {
        output();
    } else if (key == 'g') {
        cube.speed == normal ? cube.speed = fast : cube.speed = normal;
    }
}
 
void mouse(int key, int state, int, int) {
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isRandom = 1 - isRandom;
    }
    if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        cube.clearSolving();
        cube.isSolving = 1 - cube.isSolving;
    }
}
 
void timer(int) {
    glutTimerFunc(TIMER, timer, 0);
    if (isRandom) {
        if (cube.current == -1) {
            keys(randomNumber() % 6 + '0', 0, 0);
        } else {
            cube.rotate(cube.current, cube.isClockwise, true);
        }
    } else {
        if (cube.isSolving) {
            cube.solve(colors) ? cube.isSolving = false : cube.isSolving = true;
        } else if (cube.current != -1) {
            cube.rotate(cube.current, cube.isClockwise, cube.isHalf);
        }
    }
    
    if (isUp) {
        glRotatef(0.05, 1, 0, 0);
        shift += 0.08;
        if (shift >= 2) {
            isUp = false;
        }
    } else {
        glRotatef(-0.05, 1, 0, 0);
        shift -= 0.08;
        if (shift <= -2) {
            isUp = true;
        }
    }
    
    display();
}
 
int main(int argc, char * argv[]) {
    try {
        if (argc > 5 || argc % 2 == 0) {
            throw Exception("Введено неверное количество аргументов");
        }
        if (argc > 1) {
            for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-i") == 0) {
                    inputFilename = argv[i + 1];
                    std::cout << inputFilename << std::endl;
                }
                if (strcmp(argv[i], "-o") == 0) {
                    outputFilename = argv[i + 1];
                    std::cout << outputFilename << std::endl;
                }
            }
        }
        glutInit(&argc, argv);  // Инициализация
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Параметры отображения
        glutInitWindowSize(400, 400);  // Размер окна
        glutInitWindowPosition(0, 0);  // Позиция окна на экране
        glutCreateWindow("Шарик");  // Заголовок окна
        init();  // Инициализация сцены
        glutDisplayFunc(display);  // Функция для вывода модули на дисплей
        glutReshapeFunc(reshape);  // Функция для правильного отображения при изменении окна
        glutKeyboardFunc(keys);  // Обработка ASCII-клавиш
        glutMouseFunc(mouse);  // Обработка нажатий мышки
        glutTimerFunc(TIMER, timer, 0);  // Функция для работы задержки работы функций
        glutSpecialFunc(specialKeys);  // Обработка не ASCII-клавиш
        glutMainLoop();  // При изменении размера окна вызываем это для правильной настроки
    } catch (std::ifstream::failure &) {
        std::cerr << "Ошибка при открытии входного файла!" << std::endl;
        return 1;
    } catch (std::ofstream::failure &) {
        std::cout << "Ошибка при открытии выходного файла!" << std::endl;
        return 1;
    } catch (Exception & exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
}
