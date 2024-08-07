#ifndef PAGED_ARRAY_H
#define PAGED_ARRAY_H

#include <fstream>
#include <vector>
#include <array>
#include <stdexcept>

class PagedArray {
public:
    PagedArray(const std::string& filePath, size_t elementCount);

    int& operator[](size_t index);
    size_t size() const { return elementCount_; }

private:
    void loadPage(size_t pageIndex);

    std::string filePath_;
    size_t elementCount_;
    size_t pageSize_;
    std::vector<std::array<int, 1024>> pages_;
    std::vector<bool> pageLoaded_;
};

#endif 
