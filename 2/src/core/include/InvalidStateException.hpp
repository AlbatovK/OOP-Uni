#ifndef INVALID_STATE_EXCEPTION_HPP

#define INVALID_STATE_EXCEPTION_HPP

#include <string>

class InvalidStateException final : public std::exception {
    std::string message;

    std::string fieldName;

public:
    InvalidStateException(const char *message, const char *fieldName);

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

    [[nodiscard]] std::string getMessage() const;
};

#endif
