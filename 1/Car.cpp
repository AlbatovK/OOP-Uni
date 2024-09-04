#include <iostream>

#include <string>

#include "ValidationException.hpp"

#include "AbstractSerializer.hpp"

#include "Car.hpp"

std::string Car::getBrand(void) const {
    return this -> brand;
}

std::string Car::getOwner(void) const {
    return this -> owner;
}

double Car::getMileage(void) const {
    return mileage;
}

void Car::setBrand(std::string brand) {
    this -> brand = brand;
}

void Car::setOwner(std::string owner) {
    this -> owner = owner;
}

void Car::setMileage(double mileage) {
    this -> mileage = mileage;
}

Car::Car(std::string brand, std::string owner, double mileage) {
    this -> brand = brand;
    this -> owner = owner;
    this -> mileage = mileage;
}

Car::Car(std::string brand, std::string owner): Car(brand, owner, 0.0) {}
