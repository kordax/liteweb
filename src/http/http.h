#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <vector>
#include "const/headers.h"

namespace Lt {

    enum request_protocol { http, https };

    enum request_type { GET, POST };

    enum stream_level {
        request_line,
        general_headers,
        request_headers,
        entity_headers,
        empty_line,
        message_body,
        message_trailers
    };

    class httpStream {
    public:
        httpStream();
        ~httpStream();

        int level;
    };

    struct httpEntity {
    public:
        std::string request_line;
        std::vector<header_entity> general_headers;
        std::vector<header_entity> request_headers;
        std::vector<header_entity> entity_headers;
        std::string message_body;
        std::string message_trailers;
    };

    class httpRequest : public httpEntity {
    public:
        std::string formRequest() const;
        void setType(const int &type) { request_type = type; }
        void setLength(const int &len) { request_len = len; }
        int getType() { return request_type; }
        int getLength() { return request_len; }

    private:
        bool ScanHeaders(std::string *line, std::vector<header_entity> &, const std::vector<string> &);
        bool ParseLine(std::string *);

        std::string request_protocol;
        std::string request_host;
        std::string request_url;
        int request_type;
        int request_len;

        httpStream stream;
        unsigned int status;
    };

    class httpResponse : public httpEntity {
    private:
        int response_len;
    };

}

#endif // HTTP_H

