#include "simple.hpp"

#include <iostream>
#include <string>

#include "entry.hpp"

bool ends_with(const std::string& src, const std::string& suffix) {
    auto srclen = src.length(),
         suffiexlen = suffix.length();
    return srclen >= suffiexlen &&
           src.compare(srclen - suffiexlen, suffiexlen, suffix) == 0;
}

SimpleCache::SimpleCache(const std::string& __cache_dir) {
    for (const auto& file : fs::directory_iterator(__cache_dir)) {
        std::string path = file.path();
        if (ends_with(path, "_0")) {
            const auto e = new SimpleCacheEntry(file.path());
            index[e->get_key()] = std::unique_ptr<SimpleCacheEntry>(e);
        }
    }
}
