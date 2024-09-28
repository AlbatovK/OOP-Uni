#include "include/ResourceTable.hpp"

#include <algorithm>

#include <sstream>

#include <iostream>

#include <numeric>

std::pair<Resource &, int> findResourceFromResourceTableByName(const ResourceTable &table,
                                                               const std::string &resourceName) {
    auto res = std::lower_bound(
        table.begin(),
        table.end(),
        resourceName,
        [&](const Resource &resource, const std::string &name) {
            return resource.getName() < name;
        });

    if (res == table.end() || res->getName() != resourceName) {
        throw std::invalid_argument("Resource with name " + resourceName + " not found.");
    }

    return {*res, res - table.begin()};
}

long int findResourceIndexFromResourceTableByName(const ResourceTable &table, const std::string &resourceName) {
    const auto res = std::lower_bound(
        table.begin(),
        table.end(),
        resourceName,
        [&](const Resource &resource, const std::string &name) {
            return resource.getName() < name;
        });

    return res - table.begin();
}

ResourceTable::ResourceTable(const Resource *resources, const int &resourceCount, const int &capacity) {
    if (resourceCount > capacity) {
        throw InvalidStateException("Current resource count cannot be higher than capacity", "Capacity");
    }

    this->resourceCount = resourceCount;
    this->capacity = capacity;

    this->resources = new Resource[this->resourceCount];

    if (resources == nullptr) {
        return;
    }

    std::copy_n(resources, this->resourceCount, this->resources);
}

ResourceTable ResourceTable::operator*(const int &times) {
    if (times < 0) {
        throw InvalidStateException("Times cannot be negative.", "Times");
    }

    auto table = ResourceTable(this->resources, this->resourceCount, this->capacity);
    std::ranges::for_each(table, [&](Resource &resource) { resource = resource * times; });
    return table;
}

ResourceTable::ResourceTable(const ResourceTable &other): ResourceTable(other.resources, other.resourceCount,
                                                                        other.capacity) {
}

ResourceTable::ResourceTable(): ResourceTable(nullptr, 0, 0) {
}

void ResourceTable::setCapacity(const int &capacity) {
    if (this->capacity < 0) {
        throw InvalidStateException("Capacity cannot be negative", "Capacity");
    }

    if (capacity < this->resourceCount) {
        throw InvalidStateException("Capacity cannot be lower than current resource count", "Capacity");
    }

    this->capacity = capacity;
}

int ResourceTable::getCapacity() const {
    return this->capacity;
}

Resource *ResourceTable::begin() const {
    return this->resources;
}

Resource *ResourceTable::end() const {
    return this->resources + this->resourceCount;
}

ResourceTable::ResourceTable(ResourceTable &&other) noexcept {
    this->resources = other.resources;
    this->resourceCount = other.resourceCount;
    this->capacity = other.capacity;
    other.resources = nullptr;
    other.resourceCount = 0;
    other.capacity = 0;
}

void ResourceTable::renameResourceByName(const std::string &oldName, const std::string &newName) const {
    if (oldName == newName) {
        return;
    }

    auto [resource, index] = findResourceFromResourceTableByName(*this, oldName);
    resource.setName(newName);

    std::ranges::sort(*this, [](const Resource &resource1, const Resource &resource2) {
        return resource1.getName() < resource2.getName();
    });
}

double ResourceTable::countAllProfit(const int &days) const {
    if (days < 0) {
        throw InvalidStateException("Days cannot be negative.", "Days");
    }

    return std::accumulate(
        this->begin(),
        this->end(),
        0.0,
        [days](const double &profit, const Resource &resource) {
            return profit + resource.calculateProfit(days);
        });
}

ResourceTable::~ResourceTable() {
    delete[] this->resources;
    this->resources = nullptr;
    this->resourceCount = 0;
    this->capacity = 0;
}

ResourceTable::FILL_STATUS ResourceTable::getStatus() const {
    if (this->resourceCount == 0) {
        return FILL_STATUS::STATUS_EMPTY;
    }

    if (this->resourceCount == this->capacity) {
        return FILL_STATUS::STATUS_FULL;
    }

    return FILL_STATUS::STATUS_PARTIALLY_FILLED;
}

Resource &ResourceTable::deleteFromTable(const std::string &name) {
    if (this->resourceCount == 0) {
        throw InvalidStateException("Resource table is empty", "ResourceCount");
    }

    auto [res, index] = findResourceFromResourceTableByName(*this, name);

    std::copy_n(this->resources + index + 1, this->resourceCount - index - 2, this->resources + index);

    this->resourceCount--;

    return res;
}

ResourceTable &ResourceTable::operator=(ResourceTable &&other) noexcept {
    if (this != &other) {
        delete[] this->resources;
        this->resources = other.resources;
        this->resourceCount = other.resourceCount;
        this->capacity = other.capacity;
        other.resources = nullptr;
        other.resourceCount = 0;
        other.capacity = 0;
    }

    return *this;
}

ResourceTable &ResourceTable::operator=(const ResourceTable &other) {
    if (this != &other) {
        delete[] this->resources;
        this->resourceCount = other.resourceCount;
        this->resources = new Resource[this->resourceCount];
        this->capacity = other.capacity;
        std::copy_n(other.resources, this->resourceCount, this->resources);
    }

    return *this;
}

int ResourceTable::getResourceCount() const {
    return this->resourceCount;
}

ResourceTable &ResourceTable::operator+=(const Resource &res) {
    if (this->resourceCount == this->capacity) {
        throw InvalidStateException("ResourceTable is full.", "Capacity");
    }

    const auto index = findResourceIndexFromResourceTableByName(*this, res.getName());
    this->resourceCount++;
    auto *new_resources = new Resource[this->resourceCount];

    new_resources[index] = res;

    std::copy_n(this->resources, index, new_resources);
    std::copy_n(this->resources + index, this->resourceCount - index - 1, new_resources + index + 1);

    delete[] this->resources;
    this->resources = new_resources;
    return *this;
}

Resource ResourceTable::operator[](const std::string &name) const {
    return findResourceFromResourceTableByName(*this, name).first;
}


std::string ResourceTable::toString() const {
    std::stringstream ss;
    ss << "ResourceTable(" << std::to_string(this->resourceCount) << ", " << std::to_string(this->capacity) << ")";
    if (!this->resourceCount) {
        return ss.str();
    }

    std::for_each(
        this->resources,
        this->resources + this->resourceCount,
        [&ss](const Resource &resource) {
            ss << "\n\t" << resource.toString();
        }
    );

    return ss.str();
}

std::ostream &operator<<(std::ostream &output, const ResourceTable &table) {
    output << table.toString();
    return output;
}

std::istream &operator>>(std::istream &in, ResourceTable &table) {
    int capacity;
    in >> capacity;
    delete[] table.resources;
    table.resourceCount = 0;
    table.setCapacity(capacity);
    table.resourceCount = capacity;
    table.resources = new Resource[capacity];
    std::for_each(
        table.resources,
        table.resources + table.resourceCount,
        [&](Resource &resource) {
            in >> resource;
        }
    );

    std::ranges::sort(table, [](const Resource &resource1, const Resource &resource2) {
        return resource1.getName() < resource2.getName();
    });

    return in;
}
