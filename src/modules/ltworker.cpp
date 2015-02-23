#include <string>
#include <sstream>
#include <pthread.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <iostream>
#include "modules/ltworker.h"
#include "const/types.h"
#include "http/http.h"

Lt::LtWorker::LtWorker(Lt::LtInterface* itfc, QThread* parent)
    :QThread(parent)
{
    setObjectName(this->metaObject()->className());
    pItfc = itfc;
}

Lt::LtWorker::~LtWorker()
{
    std::cout << "~LtWorker()" << std::endl;
}

void Lt::LtWorker::run()
{
    if (!pItfc->isListening) {
        this->startListening();
    }

    sock->startListening(pItfc->getAddr());
}

void Lt::LtWorker::handleConnection()
{

}

Lt::httpRequest* Lt::LtWorker::HandleInput(const int &cli_sock)
{
    httpRequest* request = new httpRequest;

    ssize_t rec_bytes = 0, total_bytes = 0;
    const int chunk_size = 512;
    char chunk[chunk_size + 1] = {'\0'};
    std::string data = "\0";

    while (true) {
        if ((rec_bytes = recv(cli_sock, &chunk, chunk_size, 0)) < chunk_size) {
            total_bytes += rec_bytes;
            data.append(chunk, 0, rec_bytes);
            break;
        }

        if (rec_bytes < 0) {
            perror(strerror(errno));
            break;
        }

        if (rec_bytes == 0) {
            break;
        }

        total_bytes += rec_bytes;
        data.append(chunk, 0, rec_bytes);
    }

    std::cout << data << std::endl;

    request->formRequest();
    HandleRequest(request);

    return request;
}

void Lt::LtWorker::HandleRequest(httpRequest *request)
{
    std::istringstream is;
    std::string token, data;

    is >> token;

    if (token == "GET") {
        request->setType(static_cast<int> (GET));
    }

    else {
        request->setType(static_cast<int> (POST));
    }

    is >> token >> token;

    data = HandleDestination(token);
}

std::string Lt::LtWorker::HandleDestination(const std::string &path)
{
    int fd;
    char *buf = {0};
    ssize_t bytes;
    struct stat file_stat;

    fd = open(path.c_str(), O_RDWR);

    if (stat(path.c_str(), &file_stat) < 0) {
        perror(strerror(errno));
    }

    bytes = read(fd, buf, file_stat.st_size);

    if (bytes == 0) {
        return "";
    }

    std::string data(buf);

    return data;
}

Lt::httpResponse* Lt::LtWorker::MakeResponse(httpRequest* request)
{
    (void) request;

    return 0;
}

void Lt::LtWorker::startListening()
{
    sock = new Lt::LtSocket;

    sock->startListening(pItfc->getAddr());
}
