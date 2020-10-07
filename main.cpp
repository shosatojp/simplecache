#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "simple.hpp"
#include "structs.hpp"
#include "util.hpp"

int main() {
    std::string dir = "/home/sho/.cache/google-chrome/Default/Cache/";
    for (const auto& file : fs::directory_iterator(dir)) {
        std::string path = file.path();
        if (path.ends_with("_0")) {
            const auto e = SimpleCacheEntry(file.path());
            std::cout << e.get_key() << std::endl;

            e.save("hoge.jpg");
        }
    }
}
