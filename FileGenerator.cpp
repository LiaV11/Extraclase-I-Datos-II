#include "FileGenerator.h"
#include <fstream>
#include <random>
#include <stdexcept>
#include <limits>

FileGenerator::FileGenerator(Size size, const std::string& outputPath)
    : size(size), outputPath(outputPath) {}

void FileGenerator::generate() const {
    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Cannot open output file");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    size_t numIntegers = getSizeInBytes() / sizeof(int);
    for (size_t i = 0; i < numIntegers; ++i) {
        int randomValue = dis(gen);
        outputFile.write(reinterpret_cast<char*>(&randomValue), sizeof(int));
    }

    outputFile.close();
}

size_t FileGenerator::getSizeInBytes() const {
    switch (size) {
        case SMALL:
            return 512 * 1024 * 1024; // 512 MB
        case MEDIUM:
            return 1024 * 1024 * 1024; // 1 GB
        case LARGE:
            return 2 * 1024 * 1024 * 1024; // 2 GB
        default:
            throw std::invalid_argument("Unknown size");
    }
}
