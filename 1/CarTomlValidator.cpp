#include "CarTomlValidator.hpp"

#include "ValidationException.hpp"

#include <iostream>

#include <cstring>

#include <string>

#include <regex>

void CarTomlValidator::validate(std::string entity) {

    const std::regex structureRegex(".+\nbrand = \".+\"\nowner = \".+\"\nmileage = .+");
    
    if (!std::regex_match(entity.data(), structureRegex)) {
        throw ValidationException("Car Structure is incorrect.", "Car Structure");
    }
    
    std::smatch m;
    const std::regex findBrandRegex("brand = \"[a-zA-Z -]+\"");
    if (!std::regex_search(entity, m, findBrandRegex)) {
          throw ValidationException("Brand is only a-z, A-Z and ' ' + '-'.", "Brand");
    }

    if (m.size() == 0 || m[0].length() > strlen("brand = ") + 3 + 2) {
        throw ValidationException("Brand must be no longer than 16 chars.", "Brand");
    }

    const std::regex findOnwerRegex("owner = \".+\"");
    if (!std::regex_search(entity, m, findOnwerRegex)) {
          throw ValidationException("Owner is malformed.", "Owner");
    }

    const std::regex findMileageRegex("mileage = \\d..\\d");
    if (!std::regex_search(entity, m, findMileageRegex)) {
          throw ValidationException("Mileage must be a double.", "Mileage");
    }

}
