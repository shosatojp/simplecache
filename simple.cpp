#include "simple.hpp"

#include <iostream>
#include <string>

#include "entry.hpp"

SimpleCache::SimpleCache(std::string __cache_dir) {
    for (const auto& file : fs::directory_iterator(__cache_dir)) {
        std::string path = file.path();
        if (path.ends_with("_0")) {
            const auto e = SimpleCacheEntry(file.path());
            index[e.get_key()] = std::make_unique<SimpleCacheEntry>(e);
        }
    }
}
