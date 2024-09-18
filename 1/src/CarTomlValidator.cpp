#include "CarTomlValidator.hpp"

#include "ValidationException.hpp"

#include <string>

#include <regex>

void CarTomlValidator::validate(const std::string &entity) {
    bool structureMatches = false;
    std::ranges::sort(this->fields);
    do {
        std::stringstream ss;
        ss << "\n*.+\n*"
                << this->fields[0] << " *= *.+\n*"
                << this->fields[1] << " *= *.+\n*"
                << this->fields[2] << " *= *.+\n*";
        if (const std::regex structureRegex(ss.str()); std::regex_match(entity.data(), structureRegex)) {
            structureMatches = true;
            break;
        }
    } while (std::ranges::next_permutation(this->fields).found);

    if (!structureMatches) {
        throw ValidationException("Car Structure is incorrect.", "Car Structure");
    }

    std::smatch m;
    const std::regex findBrandRegex("brand *= *\"[a-zA-Z -]{1,16}+\"");
    if (!std::regex_search(entity, m, findBrandRegex)) {
        throw ValidationException("Brand is only a-z, A-Z and ' ' + '-'. and not empty and no longer than 16 chars",
                                  "Brand");
    }

    const std::regex findOwnerRegex("owner *= *\".+\"");
    if (!std::regex_search(entity, m, findOwnerRegex)) {
        throw ValidationException("Owner is malformed.", "Owner");
    }

    const std::regex findMileageRegex("mileage *= *(0|([1-9][0-9]*))(\\.[0-9]+)");
    if (!std::regex_search(entity, m, findMileageRegex)) {
        throw ValidationException("Mileage must be a non-negative double.", "Mileage");
    }
}
