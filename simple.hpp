#include <memory>
#include <string>

#include "entry.hpp"

class SimpleCache {
   public:
    SimpleCache(const std::string& __cache_dir);
    SimpleCacheEntry find(const std::string&) const;

//    private:
    std::unordered_map<std::string, std::unique_ptr<SimpleCacheEntry>> index;
};