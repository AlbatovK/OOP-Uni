#ifndef RESOURCE_TABLE_HPP

#define RESOURCE_TABLE_HPP

#include "Resource.hpp"

#include "ResourceTable.hpp"

/**
 * @authors Konstantin Albatov
 * @date 28.09.2024 13:52
 * @version 1.0
 * This class represents a table filled with resources of Resource class
 * Its purpose is to provide interface to view and change multiple resources at once
 */
class ResourceTable {
    Resource *resources;

    int resourceCount, capacity;

public:
    /**
    * @brief Enumerates possible filling status of a resource table
    */
    enum class FILL_STATUS {
        STATUS_EMPTY, STATUS_PARTIALLY_FILLED, STATUS_FULL
    };

    /**
         * @brief Constructor for creating a ResourceTable with specified resources.
         *
         * @param resources Pointer to an array of resources.
         * @param resourceCount Number of resources in the array.
         * @param capacity Capacity of the resource table.
         * @throws InvalidStateException If capacity is less than resource count
         */
    ResourceTable(const Resource *resources, const int &resourceCount, const int &capacity);

    /**
     * @brief  Overloads the multiplication operator (*) for scaling the resource table.
     *
     * @param times The scaling factor.
     * @return A new ResourceTable with scaled resource properties.
     * @throws InvalidStateException If times is less than 0
     */
    ResourceTable operator*(const int &times);

    /**
     * @brief Copy constructor for creating a copy of a ResourceTable.
     *
     * @param other The ResourceTable to be copied.
     */
    ResourceTable(const ResourceTable &other);

    /**
    * @brief Default constructor for creating an empty ResourceTable.
    */
    ResourceTable();

    /**
     * @brief Sets the capacity of the resource table.
     *
     * @param capacity The new capacity.
     * @throws InvalidStateException If capacity is less than 0 or less than current size
     */
    void setCapacity(const int &capacity);

    /**
     * @brief Returns the capacity of the resource table.
     *
     * @return The capacity of the resource table.
     */
    [[nodiscard]] int getCapacity() const;

    /**
        * @brief Returns a pointer (basic iterator) to the beginning of the resource array.
        *
        * @return A pointer to the beginning of the resource array.
        */
    [[nodiscard]] Resource *begin() const;

    /**
        * @brief Returns a pointer (basic iterator) to the end of the resource array.
        *
        * @return A pointer to the end of the resource array.
        */
    [[nodiscard]] Resource *end() const;

    /**
        * @brief Move constructor for efficient transfer of ownership.
        *
        * @param other The ResourceTable to be moved.
        */
    ResourceTable(ResourceTable &&other) noexcept;

    /**
     * @brief Renames a resource within the table.
     *
     * @param oldName The old name of the resource.
     * @param newName The new name for the resource.
     * @throws InvalidStateException If resource with old name does not exist
     */
    void renameResourceByName(const std::string &oldName, const std::string &newName) const;

    /**
        * @brief Calculates the total profit for all resources in the table over a given period.
        *
        * @param days The number of days for which to calculate profit.
        * @return The total profit.
        */
    [[nodiscard]] double countAllProfit(const int &days) const;

    /**
        * @brief Destructor for freeing allocated memory.
        */
    ~ResourceTable();

    /**
     * @brief Returns the filling status of the resource table.
     *
     * @return The filling status of the resource table.
     */
    [[nodiscard]] FILL_STATUS getStatus() const;

    /**
     * @brief Deletes a resource from the table by its name.
     *
     * @param name The name of the resource to delete.
     * @return The deleted resource.
     * @throws InvalidStateException if resource with given name not found.
     */
    Resource &deleteFromTable(const std::string &name);

    /**
     * @brief Move assignment operator for efficient transfer of ownership.
     *
     * @param other The ResourceTable to be moved.
     * @return A reference to the current object.
     */
    ResourceTable &operator=(ResourceTable &&other) noexcept;

    /**
    * @brief Copy assignment operator for copying another ResourceTable.
    *
    * @param other The ResourceTable to be copied.
    * @return A reference to the current object.
    */
    ResourceTable &operator=(const ResourceTable &other);

    /**
     * @brief Returns the current number of resources in the table.
     *
     * @return The number of resources.
     */
    [[nodiscard]] int getResourceCount() const;

    /**
     * @brief Adds a resource to the table.
     *
     * @param res The resource to be added.
     * @return A reference to the current object.
     * @throws InvalidStateException If table is already full
     */
    ResourceTable &operator+=(const Resource &res);

    /**
     * @brief Accesses a resource in the table by its name.
     *
     * @param name The name of the resource.
     * @return A reference to the resource.
     * @throws InvalidStateException if resource with given name not found.
     */
    [[nodiscard]] Resource operator[](const std::string &name) const;

    /**
        * @brief Returns a string representation of the ResourceTable.
        *
        * @return A string representation of the ResourceTable.
        */
    [[nodiscard]] std::string toString() const;

    /**
     * @brief Overloads the insertion operator (<<) for printing a ResourceTable object to an output stream.
     *
     * @param output The output stream.
     * @param table The ResourceTable object to be printed.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &output, const ResourceTable &table);

    /**
        * @brief Overloads the extraction operator (>>) for reading a ResourceTable object from an input stream.
        *
        * @param in The input stream.
        * @param table The ResourceTable object to be read.
        * @return The input stream.
        */
    friend std::istream &operator>>(std::istream &in, ResourceTable &table);
};


#endif
