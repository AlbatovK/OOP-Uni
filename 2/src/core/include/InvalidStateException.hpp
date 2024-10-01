#ifndef INVALID_STATE_EXCEPTION_HPP

#define INVALID_STATE_EXCEPTION_HPP

#include <string>

/**
 * @authors Konstantin Albatov
 * @date 28.09.2024 13.47
 * @version 1.0
 * Exception class used to indicate an invalid state of a certain object like invalid fields values etc.
 * Contains message with brief description of an error and an invalid field name
 */
class InvalidStateException final : public std::exception {
    std::string message;

    std::string fieldName;

public:
    /**
     * Creates new InvalidStateException instance
     * @param message Description on state and why error occurred
     * @param fieldName The field that is problematic (if there is one)
     */
    InvalidStateException(const char *message, const char *fieldName);

    /**
     * Returns brief description of an error
     * @return C-style string containing error description
     */
    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

    /**
    * Returns message that IOException object was constructed with
    * @return String message containing description of an error
    */
    [[nodiscard]] std::string getMessage() const;
};

#endif
