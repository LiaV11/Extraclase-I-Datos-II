#include <iostream>
#include <string>
#include "FileGenerator.h"

FileGenerator::Size parseSize(const std::string& sizeArg) {
    if (sizeArg == "SMALL") {
        return FileGenerator::SMALL;
    } else if (sizeArg == "MEDIUM") {
        return FileGenerator::MEDIUM;
    } else if (sizeArg == "LARGE") {
        return FileGenerator::LARGE;
    } else {
        throw std::invalid_argument("Unknown size: " + sizeArg);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    std::string sizeArg, outputFilePath;
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "-size") {
            sizeArg = argv[i + 1];
        } else if (arg == "-output") {
            outputFilePath = argv[i + 1];
        }
    }

    try {
        FileGenerator::Size size = parseSize(sizeArg);
        FileGenerator generator(size, outputFilePath);
        generator.generate();
        std::cout << "File generated successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
