#include "http/http.h"
#include <iostream>
#include <cstring>
#include <sstream>

Lt::httpStream::httpStream()
{
    level = (stream_level) 0;
}

std::string Lt::httpRequest::formRequest() const
{
    std::string request;

    request = request_protocol + "://" + request_host + "/" + request_url;

    return request;
}

bool Lt::httpRequest::ParseLine(string *line)
{
    header_list list;

    if (*line == "\r\n") {
        if (stream.level != stream_level::empty_line) {
            stream.level++;
        }

        else {
            stream.level = stream_level::message_body;
        }
    }

    if (stream.level == stream_level::request_line) {
        request_line = *line;
        stream.level++;
        return true;
    }

    if (ScanHeaders(line, general_headers, list.general_headers)) {
        stream.level = stream_level::general_headers;
        return true;
    }

    if (ScanHeaders(line, request_headers, list.request_headers)) {
        stream.level = stream_level::request_headers;
        return true;
    }

    if (ScanHeaders(line, entity_headers, list.entity_headers)) {
        stream.level = stream_level::entity_headers;
        return true;
    }

    if (stream.level > stream_level::request_line) {
        message_body = *line;
        stream.level = stream_level::message_body;
        return true;
    }

    if (stream.level == stream_level::message_body) {
        message_trailers = *line;
        stream.level = stream_level::message_trailers;
        return false;
    }

    return false;
}

bool Lt::httpRequest::ScanHeaders(string *line, vector<header_entity> &headers_stock, const vector<string> &headers_search)
{
    header_entity header;
    std::string header_name;

    std::istringstream linestream(*line);

    getline(linestream, header_name, ':');
    for (unsigned int i = 0; i < headers_search.size(); i++) {
        if (header_name == headers_search[i]) {
            header.name = header_name;
            header.value = line->substr(headers_search[i].size() + 2, line->size() -1); // + 2 because we have format header:_ // - 1 because we don't need \r or \n

            if (headers_search[i].size() == header.name.size()) {
                headers_stock.push_back(header);
                return true;
            }
        }
    }

    return false;
}
