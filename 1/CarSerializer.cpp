#include "CarSerializer.hpp"

#include "TestValidator.hpp"

#include "Car.hpp"

#include <sstream>

#include <iomanip>

#include <iostream>

Car CarSerializer::deserialize(const char * input) {
	return this -> deserialize(
		std::string(input)
	);
}

Car CarSerializer::deserialize(const std::string& input) {
    this -> validator -> validate(input);
	std::stringstream stringBuilder(input);
	std::string token;
	
	getline(stringBuilder, token, '\n');
	getline(stringBuilder, token, '\n');

	std::string brand;
	std::stringstream brandBuilder(token);
	getline(brandBuilder, brand, '=');
	getline(brandBuilder, brand, '=');

	brand = brand.substr(2, brand.size() - 3);

	getline(stringBuilder, token, '\n');

	std::string owner;
	std::stringstream ownerBuilder(token);
	getline(ownerBuilder, owner, '=');
	getline(ownerBuilder, owner, '=');

	owner = owner.substr(2, owner.size() - 3);

	getline(stringBuilder, token, '\n');

	std::string s_mileage;
	std::stringstream mileageBuilder(token);
	getline(mileageBuilder, s_mileage, '=');
	getline(mileageBuilder, s_mileage, '=');
	
	double mileage = std::stod(s_mileage);
    
    return Car(brand, owner, mileage);
}

Car CarSerializer::deserialize(const char * input, size_t size) {
    return this -> deserialize(
    	std::string(input, size + 1)
    );
}

std::string CarSerializer::serialize(const Car& input, const std::string& structName) {
	std::stringstream stringBuilder;
	stringBuilder << "[" << structName << "]" << "\n";
	stringBuilder << "brand = " << "\"" << input.getBrand() << "\"" << "\n";
	stringBuilder << "owner = " << "\"" << input.getOwner() << "\"" << "\n";
	stringBuilder << "mileage = " << std::setprecision(5) << input.getMileage();
    return stringBuilder.str();
}

CarSerializer::CarSerializer() {
    this -> validator = new TestValidator();
}

CarSerializer::CarSerializer(AbstractValidator<std::string> * validator) {
    this -> validator = validator;
}

CarSerializer::~CarSerializer() {
	delete this -> validator;
}
