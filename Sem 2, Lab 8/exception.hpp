#ifndef exception_hpp
#define exception_hpp
#include <iostream>

class Exception: public std::exception {
    std::string error;
public:
    explicit Exception(std::string);
    
    [[nodiscard]] const char * what() const noexcept override;
};

#endif
