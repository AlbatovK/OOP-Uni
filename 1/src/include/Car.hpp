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
    /// \return Car brand
    [[nodiscard]] std::string getBrand() const;

    /// Returns owner of a car
    /// \return Car owner
    [[nodiscard]] std::string getOwner() const;

    /// Returns car mileage
    /// \return Car mileage
    [[nodiscard]] double getMileage() const;

    /// Updates car brand
    /// \param brand Car new brand
    void setBrand(const std::string &brand);

    /// Updates car owner
    /// \param owner Car new owner
    void setOwner(const std::string &owner);

    /// Updates car mileage
    /// \param mileage Car new mileage
    void setMileage(const double &mileage);

    /// Full primary constructor
    /// \param mileage Car's mileage
    /// \param brand Car's brand
    /// \param owner Car's owner
    Car(const std::string &brand, const std::string &owner, const double &mileage);

    /// Secondary constructor defaulting mileage to 0.0 miles
    /// \param brand Car's brand
    /// \param owner Car's owner
    Car(const std::string &brand, const std::string &owner);

    /// Method that converts object into string representation convenient for output
    /// \return String representation of an Car object
    [[nodiscard]] std::string toString() const;
};

#endif
