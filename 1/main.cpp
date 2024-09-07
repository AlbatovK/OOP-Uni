#include <iostream>

#include <fstream>

#include <string>

#include "src/include/Car.hpp"

#include "src/include/CarSerializer.hpp"

#include "src/include/CarTomlValidator.hpp"

#include "src/include/ValidationException.hpp"

#include "src/include/IOException.hpp"

std::string readFile(const std::string &path) {
    std::ifstream inputFile(path);

    if (!inputFile.is_open()) {
        throw IOException("File could not be opened.");
    }

    std::string res;
    std::string line;
    while (getline(inputFile, line)) {
        res += line + "\n";
    }

    inputFile.close();
    return res;
}

int main() {
    CarSerializer s = CarSerializer(new CarTomlValidator());
    try {
        std::string filename;
        getline(std::cin, filename);
        Car c = s.deserialize(readFile(filename));\
        std::cout << "Successfully deserialized!" << std::endl;
        std::cout << "Serializing back: " << std::endl;
        std::cout << s.serialize(c, "name") << std::endl;
    } catch (const ValidationException &e) {
        std::cout << "ValidationException:\n" << e.getMessage() << std::endl;
    } catch (const IOException &e) {
        std::cout << "IOException:\n" << e.getMessage() << std::endl;
    }
    return 0;
}
