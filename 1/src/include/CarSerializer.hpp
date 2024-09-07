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
 * Concrete implementation of AbstractSerializer aimed at serialization/deserialization of Car objects
 */
class CarSerializer final : public AbstractSerializer<Car> {
    AbstractValidator<std::string> *validator;

public:
    std::string serialize(const Car &, const std::string &structName) override;

    Car deserialize(const char *) override;

    Car deserialize(const char *, const size_t &) override;

    Car deserialize(const std::string &) override;

    explicit CarSerializer(AbstractValidator<std::string> *validator);

    CarSerializer();

    ~CarSerializer() override;
};

#endif
