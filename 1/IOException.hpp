#ifndef IO_EXCEPTION_HPP

#define IO_EXCEPTION_HPP 

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Exception class used to indicate a problem in Input/Output operations like opening a file in local storage
 * Contains message with brief description of an error
 */
class IOException {

    private:
        
        std::string message;
        
    public:

        IOException(const char * message);

        std::string getMessage();

};

#endif
