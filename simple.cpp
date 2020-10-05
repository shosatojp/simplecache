#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://github.com/chromium/chromium/blob/master/net/disk_cache/simple/simple_entry_format.h

struct SimpleFileHeader {
    SimpleFileHeader() = default;

    uint64_t initial_magic_number;
    uint32_t version;
    uint32_t key_length;
    uint32_t key_hash;
};

struct SimpleFileEOF {
    enum Flags {
        FLAG_HAS_CRC32 = (1U << 0),
        FLAG_HAS_KEY_SHA256 = (1U << 1),  // Preceding the record if present.
    };

    SimpleFileEOF() = default;

    uint64_t final_magic_number;
    uint32_t flags;
    uint32_t data_crc32;
    // |stream_size| is only used in the EOF record for stream 0.
    uint32_t stream_size;
};

// SimpleFileHeader::SimpleFileHeader(){};

int main() {
    std::string path = "/home/sho/.cache/google-chrome/Default/Cache/fab7b15df35ff409_0";
    {
        std::ifstream ifs{path};

        SimpleFileHeader h;
        ifs.read((char *)&h, sizeof(SimpleFileHeader));

        std::string key;
        key.resize(h.key_length);
        ifs.read(&key[0], h.key_length);

        std::cout << key << std::endl;

        ifs.close();
    }
    {
        // 後ろから読む
        std::ifstream ifs{path};

        ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
        SimpleFileEOF eof0;
        ifs.read((char *)&eof0, sizeof(SimpleFileEOF));
        ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
        std::cout << eof0.stream_size << std::endl;
        if (eof0.flags && SimpleFileEOF::FLAG_HAS_KEY_SHA256) {
            ifs.seekg(-32, std::ios::cur);
        }

        ifs.seekg(-(long)eof0.stream_size, std::ios::cur);
        std::string buf(eof0.stream_size, '\0');
        ifs.read(&buf[0], eof0.stream_size);
        ifs.seekg(-(long)eof0.stream_size, std::ios::cur);
        // std::cout << "hoge" << std::endl;

        // std::cout << buf << std::endl;
        SimpleFileEOF eof1;
        ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
        ifs.read((char *)&eof1, sizeof(SimpleFileEOF));
        ifs.seekg(-sizeof(SimpleFileEOF), std::ios::end);
        std::cout << eof1.stream_size << std::endl;
        ifs.close();

        // std::ofstream ofs{"out.txt", std::ios::binary};
        // ofs << buf;
        // ofs.close();
        // ofs.write(buf.begin())
    }
}