#include "CarTomlValidator.hpp"

#include <iostream>

#include "ValidationException.hpp"

#include <string>

#include <regex>


void CarTomlValidator::validate(const std::string &entity) {
    const std::regex findFieldRegex("[a-zA-Z]+ *= *.*\n");

    std::ptrdiff_t const match_count(std::distance(
        std::sregex_iterator(entity.begin(), entity.end(), findFieldRegex), std::sregex_iterator()));
    if (match_count < 3) {
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
