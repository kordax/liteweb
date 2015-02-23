#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <string>
#include <netinet/in.h>

namespace Lt {

    class LtSocket
    {
    public:
        LtSocket(LtSocket* parent_sock = 0);
        ~LtSocket();

        LtSocket* pSocket;

        bool startListening(const sockaddr_in&);
        bool acceptConnection();
        bool declineConnection(const std::string& data);
        std::string receiveData();
        bool sendData(std::string* data);

    private:
        int sd = 0;
        int childSd = 0;

        sockaddr cliAddr;
        socklen_t addrLen = sizeof(cliAddr);
    };

}

#endif // SOCKET_H
