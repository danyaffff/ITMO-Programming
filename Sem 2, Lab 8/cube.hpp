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
 
    Cube();
    
    ~Cube();
 
    void clear(double, unsigned int *);
 
    void draw();
    
    void rotateVector(int, int);
 
    void rotate(int, bool, bool);
    
    void clearSolving();
    
    bool isSolved(unsigned int *);
    
    void solveWhiteEdgesAroundYellowCenter(unsigned int *);
    
    void solveWhiteEdgesAroundWhiteCenter(unsigned int *);
    
    void doRightHandAlgorithm();
    
    void solveWhiteCornersAroundWhiteCenter(unsigned int *);
    
    void solveRightEdge();
    
    void solveLeftEdge();
    
    void resolveEdge();
    
    void solveSecondLayer(unsigned int *);
    
    void solveCross();
    
    void solveYellowCross(unsigned int *);
    
    void solveRightCross();
    
    void solveRightYellowCross(unsigned int *);
    
    void solveCorners();
    
    void solveCornersAroundYellowCenter(unsigned int *);
    
    void doReversedRightHandAlgorithm();
    
    void solveThirdLayer(unsigned int *);
    
    bool solve(unsigned int *);
    
    void input(std::ifstream &);
    
    void print(std::ofstream &);
};
 
#endif
