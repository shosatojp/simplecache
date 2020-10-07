#pragma once
#include <cstdint>

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

struct SimpleMeta {
    uint32_t info_size;
    uint32_t flags;
    uint64_t request_time;
    uint64_t response_time;
    uint32_t header_size;
} __attribute__((__packed__));

