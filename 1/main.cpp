#include <iostream>

#include <fstream>

#include <limits>

#include <map>

#include <string>

#include "src/include/Car.hpp"

#include "src/include/CarSerializer.hpp"

#include "src/include/CarTomlValidator.hpp"

#include "src/include/IOException.hpp"

std::string readFile(const std::string &path) {
    std::ifstream inputFile(path);

    if (!inputFile.is_open()) {
        throw IOException("File could not be opened.");
    }

    std::string res;
    std::string line;
    while (std::getline(inputFile, line)) {
        res += line + "\n";
    }

    inputFile.close();
    return res;
}

void writeToFile(const std::string &path, const std::string &content) {
    std::ofstream outputFile(path);

    if (!outputFile.is_open()) {
        throw IOException("File could not be opened.");
    }

    outputFile << content << std::endl;

    if (outputFile.bad() || outputFile.fail()) {
        outputFile.close();
        throw IOException("File could not be written.");
    }

    outputFile.close();
}

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

std::string handleDeserializeCall() {
    std::cout << "Enter filename: ";
    const auto fileName = read<std::string>();
    auto serializer = CarSerializer(new CarTomlValidator());
    const Car c = serializer.deserialize(readFile(fileName));
    return "Deserialize Success:\n" + c.toString();
}

std::string handleSerializeCall() {
    std::cout << "Enter car brand: ";
    const auto brand = read<std::string>();
    std::cout << "Enter car owner: ";
    const auto owner = read<std::string>();
    std::cout << "Enter car mileage: ";
    const auto mileage = read<double>();
    std::cout << "Enter structure name: ";
    const auto name = read<std::string>();
    auto serializer = CarSerializer(new CarTomlValidator());
    const auto c = Car(brand, owner, mileage);
    return "Serialize Success:\n" + serializer.serialize(c, name);
}

std::string handleExit() {
    return "Exiting...";
}

struct ConsoleHandler {
    std::map<int, std::string (*)()> commands;
    bool isActive = true;

    FunctionCallResult operator()(const int &command) {
        const auto it = commands.find(command);
        if (it == commands.end()) {
            isActive = false;
            return FunctionCallResult(handleExit(), true);
        }

        try {
            return FunctionCallResult(commands[it->first](), true);
        } catch (const std::exception &e) {
            return FunctionCallResult(e.what(), false);
        }
    }

    void add(const int &command, std::string (*f)()) {
        this->commands[command] = f;
    }

    [[nodiscard]] bool active() const {
        return this->isActive;
    }
};

int main() {
    std::cout << "1 - serialize object." << std::endl;
    std::cout << "2 - deserialize object." << std::endl;
    std::cout << "Any other number - exit." << std::endl;

    ConsoleHandler handler;
    handler.add(1, handleSerializeCall);
    handler.add(2, handleDeserializeCall);

    while (handler.active()) {
        std::cout << "Enter command num: ";
        int command = 3;
        try {
            command = read<int>();
        } catch (const std::exception &e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }

        if (auto [message, success] = handler(command); success) {
            std::cout << message << std::endl;
        } else {
            std::cout << "Error happened: " << message << std::endl;
            std::cout << "Return to main menu." << std::endl;
        }
    }

    return 0;
}
