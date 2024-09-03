#ifndef VALIDATION_EXCEPTION_HPP

#define VALIDATION_EXCEPTION_HPP 

#include <string>

class ValidationException {

    private:
        
        std::string message;
        
        std::string fieldName;

    public:

        ValidationException(const char * message, const char * fieldName);

        std::string getMessage();

};

#endif