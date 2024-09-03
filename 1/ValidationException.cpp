#include "ValidationException.hpp"

ValidationException::ValidationException(const char * message, const char * fieldName) {
    this -> message = message;
    this -> fieldName = fieldName;
}

std::string ValidationException::getMessage() {
    return (this -> fieldName + ": " + this -> message);
}