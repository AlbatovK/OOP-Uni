#include "CarSerializer.hpp"

#include "TestValidator.hpp"

#include "Car.hpp"

Car CarSerializer::deserialize(const char * input) {
    this -> validator -> validate(input);
    return Car("", "", 2.0);
}

Car CarSerializer::deserialize(std::string input) {
    this -> validator -> validate(input);
    return Car("", "", 2.0);
}

Car CarSerializer::deserialize(const char * input, size_t size) {
    this -> validator -> validate(
        std::string(input, size + 1)
    );
    
    return Car("", "", 2.0);
}

std::string CarSerializer::serialize(Car input, std::string structName) {
    return "";
}

CarSerializer::CarSerializer() {
    this -> validator = new TestValidator();
}

CarSerializer::CarSerializer(AbstractValidator<std::string> * validator) {
    this -> validator = validator;
}