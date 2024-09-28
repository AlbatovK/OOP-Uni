#ifndef RESOURCE_HPP

#define RESOURCE_HPP

#include <string>

#include <iostream>

#include "InvalidStateException.hpp"

/**
 * @authors Konstantin Albatov
 * @date 28.09.2024 13:52
 * @version 1.0
 * This class represents a resource with properties like name, consumption, production, and price.
 */
class Resource {
    std::string name;

    double consumption;

    double production;

    double price;

public:
    /**
     * Default constructor, initializes with default values.
     */
    Resource();

    /**
     * Constructor for initializing all properties of the resource.
     * @param name Resource name
     * @param consumption Resource consumption
     * @param production Resource production
     * @param price Resource price
     * @throws InvalidStateException if values are invalid (less than zero, etc.)
     */
    Resource(const std::string &name, const double &consumption, const double &production, const double &price);

    /**
     * Constructor for initializing only name and price of the resource.
     * Other properties are initialized with default values
     * @param name Resource name
     * @param price Resource price
     * @throws InvalidStateException if values are invalid (less than zero, etc.)
     */
    Resource(const std::string &name, const double &price);

    /**
     * Overloads the addition operator (`+`) for combining two resources.
     * The resulting resource will have the sum of production and consumption of the two combined resources.
     * The price of resulted is resource is minimum from prices of two initial resources.
     * The names are also concatenated.
     * @param other Resource to combine with
     * @return New Resource with set values
     */
    Resource operator+(const Resource &other) const;

    /**
     * Overloads the spaceship operator (`<=>`) for comparing two resources based on their names.
     * @param other Resource to compare with
     * @return Result of ordering two resources
     */
    auto operator<=>(const Resource &other) const {
        return this->name <=> other.name;
    }

    /**
     *  Calculates the profit from the resource for a given number of days.
     *  The profit is calculated as the difference between the production revenue and the consumption cost.
     * @param days Number of days to from period to calculate profit for
     * @return Calculated profit value
     * @throws InvalidStateException If number of days is less than zero
     */
    [[nodiscard]] double calculateProfit(const double &days) const;

    /**
     * Overloads the multiplication operator (`*`) for scaling the resource properties.
     * @param times The number that consumption and production are multiplied by. Can be negative as well as zero\
     * @return New resource with consumption and production scaled by a number
     */
    Resource operator*(const double &times) const;

    /**
     * Sets the name of the resource.
     * @param name New resource name
     */
    void setName(const std::string &name);

    /**
     * Returns the name of the resource.
     * @return Resource name
     */
    [[nodiscard]] std::string getName() const;

    /**
     * Sets the consumption of the resource.
     * @param consumption New Resource consumption
     * @throws InvalidStateException of consumption is less than zero
     */
    void setConsumption(const double &consumption);

    /**
     * Returns resource consumption
     * @return Resource consumption
     */
    [[nodiscard]] double getConsumption() const;

    /**
     * Sets the production of the resource.
     * @param production New production value
     * @throws InvalidStateException If production is less than zero
     */
    void setProduction(const double &production);

    /**
     * Returns the production of the resource.
     * @return Resource production
     */
    [[nodiscard]] double getProduction() const;

    /**
     * Sets the price of the resource.
     * @param price New price
     * @throws InvalidStateException If price is less than zero
     */
    void setPrice(const double &price);

    /**
     * Returns the price of the resource.
     * @return Resource price
     */
    [[nodiscard]] double getPrice() const;

    /**
     * Convert Resource to string value
     * @return A string representation of the resource
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Write Resource object to a stream
     * @param output The output stream.
     * @param res The Resource object to be printed.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &output, const Resource &res);

    /**
    * Read Resource object from a stream
    * @param in The input stream.
    * @param res The Resource object to be read.
    * @return The input stream.
    */
    friend std::istream &operator>>(std::istream &in, Resource &res);
};


#endif
