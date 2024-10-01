#include "include/Resource.hpp"


Resource::Resource(const std::string &name, const double &consumption, const double &production, const double &price) {
    if (production < 0) {
        throw InvalidStateException("Production cannot be negative.", "Production");
    }

    if (price < 0) {
        throw InvalidStateException("Price cannot be negative.", "Price");
    }

    if (consumption < 0) {
        throw InvalidStateException("Consumption cannot be negative.", "Consumption");
    }

    this->name = name;
    this->consumption = consumption;
    this->production = production;
    this->price = price;
}

Resource::Resource(const std::string &name, const double &price): Resource(name, 0, 0, price) {
}

Resource::Resource(): Resource("undefined", 0, 0, 0) {
}

Resource Resource::operator+(const Resource &other) const {
    return {
        this->name + other.name,
        this->consumption + other.consumption,
        this->production + other.production,
        std::min(this->price, other.price)
    };
}

[[nodiscard]] double Resource::calculateProfit(const double &days) const {
    return (this->production - this->consumption) * days * this->price;
}

Resource Resource::operator*(const double &times) const {
    if (times < 0) {
        throw InvalidStateException("Times cannot be negative.", "Times");
    }

    return {
        this->name,
        this->consumption * times,
        this->production * times,
        this->price
    };
}

void Resource::setName(const std::string &name) {
    this->name = name;
}

[[nodiscard]] std::string Resource::getName() const {
    return this->name;
}

void Resource::setConsumption(const double &consumption) {
    if (consumption < 0) {
        throw InvalidStateException("Consumption cannot be negative.", "Consumption");
    }

    this->consumption = consumption;
}

[[nodiscard]] double Resource::getConsumption() const {
    return this->consumption;
}

void Resource::setProduction(const double &production) {
    if (production < 0) {
        throw InvalidStateException("Production cannot be negative.", "Production");
    }

    this->production = production;
}

[[nodiscard]] double Resource::getProduction() const {
    return this->production;
}

void Resource::setPrice(const double &price) {
    if (price < 0) {
        throw InvalidStateException("Price cannot be negative.", "Price");
    }

    this->price = price;
}

[[nodiscard]] double Resource::getPrice() const {
    return this->price;
}

[[nodiscard]] std::string Resource::toString() const {
    return "Resource(" + this->name + ", " + std::to_string(this->consumption) + ", " +
           std::to_string(this->production) + ", " + std::to_string(this->price) + ")";
}

std::ostream &operator<<(std::ostream &output, const Resource &res) {
    output << res.toString();
    return output;
}

std::istream &operator>>(std::istream &in, Resource &res) {
    std::string name;
    double consumption, production, price;
    in >> name >> consumption >> production >> price;

    res.setName(name);
    res.setConsumption(consumption);
    res.setProduction(production);
    res.setPrice(price);

    return in;
}
