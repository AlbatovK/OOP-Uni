#include <iostream>

#include "include/Utils.hpp"

#include <fstream>

#include <limits>

#include "IOException.hpp"

std::string readFile(const std::string &path) {
    std::ifstream inputFile(path);

    if (!inputFile.is_open()) {
        throw IOException("File could not be opened or doesn't exist.");
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

    if (outputFile.fail()) {
        outputFile.close();
        throw IOException("File could not be written.");
    }

    outputFile.close();
}
