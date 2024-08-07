#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

enum Size { SMALL, MEDIUM, LARGE };

size_t getSize(Size size) {
    switch (size) {
        case SMALL: return 512 * 1024 * 1024;  // 512 MB
        case MEDIUM: return 1 * 1024 * 1024 * 1024;  // 1 GB
        case LARGE: return 2 * 1024 * 1024 * 1024;  // 2 GB
        default: return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: generator –size <SIZE> -output <OUTPUT FILE PATH>\n";
        return 1;
    }

    Size size;
    std::string sizeArg = argv[1];
    if (sizeArg == "SMALL") size = SMALL;
    else if (sizeArg == "MEDIUM") size = MEDIUM;
    else if (sizeArg == "LARGE") size = LARGE;
    else {
        std::cerr << "Invalid size argument\n";
        return 1;
    }

    std::string outputFilePath = argv[3];
    size_t fileSize = getSize(size);
    size_t numInts = fileSize / sizeof(int);

    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open output file\n";
        return 1;
    }

    std::srand(std::time(nullptr));
    for (size_t i = 0; i < numInts; ++i) {
        int randomInt = std::rand();
        outFile.write(reinterpret_cast<char*>(&randomInt), sizeof(int));
    }

    outFile.close();
    return 0;
}
