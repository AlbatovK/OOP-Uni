#include <iostream>

#include "Car.hpp"

#include "CarSerializer.hpp"

#include "CarTomlValidator.hpp"

#include "ValidationException.hpp"

int main() {
    CarSerializer s = CarSerializer(new CarTomlValidator());
    try {
        Car c = s.deserialize("[car]\nbrand = \"BMW\"\nowner = \"PYA\"\nmileage = 10.3");
        std::cout << c.getMileage() << std::endl;
    } catch (ValidationException e) {
        std::cout << e.getMessage() << std::endl;
    }
    return 0;
}