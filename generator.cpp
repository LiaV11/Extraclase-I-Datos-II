#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Generator {
public:
    Generator(size_t size, const std::string& outputPath)
        : size_(size), outputPath_(outputPath) {
        std::srand(std::time(nullptr)); // Semilla para números aleatorios
    }

    void generate() {
        std::ofstream file(outputPath_, std::ios::binary);
        if (!file) {
            std::cerr << "Error al abrir el archivo de salida." << std::endl;
            return;
        }

        for (size_t i = 0; i < size_; ++i) {
            int num = std::rand();
            file.write(reinterpret_cast<char*>(&num), sizeof(num));
        }

        file.close();
    }

private:
    size_t size_;
    std::string outputPath_;
};
