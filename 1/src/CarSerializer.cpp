#include "CarSerializer.hpp"

#include "TestValidator.hpp"

#include "Car.hpp"

#include <sstream>

#include <iomanip>

#include <map>

Car CarSerializer::deserialize(const char *input) {
    return this->deserialize(
        std::string(input)
    );
}

void rtrim(std::string &s, const char *t = " \t\n") {
    s.erase(s.find_last_not_of(t) + 1);
}

void ltrim(std::string &s, const char *t = " \t\n") {
    s.erase(0, s.find_first_not_of(t));
}

void trim(std::string &s, const char *t = " \t\n") {
    ltrim(s, t);
    rtrim(s, t);
}

bool isStringBlank(const std::string &s) {
    return std::all_of(s.begin(), s.end(), [](const unsigned char &c) {
        return std::isspace(c) || c == ' ' || c == '\t' || c == '\r' || c == '\n';
    });
}

Car CarSerializer::deserialize(const std::string &input) {
    this->validator->validate(input);
    std::string trimmed(input);
    trim(trimmed);

    std::stringstream stringBuilder(trimmed);
    std::string token;

    std::map<std::string, std::string> fieldData;

    getline(stringBuilder, token, '\n');

    while (getline(stringBuilder, token, '\n')) {
        if (!isStringBlank(token)) {
            std::stringstream fieldBuilder(token);

            std::string field;
            getline(fieldBuilder, field, '=');
            trim(field);

            std::string fieldValue;
            getline(fieldBuilder, fieldValue, '=');
            trim(fieldValue);

            fieldData[field] = fieldValue;
        }
    }

    return {fieldData["brand"], fieldData["owner"], std::stod(fieldData["mileage"])};
}

Car CarSerializer::deserialize(const char *input, const size_t &size) {
    return this->deserialize(
        std::string(input, size)
    );
}

std::string CarSerializer::serialize(const Car &input, const std::string &structName) {
    std::stringstream stringBuilder;
    stringBuilder << "[" << structName << "]" << "\n";
    stringBuilder << "brand = " << "\"" << input.getBrand() << "\"" << "\n";
    stringBuilder << "owner = " << "\"" << input.getOwner() << "\"" << "\n";
    stringBuilder << "mileage = " << std::setprecision(5) << input.getMileage();
    auto res = stringBuilder.str();
    this->validator->validate(res);
    return res;
}

CarSerializer::CarSerializer() {
    this->validator = new TestValidator();
}

CarSerializer::CarSerializer(AbstractValidator<std::string> *validator) {
    this->validator = validator;
}

CarSerializer::~CarSerializer() {
    delete this->validator;
    this->validator = nullptr;
}
