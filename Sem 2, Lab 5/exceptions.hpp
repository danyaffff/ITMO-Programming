#ifndef exceptions_hpp
#define exceptions_hpp
#include <iostream>
using namespace std;

class Exception: exception {
    string error;
    
public:
    Exception(string);
    
    const char * what() const noexcept override;
};

#endif
