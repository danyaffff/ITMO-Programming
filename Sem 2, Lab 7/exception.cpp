#include "exception.hpp"

Exception::Exception(std::string error): _error(std::move(error)) {}

const char * Exception::what() const noexcept {
    return _error.c_str();
}
