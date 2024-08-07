#include <getopt.h> // Para el manejo de opciones de línea de comandos
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    size_t size = 0;
    std::string outputPath;

    int opt;
    while ((opt = getopt(argc, argv, "s:o:")) != -1) {
        switch (opt) {
            case 's':
                if (std::string(optarg) == "SMALL") size = 512 * 1024 * 1024 / sizeof(int);
                else if (std::string(optarg) == "MEDIUM") size = 1024 * 1024 * 1024 / sizeof(int);
                else if (std::string(optarg) == "LARGE") size = 2 * 1024 * 1024 * 1024 / sizeof(int);
                break;
            case 'o':
                outputPath = optarg;
                break;
            default:
                std::cerr << "Uso: generator -s SIZE -o OUTPUT_FILE" << std::endl;
                return 1;
        }
    }

    Generator generator(size, outputPath);
    generator.generate();

    return 0;
}
