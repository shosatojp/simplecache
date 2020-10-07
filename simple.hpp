#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "httpheader.hpp"
#include "structs.hpp"
namespace fs = std::filesystem;

class SimpleCacheEntry {
   public:
    SimpleCacheEntry(std::string __path);
    std::string __path;

    HttpHeader get_header() const;
    std::unique_ptr<std::vector<char>> get_data() const;
    std::string get_key() const;
    bool save(std::string __path) const;

   private:
};