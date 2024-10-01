#include "InvalidStateException.hpp"

InvalidStateException::InvalidStateException(const char *message, const char *fieldName) {
    this->message = message;
    this->fieldName = fieldName;
}

std::string InvalidStateException::getMessage() const {
    return this->fieldName + ": " + this->message;
}
