#include "IOException.hpp"

IOException::IOException(const char * message) {
    this -> message = message;
}

std::string IOException::getMessage() {
    return this -> message;
}
