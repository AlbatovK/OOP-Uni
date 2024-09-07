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
class IOException final : public std::exception {
    std::string message;

public:
    explicit IOException(const char *message);

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

    [[nodiscard]] std::string getMessage() const;
};

#endif
