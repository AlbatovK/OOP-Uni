#ifndef CAR_SERIALIZER_HPP

#define CAR_SERIALIZER_HPP

#include "AbstractSerializer.hpp"

#include "AbstractValidator.hpp"

#include "Car.hpp"

#include <string>

/**
 * \authors Konstantin Albatov
 * \date 04.09.2024 4:19
 * \version 1.0
 * Conrete implementation of AbstractSerializer aimed at serialization/deserialization of Car objects
 */
class CarSerializer : public AbstractSerializer<Car> {

    private:

        AbstractValidator<std::string> * validator;

    public:

        std::string serialize(const Car&, const std::string& structName) override;
        
        Car deserialize(const char *) override;

        Car deserialize(const char *, size_t) override;
        
        Car deserialize(const std::string&) override;

        CarSerializer(AbstractValidator<std::string> * validator);

        CarSerializer();

        ~CarSerializer();

};

#endif
