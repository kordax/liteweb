#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "modules/ltsocket.h"

Lt::LtSocket::LtSocket(Lt::LtSocket* parent_sock)
{
    pSocket = parent_sock;
    sd = socket(AF_INET, SOCK_STREAM, 0);
}

Lt::LtSocket::~LtSocket()
{
    std::cout << "~LtSocket()" << std::endl;
}

bool Lt::LtSocket::startListening(const sockaddr_in& interface_address)
{
    sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd < 0) {
        perror(strerror(errno));
        return false;
    }

    if (bind(sd, (sockaddr*) &interface_address, sizeof(sockaddr)) < 0) {
        perror(strerror(errno));
        return false;
    }

    if (listen(sd, 30) < 0) {
        perror(strerror(errno));
        return false;
    }

    std::cout << "Successfully listening!" << std::endl;

    return false;
}

bool Lt::LtSocket::acceptConnection()
{
    childSd = accept(sd, (sockaddr*) &cliAddr, &addrLen);

    struct timeval timeout;

    int cliFlags = fcntl(childSd, F_GETFL);

    timeout.tv_sec = 30;
    timeout.tv_usec = 0;

    if (setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout)) < 0) {
        perror(strerror(errno));
        return false;
    }

    if (fcntl(sd, F_SETFL, cliFlags | O_NONBLOCK) < 0) {
        perror(strerror(errno));
        return false;
    }

    if (sd < 0) { // Не удалось установить соединение
        perror(strerror(errno));
        return false;
    }

    return true;
}

bool Lt::LtSocket::declineConnection(const std::string& data)
{
    (void) data;

    return true;
}

std::string Lt::LtSocket::receiveData()
{
    ssize_t rec_bytes = 0, total_bytes = 0;
    const int chunk_size = 512;
    char chunk[chunk_size + 1] = {'\0'};
    std::string data = NULL;

    while (true) {
        if ((rec_bytes = recv(childSd, &chunk, chunk_size, 0)) < chunk_size) {
            total_bytes += rec_bytes;
            data.append(chunk, 0, rec_bytes);
            return data;
        }

        if (rec_bytes < 0) {
            perror(strerror(errno));
            return data;
        }

        if (rec_bytes == 0) {
            return data;
        }

        total_bytes += rec_bytes;
        data.append(chunk, 0, rec_bytes);
    }

    return data;
}

