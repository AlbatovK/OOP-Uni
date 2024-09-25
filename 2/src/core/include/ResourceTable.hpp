#ifndef RESOURCE_TABLE_HPP

#define RESOURCE_TABLE_HPP

#include "Resource.hpp"

#include "ResourceTable.hpp"


class ResourceTable {
    Resource *resources;

    int resourceCount, capacity;

public:
    enum class FILL_STATUS {
        STATUS_EMPTY, STATUS_PARTIALLY_FILLED, STATUS_FULL
    };

    ResourceTable(const Resource *resources, const int &resourceCount, const int &capacity);

    ResourceTable operator*(const int &times);

    ResourceTable(const ResourceTable &other);

    ResourceTable();

    void setCapacity(const int &capacity);

    [[nodiscard]] int getCapacity() const;

    [[nodiscard]] Resource *begin() const;

    [[nodiscard]] Resource *end() const;

    ResourceTable(ResourceTable &&other) noexcept;

    void renameResourceByName(const std::string &oldName, const std::string &newName) const;

    [[nodiscard]] double countAllProfit(const int &days) const;

    ~ResourceTable();

    [[nodiscard]] FILL_STATUS getStatus() const;

    Resource& deleteFromTable(const std::string &name);

    ResourceTable &operator=(ResourceTable &&other) noexcept;

    ResourceTable &operator=(const ResourceTable &other);

    [[nodiscard]] int getResourceCount() const;

    ResourceTable &operator+=(const Resource &res);

    [[nodiscard]] Resource operator[](const std::string &name) const;

    [[nodiscard]] std::string toString() const;

    friend std::ostream &operator<<(std::ostream &output, const ResourceTable &table);

    friend std::istream &operator>>(std::istream &in, ResourceTable &table);
};


#endif
