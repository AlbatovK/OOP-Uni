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

    private:
        
        std::string brand;
        std::string owner;
        double mileage;

    public:

		/// Returns brand of a car
        std::string getBrand(void) const;

		/// Returns owner of a car
        std::string getOwner(void) const;

		/// Returns car mileage
        double getMileage(void) const;

		/// Sets car brand
        void setBrand(std::string brand);

		/// Sets car owner
        void setOwner(std::string owner);

		/// Sets car mileage
        void setMileage(double mileage);

		/// Full primary constructor
        Car(std::string brand, std::string owner, double mileage);

		/// Secondary constructor defaulting mileage to 0.0 miles
        Car(std::string brand, std::string owner);

};

#endif
