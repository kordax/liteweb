#ifndef HEADERS_H
#define HEADERS_H

#include <vector>
#include <string>

using std::vector;
using std::string;

struct header_list {
    vector<string> general_headers =
    {
        "Cache-Control",
        "Connection",
        "Date",
        "Pragma",
        "Trailer",
        "Transfer-Encoding",
        "Upgrade",
        "Via",
        "Warning"
    };
    vector<string> request_headers =
    {
        "Accept",
        "Accept-Charset",
        "Accept-Encoding",
        "Accept-Language",
        "Authorization",
        "Expect",
        "From",
        "Host",
        "If-Match",
        "If-Modified-Since",
        "If-None-Match",
        "If-Range",
        "If-Unmodified-Since",
        "Max-Forwards",
        "Proxy-Authorization",
        "Range",
        "Referer",
        "TE",
        "User-Agent"
    };
    vector<string> entity_headers =
    {
        "Allow",
        "Content-Encoding",
        "Content-Language",
        "Content-Length",
        "Content-Location",
        "Content-MD5",
        "Content-Range",
        "Content-Type",
        "Expires",
        "Last-Modified",
        "extension-header"
    };
};

struct header_entity {
    string name;
    string value;
};

#endif // HEADERS_H

