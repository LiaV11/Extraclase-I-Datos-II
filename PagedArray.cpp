#include <fstream>
#include <vector>
#include <unordered_map>

class PagedArray {
public:
    PagedArray(const std::string& filePath, size_t elementCount)
        : filePath_(filePath), elementCount_(elementCount), pageSize_(1024 * 1024 / sizeof(int)) {
        pages_.resize(4); // 4 páginas
        pageLoaded_.resize(4, false);
    }

    int& operator[](size_t index) {
        size_t pageIndex = index / pageSize_;
        size_t pageOffset = index % pageSize_;
        if (!pageLoaded_[pageIndex % 4]) {
            loadPage(pageIndex);
        }
        return pages_[pageIndex % 4][pageOffset];
    }

private:
    void loadPage(size_t pageIndex) {
        size_t offset = pageIndex * pageSize_ * sizeof(int);
        std::ifstream file(filePath_, std::ios::binary);
        file.seekg(offset);
        file.read(reinterpret_cast<char*>(pages_[pageIndex % 4].data()), pageSize_ * sizeof(int));
        file.close();
        pageLoaded_[pageIndex % 4] = true;
    }

    std::string filePath_;
    size_t elementCount_;
    size_t pageSize_;
    std::vector<std::array<int, 1024>> pages_;
    std::vector<bool> pageLoaded_;
};
