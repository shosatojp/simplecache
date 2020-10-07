#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "entry.hpp"
#include "simple.hpp"
#include "structs.hpp"
#include "util.hpp"

int main(int argc, const char* argv[]) {
    std::string cache_dir;
    std::string key;
    std::string out_path;
    bool list = false;

    for (int i = 1; i < argc;) {
        if (!std::strcmp(argv[i], "--help") || !std::strcmp(argv[i], "-h")) {
            std::cout << "[usage]" << std::endl
                      << "simplecache [OPTIONS]" << std::endl
                      << "--list  -l      list all keys" << std::endl
                      << "--cache -c      cache directory (alternative environment variable: SIMPLECACHE_DIR)" << std::endl
                      << "--key   -k      key" << std::endl
                      << "--out   -o      output path" << std::endl;
            exit(0);
        } else if (!std::strcmp(argv[i], "--list") || !std::strcmp(argv[i], "-l")) {
            list = true;
            i++;
        } else if (!std::strcmp(argv[i], "--cache") || !std::strcmp(argv[i], "-c")) {
            cache_dir = argv[++i];
            i++;
        } else if (!std::strcmp(argv[i], "--key") || !std::strcmp(argv[i], "-k")) {
            key = argv[++i];
            i++;
        } else if (!std::strcmp(argv[i], "--out") || !std::strcmp(argv[i], "-o")) {
            out_path = argv[++i];
            i++;
        }
    }

    if (!cache_dir.size()) {
        char* dir = std::getenv("SIMPLECACHE_DIR");
        if (dir) {
            cache_dir = dir;
        } else {
            std::cerr << "Error: --cache required" << std::endl;
            exit(1);
        }
    }

    if (list) {
        SimpleCache cache{cache_dir};
        for (auto& pair : cache.index) {
            std::cout << pair.first << std::endl;
        }
        exit(0);
    }

    if (key.size() && out_path.size()) {
        // key-path
        SimpleCache cache{cache_dir};
        auto ff = cache.index.find(key);
        if (ff != cache.index.end()) {
            if (ff->second->save(out_path)) {
                exit(0);
            } else {
                exit(2);
            }
        } else {
            std::cout << "not found" << std::endl;
            exit(2);
        }
    } else {
        // from stdin
        // SimpleCache index{cache_dir};

        // std::string buf;
        // while (std::getline(std::cin, buf)) {
        //     std::string key, path;
        //     try {
        //         auto sep = std::find(buf.begin(), buf.end(), ' ');
        //         key = buf.substr(0, sep - buf.begin());
        //         path = buf.substr(sep - buf.begin() + 1, buf.size());
        //     } catch (...) {
        //         std::cout << "invalid input" << std::endl;
        //         exit(2);
        //     }

        //     try {
        //         SimpleCacheEntry ff = index.find(key);
        //         ff.save(path);
        //         std::cout << path << std::endl;
        //     } catch (const std::exception& e) {
        //         std::cout << "not found" << std::endl;
        //     }
        // }
        // exit(0);
    }
}