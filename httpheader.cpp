#include "httpheader.hpp"

bool HttpHeader::is_gzipped() {
    return this->headers.count("content-encoding") != 0 && headers["content-encoding"] == "gzip";
}