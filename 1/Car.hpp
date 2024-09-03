#ifndef CAR_HPP

#define CAR_HPP 

#include <string>

class Car {

    private:
        
        std::string brand;
        std::string owner;
        double mileage;

    public:

        std::string getBrand(void);

        std::string getOwner(void);

        double getMileage(void);

        void setBrand(std::string brand);

        void setOwner(std::string owner);

        void setMileage(double mileage);

        Car(std::string brand, std::string owner, double mileage);

        Car(std::string brand, std::string owner);

};

#endif