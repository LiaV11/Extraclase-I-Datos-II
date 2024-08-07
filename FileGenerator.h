#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <string>

class FileGenerator {
public:
    enum Size { SMALL, MEDIUM, LARGE };

    FileGenerator(Size size, const std::string& outputPath);
    void generate() const;

private:
    Size size;
    std::string outputPath;

    size_t getSizeInBytes() const;
};

#endif // FILE_GENERATOR_H
