#include "entry.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "httpheader.hpp"

SimpleCacheEntry::SimpleCacheEntry(const std::string& __path) : __path(__path) {
    this->get_key();
}

std::string SimpleCacheEntry::get_key() const {
    std::ifstream ifs{this->__path};

    SimpleFileHeader h;
    ifs.read((char *)&h, sizeof(SimpleFileHeader));

    std::string key;
    key.resize(h.key_length);
    ifs.read(&key[0], h.key_length);

    ifs.close();

    return key;
}

HttpHeader SimpleCacheEntry::get_header() const {
    // read from back
    std::ifstream ifs{this->__path};

    // stream 0 eof
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
    SimpleFileEOF eof0;
    ifs.read((char *)&eof0, sizeof(SimpleFileEOF));
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);

    if (eof0.flags & SimpleFileEOF::FLAG_HAS_KEY_SHA256) {
        // skip sha256
        ifs.seekg(-32, std::ios::cur);
    }

    // stream 0 data
    ifs.seekg(-(long)eof0.stream_size, std::ios::cur);

    SimpleMeta meta;
    // std::streampos stream_0_start = ifs.tellg();
    ifs.read((char *)&meta, sizeof(SimpleMeta));
    std::string buf(meta.header_size, '\0');
    ifs.read(&buf[0], meta.header_size);
    // ifs.seekg(stream_0_start);
    ifs.close();

    // parse header
    HttpHeader h;

    size_t start = 0;
    while (buf[start] != '\0') {
        size_t end = buf.find_first_of('\0', start);

        if (start == 0) {
            h.status_source = buf.substr(start, end - start + 1);
        } else {
            size_t coron = buf.find_first_of(':', start);
            auto key = buf.substr(start, coron - start);
            std::transform(key.begin(), key.end(), key.begin(), [](char c) {
                return std::tolower(c);
            });
            auto value = buf.substr(coron + 1, end - 1 - coron);
            h.headers[key] = value;
        }

        start = end + 1;
    }

    return h;
}

std::unique_ptr<std::vector<char>> SimpleCacheEntry::get_data() const {
    // read from back
    std::ifstream ifs{this->__path};

    // stream 0 eof
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
    SimpleFileEOF eof0;
    ifs.read((char *)&eof0, sizeof(SimpleFileEOF));
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);

    if (eof0.flags & SimpleFileEOF::FLAG_HAS_KEY_SHA256) {
        // skip sha256
        ifs.seekg(-32, std::ios::cur);
    }

    // stream 0 data
    ifs.seekg(-(long)eof0.stream_size, std::ios::cur);

    // stream 1 eof
    SimpleFileEOF eof1;
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::cur);
    ifs.read((char *)&eof1, sizeof(SimpleFileEOF));
    ifs.seekg(-sizeof(SimpleFileEOF), std::ios::cur);

    // stream 1 data
    ifs.seekg(-(long)eof1.stream_size, std::ios::cur);
    auto ptr = std::unique_ptr<std::vector<char>>(new std::vector<char>(eof1.stream_size));
    if (eof1.stream_size > 0) {
        ifs.read(&ptr->at(0), eof1.stream_size);
    }
    ifs.close();

    return ptr;
}

bool SimpleCacheEntry::save(const std::string& __path) const {
    auto ptr = this->get_data();

    if (ptr->size() > 0) {
        std::ofstream ofs{__path, std::ios::binary};
        ofs.write(&ptr->at(0), ptr->size());
        ofs.close();
        return true;
    } else {
        return false;
    }
}
