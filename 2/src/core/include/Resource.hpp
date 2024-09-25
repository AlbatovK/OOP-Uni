#ifndef RESOURCE_HPP

#define RESOURCE_HPP

#include <string>

#include <iostream>

#include "InvalidStateException.hpp"

class Resource {
    std::string name;

    double consumption;

    double production;

    double price;

public:
    Resource();

    Resource(const std::string &name, const double &consumption, const double &production, const double &price);

    Resource(const std::string &name, const double &price);

    Resource operator+(const Resource &other) const;

    auto operator<=>(const Resource &other) const {
        return this->name <=> other.name;
    }

    [[nodiscard]] double calculateProfit(const double &days) const;

    Resource operator*(const double &times) const;

    void setName(const std::string &name);

    [[nodiscard]] std::string getName() const;

    void setConsumption(const double &consumption);

    [[nodiscard]] double getConsumption() const;

    void setProduction(const double &production);

    [[nodiscard]] double getProduction() const;

    void setPrice(const double &price);

    [[nodiscard]] double getPrice() const;

    [[nodiscard]] std::string toString() const;

    friend std::ostream &operator<<(std::ostream &output, const Resource &res);

    friend std::istream &operator>>(std::istream &in, Resource &res);
};


#endif
