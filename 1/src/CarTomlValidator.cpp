#include "CarTomlValidator.hpp"

#include "ValidationException.hpp"

#include <string>

#include <regex>

void CarTomlValidator::validate(const std::string &entity) {
    const std::regex structureRegex("\n*.+\nbrand = \".+\"\nowner = \".+\"\nmileage = .+\n*");

    if (!std::regex_match(entity.data(), structureRegex)) {
        throw ValidationException("Car Structure is incorrect.", "Car Structure");
    }

    std::smatch m;
    const std::regex findBrandRegex("brand = \"[a-zA-Z -]+\"");
    if (!std::regex_search(entity, m, findBrandRegex)) {
        throw ValidationException("Brand is only a-z, A-Z and ' ' + '-'.", "Brand");
    }

    if (m.empty() || m[0].length() > 8 + 16 + 2) {
        throw ValidationException("Brand must be no longer than 16 chars.", "Brand");
    }

    const std::regex findOnwerRegex("owner = \".+\"");
    if (!std::regex_search(entity, m, findOnwerRegex)) {
        throw ValidationException("Owner is malformed.", "Owner");
    }

    const std::regex findMileageRegex("mileage = \\d*.\\d*");
    if (!std::regex_search(entity, m, findMileageRegex)) {
        throw ValidationException("Mileage must be a double.", "Mileage");
    }
}
