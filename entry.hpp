#pragma once

#include <experimental/filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "httpheader.hpp"
#include "structs.hpp"
namespace fs = std::experimental::filesystem;

class SimpleCacheEntry {
   public:
    SimpleCacheEntry(const std::string& __path);
    std::string __path;

    HttpHeader get_header() const;
    std::unique_ptr<std::vector<char>> get_data() const;
    std::vector<char> get_data_copy() const;
    std::string get_key() const;
    bool save(const std::string& __path) const;

   private:
};