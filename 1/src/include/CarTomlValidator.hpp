#ifndef CAR_TOML_VALIDATOR

#define CAR_TOML_VALIDATOR

#include "AbstractValidator.hpp"

#include <string>

#include <vector>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Concrete implementation of AbstractValidator used to validate serialized Car objects in TOML format before transforming
 */
class CarTomlValidator final : public AbstractValidator<std::string> {
    std::vector<std::string> fields = {"brand", "owner", "mileage"};

public:
    void validate(const std::string &entity) override;

    ~CarTomlValidator() override = default;
};

#endif
