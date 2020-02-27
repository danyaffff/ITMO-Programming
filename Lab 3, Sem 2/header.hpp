#ifndef Square_hpp
#define Square_hpp

typedef struct point {
    double x;
    double y;
} point;

typedef struct vector {
    point start;
    point end;
    point difference;
} vec;

class square {
    point a;
    double angle;
    double rib;
    
public:
    square(point, double, double);
    
    double getX();
    double getY();
    
    bool operator== (square &);
    bool operator!= (square &);
    bool operator< (square &);
    bool operator> (square &);
    
    double operator* (double &);
    
    point operator+ (vec &);
};

class array {
    int size;
    int *data;
    
public:
    array();
    array(int);
    array(const array &);
    ~array();
     
    void set();
    
    array operator+ (array &);
    
    bool operator== (array &);
    bool operator!= (array &);
    bool operator< (array &);
    bool operator> (array &);
    
    void showArr();
};

#endif
