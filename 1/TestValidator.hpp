#ifndef TEST_VALIDATOR_HPP

#define TEST_VALIDATOR_HPP

#include "AbstractValidator.hpp"

#include <string>

class TestValidator: public AbstractValidator<std::string> {

    public:

        void validate(std::string entity) override;

        ~TestValidator() {}

};

#endif
