#ifndef CAR_SERIALIZER_HPP

#define CAR_SERIALIZER_HPP

#include "AbstractSerializer.hpp"

#include "AbstractValidator.hpp"

#include "Car.hpp"

#include <string>

class CarSerializer : public AbstractSerializer<Car> {

    private:

        AbstractValidator<std::string> * validator;

    public:

        std::string serialize(Car, std::string structName) override;
        
        Car deserialize(const char *) override;

        Car deserialize(const char *, size_t) override;
        
        Car deserialize(std::string) override;

        CarSerializer(AbstractValidator<std::string> * validator);

        CarSerializer();

};

#endif