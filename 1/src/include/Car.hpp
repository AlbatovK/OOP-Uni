#ifndef CAR_HPP

#define CAR_HPP 

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Basic class representing a Car entity with 3 fields: brand, owner and mileage
 * Sole purpose is to be serializable object for transportation
 */
class Car {
    std::string brand;
    std::string owner;
    double mileage;

public:
    /// Returns brand of a car
    [[nodiscard]] std::string getBrand() const;

    /// Returns owner of a car
    [[nodiscard]] std::string getOwner() const;

    /// Returns car mileage
    [[nodiscard]] double getMileage() const;

    /// Sets car brand
    void setBrand(const std::string &brand);

    /// Sets car owner
    void setOwner(const std::string &owner);

    /// Sets car mileage
    void setMileage(const double &mileage);

    /// Full primary constructor
    Car(const std::string &brand, const std::string &owner, const double &mileage);

    /// Secondary constructor defaulting mileage to 0.0 miles
    Car(const std::string &brand, const std::string &owner);

    [[nodiscard]] std::string toString() const;
};

#endif
