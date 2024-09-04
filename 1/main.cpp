#include <iostream>

#include <fstream>

#include <string>

#include "Car.hpp"

#include "CarSerializer.hpp"

#include "CarTomlValidator.hpp"

#include "ValidationException.hpp"

#include "IOException.hpp"

std::string readFile(const std::string& path) {
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
        Car c = s.deserialize(readFile(filename));
        std::cout << c.getMileage() << std::endl;
        std::cout << s.serialize(c, "name") << std::endl; 
    } catch (ValidationException e) {
        std::cout << "ValidationException:\n" << e.getMessage() << std::endl;
    } catch (IOException e) {
    	std::cout << "IOException:\n" << e.getMessage() << std::endl;
    }
    return 0;
}
