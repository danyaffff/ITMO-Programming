#ifndef exception_hpp
#define exception_hpp
#include <iostream>

class Exception: public std::exception {
    std::string _error;
    
public:
    Exception(std::string);
    
    const char * what() const noexcept override;
};


#endif
