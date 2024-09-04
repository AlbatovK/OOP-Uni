#ifndef VALIDATION_EXCEPTION_HPP

#define VALIDATION_EXCEPTION_HPP 

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Exception class used to indicate a problem in serialized object structure or format, making it impossible to convert to original object 
 * Contains message with brief description of an error and an optional name of the field, that caused a problem
 */
class ValidationException {

    private:
        
        std::string message;
        
        std::string fieldName;

    public:

        ValidationException(const char * message, const char * fieldName);

        std::string getMessage();

};

#endif
