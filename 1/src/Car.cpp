#include <string>

#include "Car.hpp"

std::string Car::getBrand() const {
    return this->brand;
}

std::string Car::getOwner() const {
    return this->owner;
}

double Car::getMileage() const {
    return mileage;
}

void Car::setBrand(const std::string &brand) {
    this->brand = brand;
}

void Car::setOwner(const std::string &owner) {
    this->owner = owner;
}

void Car::setMileage(const double &mileage) {
    this->mileage = mileage;
}

Car::Car(const std::string &brand, const std::string &owner, const double &mileage) {
    this->brand = brand;
    this->owner = owner;
    this->mileage = mileage;
}

Car::Car(const std::string &brand, const std::string &owner): Car(brand, owner, 0.0) {
}

std::string Car::toString() const {
    return "Car(brand=" + brand + ", owner=" + owner + ", mileage=" + std::to_string(mileage) + ")";
}
