#include <iostream>

#include <fstream>

#include <limits>

#include "Utils.hpp"

#include <map>

#include <string>

#include "IOException.hpp"
#include "ResourceTable.hpp"

bool tryRead(auto &value) {
    std::cin >> value;

    if (std::cin.good()) {
        return true;
    }

    if (std::cin.eof()) {
        throw IOException("End Of File.");
    }

    if (std::cin.bad()) {
        throw IOException("Really-Really-Wrong Input.");
    }

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

template<typename T>
T read() {
    T res;
    while (!tryRead(res)) {
        std::cout << "Wrong Input. Enter again." << std::endl;
    }
    return res;
}

struct FunctionCallResult {
    std::string message;
    bool success = true;
};

std::string handleExit(ResourceTable &) {
    return "Exiting...";
}

std::string createResourceTable(ResourceTable &table) {
    std::cout << "Enter Resource Table: " << std::endl;
    std::cin >> table;
    return "Entered Resource Table:\n" + table.toString();
}

std::string printTable(ResourceTable &table) {
    return table.toString();
}

std::string setCapacity(ResourceTable &table) {
    std::cout << "Enter Capacity: " << std::endl;
    int capacity;
    std::cin >> capacity;
    table.setCapacity(capacity);
    return "Changed capacity to " + std::to_string(capacity);
}

std::string addNewResource(ResourceTable &table) {
    std::cout << "Enter Resource: " << std::endl;
    Resource resource;
    std::cin >> resource;
    table += resource;
    return "Add New Resource To Table: " + resource.toString();
}

std::string getResourceByName(ResourceTable &table) {
    std::cout << "Enter resource name: " << std::endl;
    std::string resource;
    std::cin >> resource;
    return table[resource].toString();
}

std::string getResourceState(ResourceTable &table) {
    std::map<ResourceTable::FILL_STATUS, std::string> statusMap;
    statusMap[ResourceTable::FILL_STATUS::STATUS_FULL] = "Full";
    statusMap[ResourceTable::FILL_STATUS::STATUS_EMPTY] = "Empty";
    statusMap[ResourceTable::FILL_STATUS::STATUS_PARTIALLY_FILLED] = "Partially Full";
    return statusMap[table.getStatus()];
}

std::string deleteResource(ResourceTable &table) {
    std::cout << "Enter resource name: " << std::endl;
    std::string resource;
    std::cin >> resource;
    const Resource deleted = table.deleteFromTable(resource);
    return "Deleted " + deleted.toString();
}

std::string calculateProfit(ResourceTable &table) {
    std::cout << "Enter days: ";
    int days;
    std::cin >> days;
    return "Profit for " + std::to_string(days) + " days: " + std::to_string(table.countAllProfit(days));
}

std::string increaseTurnover(ResourceTable &table) {
    std::cout << "Enter turnover: ";
    int turnover;
    std::cin >> turnover;
    table = table * turnover;
    return "Increased turnover";
}

std::string renameResource(ResourceTable &table) {
    std::cout << "Enter old resource name: " << std::endl;
    std::string oldResource;
    std::cin >> oldResource;
    std::cout << "Enter new resource name: " << std::endl;
    std::string newResource;
    std::cin >> newResource;
    table.renameResourceByName(oldResource, newResource);
    return "Renamed Resource " + oldResource + " to " + newResource;
}

struct ConsoleHandler {
    std::map<int, std::string (*)(ResourceTable &)> commands;
    bool isActive = true;

    FunctionCallResult operator()(const int &command, ResourceTable &resourceTable) {
        const auto it = commands.find(command);
        if (it == commands.end()) {
            isActive = false;
            return FunctionCallResult(handleExit(resourceTable), true);
        }

        try {
            return FunctionCallResult(commands[it->first](resourceTable), true);
        } catch (const std::exception &e) {
            return FunctionCallResult(e.what(), false);
        }
    }

    void add(const int &command, std::string (*f)(ResourceTable &table)) {
        this->commands[command] = f;
    }

    [[nodiscard]] bool active() const {
        return this->isActive;
    }
};

int main() {
    std::cout << "1 - create new table." << std::endl;
    std::cout << "2 - add new resource." << std::endl;
    std::cout << "3 - print table." << std::endl;
    std::cout << "4 - change capacity." << std::endl;
    std::cout << "5 - get resource by name." << std::endl;
    std::cout << "6 - get table state." << std::endl;
    std::cout << "7 - delete resource by name." << std::endl;
    std::cout << "8 - calculate profit for days." << std::endl;
    std::cout << "9 - increase turnover." << std::endl;
    std::cout << "10 - rename resource by name." << std::endl;

    ResourceTable table;

    ConsoleHandler handler;
    handler.add(1, createResourceTable);
    handler.add(2, addNewResource);
    handler.add(3, printTable);
    handler.add(4, setCapacity);
    handler.add(5, getResourceByName);
    handler.add(6, getResourceState);
    handler.add(7, deleteResource);
    handler.add(8, calculateProfit);
    handler.add(9, increaseTurnover);
    handler.add(10, renameResource);

    while (handler.active()) {
        std::cout << "Enter command num: ";
        int command = 0;
        try {
            command = read<int>();
        } catch (const std::exception &e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }

        if (auto [message, success] = handler(command, table); success) {
            std::cout << message << std::endl;
        } else {
            std::cout << "Error happened: " << message << std::endl;
            std::cout << "Return to main menu." << std::endl;
        }
    }

    return 0;
}
