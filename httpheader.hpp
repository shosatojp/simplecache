#pragma once

#include <string>
#include <unordered_map>

class HttpHeader {
   public:
    HttpHeader() = default;
    int status_code;
    std::string status_source;
    std::string status_message;
    std::string protocol;
    std::unordered_map<std::string, std::string> headers;
    bool is_gzipped();
};
