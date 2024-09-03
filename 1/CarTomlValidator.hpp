#ifndef CAR_TOML_VALIDATOR

#define CAR_TOML_VALIDATOR

#include "AbstractValidator.hpp"

#include <string>

class CarTomlValidator: public AbstractValidator<std::string> {

    public:

        void validate(std::string entity) override;

};

#endif