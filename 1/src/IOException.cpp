#include "IOException.hpp"

IOException::IOException(const char *message) {
    this->message = message;
}

std::string IOException::getMessage() const {
    return this->message;
}
