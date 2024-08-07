#include "PagedArray.h"
#include <fstream>

PagedArray::PagedArray(const std::string& filePath, size_t elementCount)
    : filePath_(filePath), elementCount_(elementCount), pageSize_(1024), pages_(4), pageLoaded_(4, false) {}

int& PagedArray::operator[](size_t index) {
    if (index >= elementCount_) {
        throw std::out_of_range("Index out of range");
    }

    size_t pageIndex = index / pageSize_;
    size_t pageOffset = index % pageSize_;
    if (!pageLoaded_[pageIndex % 4]) {
        loadPage(pageIndex);
    }
    return pages_[pageIndex % 4][pageOffset];
}

void PagedArray::loadPage(size_t pageIndex) {
    size_t offset = pageIndex * pageSize_ * sizeof(int);
    std::ifstream file(filePath_, std::ios::binary);
    file.seekg(offset);
    file.read(reinterpret_cast<char*>(pages_[pageIndex % 4].data()), pageSize_ * sizeof(int));
    file.close();
    pageLoaded_[pageIndex % 4] = true;
}
