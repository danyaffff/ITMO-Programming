#ifndef cube_hpp
#define cube_hpp
#include <fstream>
#include "smallCube.hpp"
#include "exception.hpp"

enum Speed {
    normal = 5,
    fast = 90,
};
 
class Cube {
    std::vector<std::vector<std::vector<smallCube>>> cube;
    std::vector<std::vector<smallCube>> temp;
    
    std::vector<int> angle;
    
    double size;
    
    std::vector<unsigned int> color;
    
    std::vector<std::vector<std::vector<bool>>> isRests;
    
    bool isAlreadySolved = true;
    
    bool sweayc;
    bool sweawc;
    bool swcawc;
    bool ssl;
    bool syc;
    bool sryc;
    bool scayc;
    bool stl;
    bool lastStep;
    
    bool isBlueSolved;
    bool isGreenSolved;
    bool isRedSolved;
    bool isOrangeSolved;
    
    short int isRightHandAlgorithm;
    
    bool isSolveRight;
    bool isSolveLeft;
    bool isWrongEdge;
    bool isSolveCross;
    bool isSolveRightCross;
    bool isSolveCrossLine;
    bool isSolveCorners;
    bool isSolveThirdLayer;
    
    short int phase;
    
    short int front;
    short int right;
    short int left;
    
    std::vector<std::string> solution;
 
public:
    bool isSolving = false;
    bool isHalf = true;
    bool isClockwise = true;
    
    int current;
    
    Speed speed = normal;
 
    Cube() {
        angle.resize(6);
        color.resize(6);
        isRests.resize(3);
        cube.resize(3);
        temp.resize(3);
        for (int i = 0; i < 3; i++) {
            isRests[i].resize(3);
            cube[i].resize(3);
            temp[i].resize(3);
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                isRests[i][j].resize(3, true);
                cube[i][j].resize(3);
            }
        }
    }
    
    ~Cube() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                isRests[i][j].clear();
                cube[i][j].clear();
            }
        }
        for (int i = 0; i < 3; i++) {
            isRests[i].clear();
            cube[i].clear();
            temp.clear();
        }
        angle.clear();
        color.clear();
        isRests.clear();
        cube.clear();
        temp.clear();
        solution.clear();
    }
 
    void clear(double newSize, unsigned int * colors) {
        size = newSize;
        current = -1;
        
        for (int i = 0; i < 6; i++) {
            color[i] = colors[i];
        }
 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cube[i][j][2].setColor(0, colors[0]);
                cube[i][j][0].setColor(1, colors[1]);
                cube[j][0][i].setColor(2, colors[2]);
                cube[j][2][i].setColor(3, colors[3]);
                cube[0][j][i].setColor(4, colors[4]);
                cube[2][j][i].setColor(5, colors[5]);
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k].size = newSize / 3.0 * 0.95;
                }
            }
        }
    }
 
    void draw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    isRests[i][j][k] = true;
                }
            }
        }
        if (current != -1) {
            glPushMatrix();
            if (current == 0 || current == 1) {
                int k = (current & 1) * 2;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        isRests[i][j][k] = false;
                    }
                }
                glTranslated(size / 2, size / 2, 0);
                glRotatef(angle[current], 0, 0, 1);
                glTranslated(-size / 2, -size / 2, 0);
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        cube[i][j][k].draw(size / 3 * i + 0.1, size / 3 * j + 0.1, size / 3 * k + 0.1);
                    }
                }
            } else if (current == 2 || current == 3) {
                int j = (current & 1) * 2;
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        isRests[i][j][k] = false;
                    }
                }
 
                glTranslated(size / 2, 0, size / 2);
                glRotatef(angle[current], 0, 1, 0);
                glTranslated(-size / 2, 0, -size / 2);
                
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        cube[i][j][k].draw(size / 3 * i + 0.1, size / 3 * j + 0.1, size / 3 * k + 0.1);
                    }
                }
            } else if (current == 4 || current == 5) {
                int i = (current & 1) * 2;
                
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        isRests[i][j][k] = false;
                    }
                }
 
                glTranslated(0, size / 2, size / 2);
                glRotatef(angle[current], 1, 0, 0);
                glTranslated(0, -size / 2, -size / 2);
                
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        cube[i][j][k].draw(size / 3 * i + 0.1, size / 3 * j + 0.1, size / 3 * k + 0.1);
                    }
                }
            }
            glPopMatrix();
        }
 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (isRests[i][j][k]) {
                        cube[i][j][k].draw(size / 3 * i + 0.1, size / 3 * j + 0.1, size / 3 * k + 0.1);
                    }
                }
            }
        }
    }
    
    void rotateVector(int face, int sign) {
        if (sign == -1) {
            sign = 3;
        } else if (sign == 0) {
            sign = 2;
        }
        
        while (sign--) {
            if (face == 0 || face == 1) {
                int k = (face & 1) * 2;
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        temp[j][2 - i] = cube[i][j][k];
                    }
                }
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        temp[i][j].rotateZ();
                        cube[i][j][k] = temp[i][j];
                    }
                }
            } else if (face == 2 || face == 3) {
                int j = (face & 1) * 2;
                
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        temp[k][2 - i] = cube[i][j][k];
                    }
                }
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        temp[i][k].rotateX();
                        cube[i][j][k] = temp[i][k];
                    }
                }
            } else if (face == 4 || face == 5) {
                int i = (face & 1) * 2;
                
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp[k][2 - j] = cube[i][j][k];
                    }
                }
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp[j][k].rotateY();
                        cube[i][j][k] = temp[j][k];
                    }
                }
            }
        }
    }
 
    void rotate(int face, bool isClockwise, bool isHalf) {
        this->isHalf = isHalf;
        this->isClockwise = isClockwise;
        if (current == -1 || current == face) {
            isClockwise ? (face == 0 || face == 2 || face == 4) ? angle[face] += speed : angle[face] -= speed : (face == 0 || face == 2 || face == 4) ? angle[face] -= speed : angle[face] += speed;
            
            if (angle[face] % (this->isHalf ? 90 : 180) != 0) {
                current = face;
            } else if (isHalf) {
                if (isSolving) {
                    switch (face) {
                        case 0: {
                            isClockwise ? solution.push_back("Y") : solution.push_back("Y'");
                            break;
                        }
                        
                        case 1: {
                            isClockwise ? solution.push_back("W") : solution.push_back("W'");
                            break;
                        }
                            
                        case 2: {
                            isClockwise ? solution.push_back("B") : solution.push_back("B'");
                            break;
                        }
                            
                        case 3: {
                            isClockwise ? solution.push_back("G") : solution.push_back("G'");
                            break;
                        }
                            
                        case 4: {
                            isClockwise ? solution.push_back("R") : solution.push_back("R'");
                            break;
                        }
                            
                        case 5: {
                            isClockwise ? solution.push_back("O") : solution.push_back("O'");
                            break;
                        }
                    }
                }
                if (((angle[face] < 0) ^ (current == 2 || current == 3))) {
                    rotateVector(face, 1);
                } else {
                    rotateVector(face, -1);
                }
                angle[face] = 0;
                current = -1;
            } else {
                if (isSolving) {
                    switch (face) {
                        case 0: {
                            solution.push_back("Y2");
                            break;
                        }
                        
                        case 1: {
                            solution.push_back("W2");
                            break;
                        }
                            
                        case 2: {
                            solution.push_back("B2");
                            break;
                        }
                            
                        case 3: {
                            solution.push_back("G2");
                            break;
                        }
                            
                        case 4: {
                            solution.push_back("R2");
                            break;
                        }
                            
                        case 5: {
                            solution.push_back("O2");
                            break;
                        }
                    }
                }
                this->isHalf = true;
                rotateVector(face, 0);
                angle[face] = 0;
                current = -1;
            }
        }
        if (solution.size() > 200) {
            std::cerr << "Куб не удается собрать! Попытайтесь заново!" << std::endl;
            solution.clear();
            clearSolving();
            if (current == -1) {
                isSolving = false;
            }
        }
    }
    
    void clearSolving() {
        sweayc = true;
        sweawc = false;
        swcawc = false;
        ssl = false;
        syc = false;
        stl = false;
        scayc = false;
        
        isBlueSolved = false;
        isGreenSolved = false;
        isRedSolved = false;
        isOrangeSolved = false;
        
        isRightHandAlgorithm = 0;
        
        isSolveRight = false;
        isSolveLeft = false;
        isWrongEdge = false;
        isSolveCross = false;
        isSolveRightCross = false;
        isSolveCrossLine = false;
        isSolveCorners = false;
        isSolveThirdLayer = false;
        
        phase = 0;
        
        front = -1;
        right = -1;
        left = -1;
        
        solution.clear();
    }
    
    bool isSolved(unsigned int * colors) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (cube[i][j][2].color[0] != colors[0] || cube[i][j][0].color[1] != colors[1] || cube[j][0][i].color[2] != colors[2] || cube[j][2][i].color[3] != colors[3] || cube[0][j][i].color[4] != colors[4] || cube[2][j][i].color[5] != colors[5]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void solveWhiteEdgesAroundYellowCenter(unsigned int * colors) {
        if (cube[0][0][1].color[2] == colors[0]) {
            if (cube[0][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(4, true, true);
            return;
        } else if (cube[2][0][1].color[2] == colors[0]) {
            if (cube[2][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(5, false, true);
            return;
        } else if (cube[1][0][0].color[2] == colors[0]) {
            rotate(2, true, true);
            return;
        } else if (cube[1][0][2].color[2] == colors[0]) {
            if (cube[1][0][0].color[1] == colors[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(2, true, true);
            return;
        }
        
        if (cube[2][2][1].color[3] == colors[0]) {
            if (cube[2][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(5, true, true);
            return;
        } else if (cube[2][0][1].color[3] == colors[0]) {
            if (cube[0][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(4, false, true);
            return;
        } else if (cube[1][2][0].color[3] == colors[0]) {
            rotate(3, true, true);
            return;
        } else if (cube[1][2][2].color[3] == colors[0]) {
            if (cube[1][2][0].color[1] == colors[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(3, true, true);
            return;
        }

        if (cube[0][2][1].color[4] == colors[0]) {
            if (cube[1][2][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(3, true, true);
            return;
        } else if (cube[0][0][1].color[4] == colors[0]) {
            if (cube[1][0][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(2, false, true);
            return;
        } else if (cube[0][1][0].color[4] == colors[0]) {
            rotate(4, true, true);
            return;
        } else if (cube[0][1][2].color[4] == colors[0]) {
            if (cube[0][1][0].color[1] == colors[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(4, true, true);
            return;
        }

        if (cube[2][0][1].color[5] == colors[0]) {
            if (cube[1][0][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(2, true, true);
            return;
        } else if (cube[2][2][1].color[5] == colors[0]) {
            if (cube[1][2][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(3, false, true);
            return;
        } else if (cube[2][1][0].color[5] == colors[0]) {
            rotate(5, true, true);
            return;
        } else if (cube[2][1][2].color[5] == colors[0]) {
            if (cube[2][1][0].color[1] == colors[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(5, true, true);
            return;
        }

        if (cube[2][1][2].color[0] == colors[0]) {
            if (cube[2][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(5, false, false);
            return;
        } else if (cube[0][1][2].color[0] == colors[0]) {
            if (cube[0][1][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(4, false, false);
            return;;
        } else if (cube[1][2][2].color[0] == colors[0]) {
            if (cube[1][2][0].color[1] == color[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(3, false, false);
            return;
        } else if (cube[1][0][2].color[0] == colors[0]) {
            if (cube[1][0][0].color[1] == colors[0]) {
                rotate(0, true, true);
                return;
            }
            rotate(2, false, true);
            return;
        }
    }
    
    void solveWhiteEdgesAroundWhiteCenter(unsigned int * colors) {
        if (!isBlueSolved) {
            if (cube[1][0][0].color[1] == colors[0] && cube[1][0][0].color[2] == colors[2]) {
                rotate(2, true, false);
                if (cube[1][0][2].color[0] == colors[0]) {
                    isBlueSolved = true;
                }
                return;
            } else {
                rotate(0, false, true);
                return;
            }
        } else if (!isGreenSolved) {
            if (cube[1][2][0].color[1] == colors[0] && cube[1][2][0].color[3] == colors[3]) {
                rotate(3, false, false);
                if (cube[1][2][2].color[0] == colors[0]) {
                    isGreenSolved = true;
                }
                return;
            } else {
                rotate(0, false, true);
                return;
            }
        } else if (!isRedSolved) {
            if (cube[0][1][0].color[1] == colors[0] && cube[0][1][0].color[4] == colors[4]) {
                rotate(4, false, false);
                if (cube[0][1][2].color[0] == colors[0]) {
                    isRedSolved = true;
                }
                return;
            } else {
                rotate(0, false, true);
                return;
            }
        } else if (!isOrangeSolved) {
            if (cube[2][1][0].color[1] == colors[0] && cube[2][1][0].color[5] == colors[5]) {
                rotate(5, false, false);
                if (cube[2][1][2].color[0] == colors[0]) {
                    isOrangeSolved = true;
                }
                return;
            } else {
                rotate(0, false, true);
                return;
            }
        }
    }
    
    void doRightHandAlgorithm() {
        switch (phase) {
            case 1: {
                rotate(right, true, true);
                return;
            }
                
            case 2: {
                rotate(0, true, true);
                return;
            }
                
            case 3: {
                rotate(right, false, true);
                return;
            }
                
            case 4: {
                rotate(0, false, true);
                return;
            }
        }
        isRightHandAlgorithm--;
        if (isRightHandAlgorithm == 0) {
            phase = 0;
            right = -1;
        }
    }
    
    void solveWhiteCornersAroundWhiteCenter(unsigned int * colors) {
        if (isRightHandAlgorithm > 0) {
            if (current == -1) {
                phase++;
            }
            doRightHandAlgorithm();
            return;
        }
        if ((cube[2][0][0].color[1] == colors[0] && cube[2][0][0].color[5] == colors[2] && cube[2][0][0].color[2] == colors[5]) || (cube[2][0][0].color[2] == colors[0] && cube[2][0][0].color[1] == colors[2] && cube[2][0][0].color[5] == colors[5]) || (cube[2][0][0].color[5] == colors[0] && cube[2][0][0].color[1] == colors[5] && cube[2][0][0].color[2] == colors[2])) {
            right = 2;
            if (cube[2][0][0].color[1] == colors[0]) {
                isRightHandAlgorithm = 3;
            } else if (cube[2][0][0].color[2] == colors[0]) {
                isRightHandAlgorithm = 1;
            } else {
                isRightHandAlgorithm = 5;
            }
            return;
        } else if ((cube[0][0][0].color[1] == colors[0] && cube[0][0][0].color[2] == colors[4] && cube[0][0][0].color[4] == colors[2]) || (cube[0][0][0].color[2] == colors[0] && cube[0][0][0].color[1] == colors[2] && cube[0][0][0].color[4] == colors[4]) || (cube[0][0][0].color[4] == colors[0] && cube[0][0][0].color[1] == colors[4] && cube[0][0][0].color[2] == colors[2])) {
            right = 4;
            if (cube[0][0][0].color[1] == colors[0]) {
                isRightHandAlgorithm = 3;
            } else if (cube[0][0][0].color[2] == colors[0]) {
                isRightHandAlgorithm = 5;
            } else {
                isRightHandAlgorithm = 1;
            }
            return;
        } else if ((cube[0][2][0].color[1] == colors[0] && cube[0][2][0].color[4] == colors[3] && cube[0][2][0].color[3] == colors[4]) || (cube[0][2][0].color[4] == colors[0] && cube[0][2][0].color[1] == colors[4] && cube[0][2][0].color[3] == colors[3]) || (cube[0][2][0].color[3] == colors[0] && cube[0][2][0].color[1] == colors[3] && cube[0][2][0].color[4] == colors[4])) {
            right = 3;
            if (cube[0][2][0].color[1] == colors[0]) {
                isRightHandAlgorithm = 3;
            } else if (cube[0][2][0].color[4] == colors[0]) {
                isRightHandAlgorithm = 5;
            } else {
                isRightHandAlgorithm = 1;
            }
            return;
        } else if ((cube[2][2][0].color[1] == colors[0] && cube[2][2][0].color[3] == colors[5] && cube[2][2][0].color[5] == colors[3]) || (cube[2][2][0].color[3] == colors[0] && cube[2][2][0].color[1] == colors[3] && cube[2][2][0].color[5] == colors[5]) || (cube[2][2][0].color[5] == colors[0] && cube[2][2][0].color[1] == colors[5] && cube[2][2][0].color[3] == colors[3])) {
            right = 5;
            if (cube[2][2][0].color[1] == colors[0]) {
                isRightHandAlgorithm = 3;
            } else if (cube[2][2][0].color[4] == colors[0]) {
                isRightHandAlgorithm = 5;
            } else {
                isRightHandAlgorithm = 1;
            }
            return;
        } else if (cube[2][0][0].color[1] != colors[0] && cube[2][0][0].color[2] != colors[0] && cube[2][0][0].color[5] != colors[0] && cube[0][0][0].color[1] != colors[0] && cube[0][0][0].color[2] != colors[0] && cube[0][0][0].color[4] != colors[0] && cube[0][2][0].color[1] != colors[0] && cube[0][2][0].color[4] != colors[0] && cube[0][2][0].color[3] != colors[0] && cube[2][2][0].color[1] != colors[0] && cube[2][2][0].color[3] != colors[0] && cube[2][2][0].color[5] != colors[0]) {
            if (cube[2][0][2].color[0] != colors[0] || cube[2][0][2].color[5] != colors[5] || cube[2][0][2].color[2] != colors[2]) {
                right = 2;
                isRightHandAlgorithm = 1;
            } else if (cube[0][0][2].color[0] != colors[0] || cube[0][0][2].color[2] != colors[2] || cube[0][0][2].color[4] != colors[4]) {
                right = 4;
                isRightHandAlgorithm = 1;
            } else if (cube[0][2][2].color[0] != colors[0] || cube[0][2][2].color[4] != colors[4] || cube[0][2][2].color[3] != colors[3]) {
                right = 3;
                isRightHandAlgorithm = 1;
            } else if (cube[2][2][2].color[0] != colors[0] || cube[2][2][2].color[3] != colors[3] || cube[2][2][2].color[5] != colors[5]) {
                right = 5;
                isRightHandAlgorithm = 1;
            }
        } else {
            rotate(0, true, true);
            return;
        }
    }
    
    void solveRightEdge() {
        switch (phase) {
            case 1: {
                rotate(0, false, true);
                return;
            }
                
            case 2: {
                rotate(left, false, true);
                return;
            }
                
            case 3: {
                rotate(0, false, true);
                return;
            }
            
            case 4: {
                rotate(left, true, true);
                return;
            }
                
            case 5: {
                rotate(0, true, true);
                return;
            }
                
            case 6: {
                rotate(right, true, true);
                return;
            }
                
            case 7: {
                rotate(0, true, true);
                return;
            }
                
            case 8: {
                rotate(right, false, true);
                return;
            }
                
            case 9: {
                rotate(0, false, true);
                return;
            }
        }
        isSolveRight = false;
        right = -1;
        left = -1;
        phase = 0;
    }
    
    void solveLeftEdge() {
        switch (phase) {
            case 1: {
                rotate(0, true, true);
                return;
            }
                
            case 2: {
                rotate(right, true, true);
                return;
            }
                
            case 3: {
                rotate(0, true, true);
                return;
            }
            
            case 4: {
                rotate(right, false, true);
                return;
            }
                
            case 5: {
                rotate(0, false, true);
                return;
            }
                
            case 6: {
                rotate(left, false, true);
                return;
            }
                
            case 7: {
                rotate(0, false, true);
                return;
            }
                
            case 8: {
                rotate(left, true, true);
                return;
            }
                
            case 9: {
                rotate(0, true, true);
                return;
            }
        }
        isSolveLeft = false;
        right = -1;
        left = -1;
        phase = 0;
    }
    
    void resolveEdge() {
        switch (phase) {
            case 1: {
                rotate(right, true, true);
                return;
            }
            
            case 2: {
                rotate(0, true, true);
                return;
            }
                
            case 3: {
                rotate(right, false, true);
                return;
            }
                
            case 4: {
                rotate(0, false, true);
                return;
            }
                
            case 5: {
                rotate(left, false, true);
                return;
            }
                
            case 6: {
                rotate(0, false, true);
                return;
            }
                
            case 7: {
                rotate(left, true, true);
                return;
            }
                
            case 8: {
                rotate(0, true, true);
                return;
            }
        }
        isWrongEdge = false;
        left = -1;
        right = -1;
        phase = 0;
    }
    
    void solveSecondLayer(unsigned int * colors) {
        if (isSolveRight) {
            if (current == -1) {
                phase++;
            }
            solveRightEdge();
            return;
        } else if (isSolveLeft) {
            if (current == -1) {
                phase++;
            }
            solveLeftEdge();
            return;
        } else if (isWrongEdge) {
            if (current == -1) {
                phase++;
            }
            resolveEdge();
            return;
        }
        if (cube[0][1][0].color[1] == colors[2] && cube[0][1][0].color[4] == colors[4]) {
            isSolveRight = true;
            left = 2;
            right = 4;
        } else if (cube[1][0][0].color[1] == colors[5] && cube[1][0][0].color[2] == colors[2]) {
            isSolveRight = true;
            left = 5;
            right = 2;
        } else if (cube[2][1][0].color[1] == colors[3] && cube[2][1][0].color[5] == colors[5]) {
            isSolveRight = true;
            left = 3;
            right = 5;
        } else if (cube[1][2][0].color[1] == colors[4] && cube[1][2][0].color[3] == colors[3]) {
            isSolveRight = true;
            left = 4;
            right = 3;
        } else if (cube[1][0][0].color[1] == colors[4] && cube[1][0][0].color[2] == colors[2]) {
            isSolveLeft = true;
            left = 2;
            right = 4;
        } else if (cube[2][1][0].color[1] == colors[2] && cube[2][1][0].color[5] == colors[5]) {
            isSolveLeft = true;
            left = 5;
            right = 2;
        } else if (cube[1][2][0].color[1] == colors[5] && cube[1][2][0].color[3] == colors[3]) {
            isSolveLeft = true;
            left = 3;
            right = 5;
        } else if (cube[0][1][0].color[1] == colors[3] && cube[0][1][0].color[4] == colors[4]) {
            isSolveLeft = true;
            left = 4;
            right = 3;
        } else if ((cube[0][1][0].color[1] != colors[1] && cube[0][1][0].color[4] != colors[1]) || (cube[2][1][0].color[1] != colors[1] && cube[2][1][0].color[5] != colors[1]) || (cube[1][2][0].color[1] != colors[1] && cube[1][2][0].color[3] != colors[1]) || (cube[1][0][0].color[1] != colors[1] && cube[1][0][0].color[2] != colors[1]) || (cube[2][1][0].color[1] != colors[1] && cube[2][1][0].color[5] != colors[1]) || (cube[1][2][0].color[1] != colors[1] && cube[1][2][0].color[3] != colors[1]) || (cube[0][1][0].color[1] != colors[1] && cube[0][1][0].color[4] != colors[1])) {
            rotate(0, true, true);
        } else if ((cube[0][2][1].color[4] != colors[4] || cube[0][2][1].color[3] != colors[3]) && (cube[0][2][1].color[4] != colors[1] || cube[0][2][1].color[3] != colors[1])) {
            isWrongEdge = true;
            left = 4;
            right = 3;
        } else if ((cube[2][2][1].color[3] != colors[3] || cube[2][2][1].color[5] != colors[5]) && (cube[2][2][1].color[3] != colors[1] || cube[2][2][1].color[5] != colors[1])) {
            isWrongEdge = true;
            left = 3;
            right = 5;
        } else if ((cube[2][0][1].color[5] != colors[5] || cube[2][0][1].color[2] != colors[2]) && (cube[2][0][1].color[5] != colors[1] || cube[2][0][1].color[2] != colors[1])) {
            isWrongEdge = true;
            left = 5;
            right = 2;
        } else if ((cube[0][0][1].color[2] != colors[2] || cube[0][0][1].color[4] != colors[4]) && (cube[0][0][1].color[2] != colors[1] || cube[0][0][1].color[4] != colors[1])) {
            isWrongEdge = true;
            left = 2;
            right = 4;
        }
    }
    
    void solveCross() {
        switch (phase) {
            case 1: {
                rotate(front, true, true);
                return;
            }
                
            case 2: {
                rotate(right, true, true);
                return;
            }
                
            case 3: {
                rotate(0, true, true);
                return;
            }
                
            case 4: {
                rotate(right, false, true);
                return;
            }
                
            case 5: {
                rotate(0, false, true);
                return;
            }
        
            case 6: {
                rotate(front, false, true);
                return;
            }
        }
        isSolveCross = false;
        front = -1;
        right = -1;
        phase = 0;
    }
    
    void solveYellowCross(unsigned int * colors) {
        if (isSolveCross) {
            if (current == -1) {
                phase++;
            }
            solveCross();
            return;
        }
        if (cube[1][2][0].color[1] != colors[1] && cube[0][1][0].color[1] != colors[1] && cube[1][0][0].color[1] != colors[1] && cube[2][1][0].color[1] != colors[1]) {
            isSolveCross = true;
            front = 2;
            right = 4;
        } else if (cube[1][2][0].color[1] == colors[1] && cube[0][1][0].color[1] != colors[1] && cube[1][0][0].color[1] != colors[1] && cube[2][1][0].color[1] == colors[1]) {
            isSolveCross = true;
            front = 2;
            right = 4;
        } else if (cube[1][2][0].color[1] != colors[1] && cube[0][1][0].color[1] != colors[1] && cube[1][0][0].color[1] == colors[1] && cube[2][1][0].color[1] == colors[1]) {
            isSolveCross = true;
            front = 4;
            right = 3;
        } else if (cube[1][2][0].color[1] != colors[1] && cube[0][1][0].color[1] == colors[1] && cube[1][0][0].color[1] == colors[1] && cube[2][1][0].color[1] != colors[1]) {
            isSolveCross = true;
            front = 3;
            right = 5;
        } else if (cube[1][2][0].color[1] == colors[1] && cube[0][1][0].color[1] == colors[1] && cube[1][0][0].color[1] != colors[1] && cube[2][1][0].color[1] != colors[1]) {
            isSolveCross = true;
            front = 5;
            right = 2;
        } else if (cube[1][2][0].color[1] == colors[1] && cube[0][1][0].color[1] != colors[1] && cube[1][0][0].color[1] == colors[1] && cube[2][1][0].color[1] != colors[1]) {
            isSolveCross = true;
            front = 5;
            right = 2;
        } else if (cube[1][2][0].color[1] != colors[1] && cube[0][1][0].color[1] == colors[1] && cube[1][0][0].color[1] != colors[1] && cube[2][1][0].color[1] == colors[1]) {
            isSolveCross = true;
            front = 2;
            right = 4;
        }
    }
    
    void solveRightCross() {
        switch (phase) {
            case 1: {
                rotate(right, true, true);
                return;
            }
                
            case 2: {
                rotate(0, true, true);
                return;
            }
                
            case 3: {
                rotate(right, false, true);
                return;
            }
                
            case 4: {
                rotate(0, true, true);
                return;
            }
                
            case 5: {
                rotate(right, true, true);
                return;
            }
                
            case 6: {
                rotate(0, true, false);
                return;
            }
                
            case 7: {
                rotate(right, false, true);
                return;
            }
                
            case 8: {
                rotate(0, true, true);
                return;
            }
        }
        isSolveRightCross = false;
        isSolveCrossLine = false;
        phase = 0;
        right = -1;
    }
    
    void solveRightYellowCross(unsigned int * colors) {
        if (isSolveRightCross) {
            if (current == -1) {
                phase++;
            }
            solveRightCross();
            return;
        } else if (isSolveCrossLine) {
            if (current == -1) {
                phase++;
                if (phase == 8) {
                    phase = 9;
                }
            }
            solveRightCross();
            return;
        }
        if (cube[1][0][0].color[2] == colors[2] && cube[0][1][0].color[4] == colors[4] && cube[1][2][0].color[3] == colors[3] && cube[2][1][0].color[5] == colors[5]) {
            return;
        } else if (cube[1][2][0].color[3] == colors[3] && cube[0][1][0].color[4] == colors[4] && cube[1][2][0].color[1] == colors[1] && cube[0][1][0].color[1] == colors[1]) {
            isSolveRightCross = true;
            right = 4;
        } else if (cube[0][1][0].color[4] == colors[4] && cube[1][0][0].color[2] == colors[2] && cube[0][1][0].color[1] == colors[1] && cube[1][0][0].color[1] == colors[1]) {
            isSolveRightCross = true;
            right = 2;
        } else if (cube[1][0][0].color[2] == colors[2] && cube[2][1][0].color[5] == colors[5] && cube[1][0][0].color[1] == colors[1] && cube[2][1][0].color[1] == colors[1]) {
            isSolveRightCross = true;
            right = 5;
        } else if (cube[2][1][0].color[5] == colors[5] && cube[1][2][0].color[3] == colors[3] && cube[2][1][0].color[1] == colors[1] && cube[1][2][0].color[1] == colors[1]) {
            isSolveRightCross = true;
            right = 3;
        } else if (cube[1][2][0].color[3] == colors[3] && cube[1][0][0].color[2] == colors[2] && cube[1][2][0].color[1] == colors[1] && cube[1][0][0].color[1] == colors[1]) {
            isSolveCrossLine = true;
            right = 4;
        } else if (cube[2][1][0].color[5] == colors[5] && cube[0][1][0].color[4] == colors[4] && cube[2][1][0].color[1] == colors[1] && cube[0][1][0].color[1] == colors[1]) {
            isSolveCrossLine = true;
            right = 2;
        } else {
            rotate(0, true, true);
        }
    }
    
    void solveCorners() {
        switch (phase) {
            case 1: {
                rotate(right, true, true);
                return;
            }
                
            case 2: {
                rotate(0, false, true);
                return;
            }
                
            case 3: {
                rotate(left, false, true);
                return;
            }
                
            case 4: {
                rotate(0, true, true);
                return;
            }
                
            case 5: {
                rotate(right, false, true);
                return;
            }
                
            case 6: {
                rotate(0, false, true);
                return;
            }
                
            case 7: {
                rotate(left, true, true);
                return;
            }
                
            case 8: {
                rotate(0, true, true);
                return;
            }
        }
        left = -1;
        right = -1;
        isSolveCorners = false;
        phase = 0;
    }
    
    void solveCornersAroundYellowCenter(unsigned int * colors) {
        if (isSolveCorners) {
            if (current == -1) {
                phase++;
            }
            solveCorners();
            return;
        }
        if (((cube[0][0][0].color[2] == colors[2] && cube[0][0][0].color[4] == colors[4]) || (cube[0][0][0].color[1] == colors[4] && cube[0][0][0].color[4] == colors[2]) || (cube[0][0][0].color[1] == colors[2] && cube[0][0][0].color[2] == colors[4])) && ((cube[0][2][0].color[4] == colors[4] && cube[0][2][0].color[3] == colors[3]) || (cube[0][2][0].color[1] == colors[4] && cube[0][2][0].color[4] == colors[3]) || (cube[0][2][0].color[1] == colors[3] && cube[0][2][0].color[3] == colors[4])) && ((cube[2][2][0].color[3] == colors[3] && cube[2][2][0].color[5] == colors[5]) || (cube[2][2][0].color[1] == colors[3] && cube[2][2][0].color[3] == colors[5]) || (cube[2][2][0].color[1] == colors[5] && cube[2][2][0].color[5] == colors[3])) && ((cube[2][0][0].color[5] == colors[5] && cube[2][0][0].color[2] == colors[2]) || (cube[2][0][0].color[1] == colors[5] && cube[2][0][0].color[5] == colors[2]) || (cube[2][0][0].color[1] == colors[2] && cube[2][0][0].color[2] == colors[5]))) {
            return;
        } else if ((cube[0][0][0].color[2] == colors[2] && cube[0][0][0].color[4] == colors[4]) || (cube[0][0][0].color[1] == colors[4] && cube[0][0][0].color[4] == colors[2]) || (cube[0][0][0].color[1] == colors[2] && cube[0][0][0].color[2] == colors[4])) {
            right = 3;
            left = 2;
            isSolveCorners = true;
        } else if ((cube[0][2][0].color[4] == colors[4] && cube[0][2][0].color[3] == colors[3]) || (cube[0][2][0].color[1] == colors[4] && cube[0][2][0].color[4] == colors[3]) || (cube[0][2][0].color[1] == colors[3] && cube[0][2][0].color[3] == colors[4])) {
            right = 5;
            left = 4;
            isSolveCorners = true;
        } else if ((cube[2][2][0].color[3] == colors[3] && cube[2][2][0].color[5] == colors[5]) || (cube[2][2][0].color[1] == colors[3] && cube[2][2][0].color[3] == colors[5]) || (cube[2][2][0].color[1] == colors[5] && cube[2][2][0].color[5] == colors[3])) {
            right = 2;
            left = 3;
            isSolveCorners = true;
        } else {
            right = 4;
            left = 5;
            isSolveCorners = true;
        }
    }
    
    void doReversedRightHandAlgorithm() {
        switch (phase) {
            case 1: {
                rotate(right, true, true);
                return;
            }
                
            case 2: {
                rotate(1, true, true);
                return;
            }
                
            case 3: {
                rotate(right, false, true);
                return;
            }
                
            case 4: {
                rotate(1, false, true);
                return;
            }
        }
        isSolveThirdLayer = false;
        phase = 0;
    }
    
    void solveThirdLayer(unsigned int * colors) {
        if (isSolveThirdLayer) {
            if (current == -1) {
                phase++;
            }
            doReversedRightHandAlgorithm();
            return;
        }
        if (cube[0][0][0].color[1] == colors[1] && cube[0][2][0].color[1] == colors[1] && cube[2][2][0].color[1] == colors[1] && cube[2][0][0].color[1] == colors[1]) {
            return;
        } else if (cube[0][0][0].color[1] != colors[1]) {
            right = 2;
            isSolveThirdLayer = true;
        } else if (right == -1 && cube[0][2][0].color[1] != colors[1]) {
            right = 4;
            isSolveThirdLayer = true;
        } else if (right == -1 && cube[2][2][0].color[1] != colors[1]) {
            right = 3;
            isSolveThirdLayer = true;
        } else if (right == -1 && cube[2][0][0].color[1] != colors[1]) {
            right = 5;
            isSolveThirdLayer = true;
        } else {
            rotate(0, true, true);
            return;
        }
    }
    
    bool solve(unsigned int * colors) {
        if (!isSolved(colors)) {
            isAlreadySolved = false;
            if (sweayc) {
                solveWhiteEdgesAroundYellowCenter(colors);
                if (cube[0][1][0].color[1] == colors[0] && cube[1][0][0].color[1] == colors[0] && cube[2][1][0].color[1] == colors[0] && cube[1][2][0].color[1] == colors[0]) {
                    sweayc = false;
                    sweawc = true;
                }
            } else if (sweawc) {
                solveWhiteEdgesAroundWhiteCenter(colors);
                if (cube[2][1][2].color[0] == colors[0] && cube[1][0][2].color[0] == colors[0] && cube[0][1][2].color[0] == colors[0] && cube[1][2][2].color[0] == colors[0]) {
                    sweawc = false;
                    swcawc = true;
                }
            } else if (swcawc) {
                solveWhiteCornersAroundWhiteCenter(colors);
                if (cube[0][2][2].color[0] == colors[0] && cube[1][2][2].color[0] == colors[0] && cube[2][2][2].color[0] == colors[0] && cube[0][1][2].color[0] == colors[0] & cube[1][1][2].color[0] == colors[0] && cube[2][1][2].color[0] == colors[0] && cube[0][0][2].color[0] == colors[0] && cube[1][0][2].color[0] == colors[0] && cube[2][0][2].color[0] == colors[0]) {
                    right = -1;
                    swcawc = false;
                    ssl = true;
                    phase = 0;
                }
            } else if (ssl) {
                solveSecondLayer(colors);
                if (cube[0][2][1].color[4] == colors[4] && cube[0][2][1].color[3] == colors[3] && cube[2][2][1].color[3] == colors[3] && cube[2][2][1].color[5] == colors[5] && cube[2][0][1].color[5] == colors[5] && cube[2][0][1].color[2] == colors[2] && cube[0][0][1].color[2] == colors[2] && cube[0][0][1].color[4] == colors[4]) {
                    ssl = false;
                    syc = true;
                    phase = 0;
                    right = -1;
                    left = -1;
                }
            } else if (syc) {
                solveYellowCross(colors);
                if (cube[1][2][0].color[1] == colors[1] && cube[0][1][0].color[1] == colors[1] && cube[1][0][0].color[1] == colors[1] && cube[2][1][0].color[1] == colors[1]) {
                    syc = false;
                    sryc = true;
                    right = -1;
                    front = -1;
                    phase = 0;
                }
            } else if (sryc) {
                solveRightYellowCross(colors);
                if (cube[1][0][0].color[2] == colors[2] && cube[0][1][0].color[4] == colors[4] && cube[1][2][0].color[3] == colors[3] && cube[2][1][0].color[5] == colors[5]) {
                    sryc = false;
                    scayc = true;
                    right = -1;
                    phase = 0;
                }
            } else if (scayc) {
                solveCornersAroundYellowCenter(colors);
                if (((cube[0][0][0].color[2] == colors[2] && cube[0][0][0].color[4] == colors[4]) || (cube[0][0][0].color[1] == colors[4] && cube[0][0][0].color[4] == colors[2]) || (cube[0][0][0].color[1] == colors[2] && cube[0][0][0].color[2] == colors[4])) && ((cube[0][2][0].color[4] == colors[4] && cube[0][2][0].color[3] == colors[3]) || (cube[0][2][0].color[1] == colors[4] && cube[0][2][0].color[4] == colors[3]) || (cube[0][2][0].color[1] == colors[3] && cube[0][2][0].color[3] == colors[4])) && ((cube[2][2][0].color[3] == colors[3] && cube[2][2][0].color[5] == colors[5]) || (cube[2][2][0].color[1] == colors[3] && cube[2][2][0].color[3] == colors[5]) || (cube[2][2][0].color[1] == colors[5] && cube[2][2][0].color[5] == colors[3])) && ((cube[2][0][0].color[5] == colors[5] && cube[2][0][0].color[2] == colors[2]) || (cube[2][0][0].color[1] == colors[5] && cube[2][0][0].color[5] == colors[2]) || (cube[2][0][0].color[1] == colors[2] && cube[2][0][0].color[2] == colors[5]))) {
                    scayc = false;
                    stl = true;
                    left = -1;
                    right = -1;
                    phase = 0;
                }
            } else if (stl) {
                solveThirdLayer(colors);
                if (cube[0][0][0].color[1] == colors[1] && cube[0][2][0].color[1] == colors[1] && cube[2][2][0].color[1] == colors[1] && cube[2][0][0].color[1] == colors[1]) {
                    stl = false;
                    lastStep = true;
                }
            } else if (lastStep) {
                if (cube[0][2][2].color[4] != colors[4]) {
                    rotate(1, false, true);
                } else if (cube[0][2][0].color[4] != colors[4]) {
                    rotate(0, true, true);
                } else {
                    lastStep = false;
                }
            }
            return false;
        } else {
            if (!isAlreadySolved) {
                std::vector<std::string> parsedSolution;
                for (int i = 0; i < solution.size(); i++) {
                    if (i < solution.size() - 2 && solution[i] == solution[i + 1] && solution[i] == solution[i + 2]) {
                        if (solution[i] == "W") {
                            parsedSolution.push_back("W'");
                        } else if (solution[i] == "Y") {
                            parsedSolution.push_back("Y'");
                        } else if (solution[i] == "B") {
                            parsedSolution.push_back("B'");
                        } else if (solution[i] == "G") {
                            parsedSolution.push_back("G'");
                        } else if (solution[i] == "R") {
                            parsedSolution.push_back("R'");
                        } else if (solution[i] == "O") {
                            parsedSolution.push_back("O'");
                        } else if (solution[i] == "W'") {
                            parsedSolution.push_back("W");
                        } else if (solution[i] == "Y'") {
                            parsedSolution.push_back("Y");
                        } else if (solution[i] == "B'") {
                            parsedSolution.push_back("B");
                        } else if (solution[i] == "G'") {
                            parsedSolution.push_back("G");
                        } else if (solution[i] == "R'") {
                            parsedSolution.push_back("R");
                        } else if (solution[i] == "O'") {
                            parsedSolution.push_back("O");
                        }
                            
                        i += 2;
                        continue;
                    }
                    
                    if (i < solution.size() - 1 && solution[i] == solution[i + 1]) {
                        if (solution[i] == "W" || solution[i] == "W'") {
                            parsedSolution.push_back("W2");
                        } else if (solution[i] == "Y" || solution[i] == "Y'") {
                            parsedSolution.push_back("Y2");
                        } else if (solution[i] == "B" || solution[i] == "B'") {
                            parsedSolution.push_back("B2");
                        } else if (solution[i] == "G" || solution[i] == "G'") {
                            parsedSolution.push_back("G2");
                        } else if (solution[i] == "R" || solution[i] == "R'") {
                            parsedSolution.push_back("R2");
                        } else if (solution[i] == "O" || solution[i] == "O'") {
                            parsedSolution.push_back("O2");
                        }
                        
                        i++;
                        continue;
                    }
                    
                    if (i < solution.size() - 1) {
                        if ((solution[i] == "W" && solution[i + 1] == "W'") || (solution[i] == "W'" && solution[i + 1] == "W")) {
                            i++;
                            continue;
                        } else if ((solution[i] == "Y" && solution[i + 1] == "Y'") || (solution[i] == "Y'" && solution[i + 1] == "Y")) {
                            i++;
                            continue;
                        } else if ((solution[i] == "B" && solution[i + 1] == "B'") || (solution[i] == "B'" && solution[i + 1] == "B")) {
                            i++;
                            continue;
                        } else if ((solution[i] == "G" && solution[i + 1] == "G'") || (solution[i] == "G'" && solution[i + 1] == "G")) {
                            i++;
                            continue;
                        } else if ((solution[i] == "R" && solution[i + 1] == "R'") || (solution[i] == "R'" && solution[i + 1] == "R")) {
                            i++;
                            continue;
                        } else if ((solution[i] == "O" && solution[i + 1] == "O'") || (solution[i] == "O'" && solution[i + 1] == "O")) {
                            i++;
                            continue;
                        }
                    }
                    
                    parsedSolution.push_back(solution[i]);
                }
                std::cout << "Куб собран! Для его сборки ";
                switch (parsedSolution.size() % 10) {
                    case 1: {
                        std::cout << "потребовался " << parsedSolution.size() << " шаг." << std::endl;
                        break;
                    }
                        
                    case 2:
                    case 3:
                    case 4: {
                        std::cout << "потребовалось " << solution.size() << " шага." << std::endl;
                        break;
                    }
                        
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9: {
                        std::cout << "потребовалось " << solution.size() << " шагов." << std::endl;
                    }
                }
                std::cout << "Последовательность повротов граней в обозначении Сингмастера и метрики FTM: ";
                for (int i = 0; i < parsedSolution.size(); i++) {
                    std::cout << parsedSolution[i] << " ";
                }
                std::cout << std::endl;
                isAlreadySolved = true;
                parsedSolution.clear();
            } else {
                std::cout << "Куб уже собран!" << std::endl;
            }
            return true;
        }
        return false;
    }
    
    void input(std::ifstream & fin) {
        std::string version;
        
        int width;
        int height;
        short int depth;
        
        std::vector<std::vector<unsigned int>> image;
        image.resize(12);  // height (12)
        for (int i = 0; i < 12; i++) {
            image[i].resize(27);  // width (9) * 3
        }
        
        fin >> version;
        if (version != "P3") {
            throw Exception("Неверное значение версии PNM-файла (должно быть P3)!");
        }
        fin >> width >> height;
        if (width != 9 || height != 12) {
            throw Exception("Неверное значение резмера (должно быть 9x12)!");
        }
        fin >> depth;
        if (depth != 255) {
            throw Exception("Неверное значение глубины цвета (должно быть 255)!");
        }
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < 27; j++) {
                fin >> image[i][j];
            }
        }
        
        for (int i = 0; i < 3; i++) {
            for (int j = 9; j < 18; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[j / 3 - 3][2][i].setColor(3, color);
            }
        }
        
        for (int i = 3; i < 6; i++) {
            for (int j = 0; j < 9; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[0][2 - (i - 3)][j / 3].setColor(4, color);
            }
        }

        for (int i = 3; i < 6; i++) {
            for (int j = 9; j < 18; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[j / 3 - 3][2 - (i - 3)][2].setColor(0, color);
            }
        }

        for (int i = 3; i < 6; i++) {
            for (int j = 18; j < 27; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[2][2 - (i - 3)][2 - (j / 3 - 6)].setColor(5, color);
            }
        }

        for (int i = 6; i < 9; i++) {
            for (int j = 9; j < 18; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[j / 3 - 3][0][2 - (i - 6)].setColor(2, color);
            }
        }

        for (int i = 9; i < 12; i++) {
            for (int j = 9; j < 18; j += 3) {
                unsigned int color = (image[i][j] << 16);
                color += (image[i][j + 1] << 8);
                color += image[i][j + 2];
                cube[j / 3 - 3][i - 9][0].setColor(1, color);
            }
        }
        
        for (int i = 0; i < 12; i++) {
            image[i].clear();
        }
        image.clear();
    }
    
    void print(std::ofstream & fout) {
        fout << "P3" << "\n";
        fout << "9 12" << "\n";
        fout << "255" << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << ((cube[j][2][i].color[3]) >> 16) << " ";
                fout << ((cube[j][2][i].color[3] & 0x00FF00) >> 8) << " ";
                fout << (cube[j][2][i].color[3] & 0x0000FF) << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        
        for (int i = 2; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                fout << ((cube[0][i][j].color[4]) >> 16) << " ";
                fout << ((cube[0][i][j].color[4] & 0x00FF00) >> 8) << " ";
                fout << (cube[0][i][j].color[4] & 0x0000FF) << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << ((cube[j][i][2].color[0]) >> 16) << " ";
                fout << ((cube[j][i][2].color[0] & 0x00FF00) >> 8) << " ";
                fout << (cube[j][i][2].color[0] & 0x0000FF) << " ";
            }
            for (int j = 2; j >= 0; j--) {
                fout << ((cube[2][i][j].color[5]) >> 16) << " ";
                fout << ((cube[2][i][j].color[5] & 0x00FF00) >> 8) << " ";
                fout << (cube[2][i][j].color[5] & 0x0000FF) << " ";
            }
        }
        
        for (int i = 2; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << ((cube[j][0][i].color[2]) >> 16) << " ";
                fout << ((cube[j][0][i].color[2] & 0x00FF00) >> 8) << " ";
                fout << (cube[j][0][i].color[2] & 0x0000FF) << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << ((cube[j][i][0].color[1]) >> 16) << " ";
                fout << ((cube[j][i][0].color[1] & 0x00FF00) >> 8) << " ";
                fout << (cube[j][i][0].color[1] & 0x0000FF) << " ";
            }
            for (int j = 0; j < 3; j++) {
                fout << 0 << " " << 0 << " " << 0 << " ";
            }
        }
    }
};
 
#endif
