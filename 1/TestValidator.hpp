#ifndef TEST_VALIDATOR_HPP

#define TEST_VALIDATOR_HPP

#include "AbstractValidator.hpp"

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Concrete implementation of AbstractValidator used only for test purposes and during early development
 * Does not contain any business logic and can be considered an empty block
 */
class TestValidator: public AbstractValidator<std::string> {

    public:

        void validate(const std::string& entity) override;

        ~TestValidator() {}

};

#endif
