#include <arpa/inet.h>
#include <iostream>
#include "modules/ltinterface.h"

Lt::LtInterface::LtInterface(const configOption& config_map, QObject* parent)
    :QObject(parent)
{
    setObjectName(this->metaObject()->className());
    cfgMap = config_map;

    maxclients = cfgMap["MaxClients"].toInt();
    clients = 0;

    timeout.tv_sec = 15;
    timeout.tv_usec = 0;

    bzero((char *) &interfaceAddress, sizeof(interfaceAddress));
    interfaceAddress.sin_family = AF_INET;
    inet_pton(AF_INET, cfgMap["Address"].toStdString().c_str(), &interfaceAddress.sin_addr);
    interfaceAddress.sin_port = htons(cfgMap["Port"].toInt());
}

Lt::LtInterface::~LtInterface()
{
    std::cout << "~LtInterface()" << std::endl;
}

void Lt::LtInterface::startListen()
{
    LtWorker* listen_thread = new LtWorker(this);

    emit(interfaceStarted(this));
    listen_thread->start();
}

void Lt::LtInterface::attachToCore(LtCore *ptr)
{
    pCore = ptr;
}

sockaddr_in Lt::LtInterface::getAddr()
{
    return interfaceAddress;
}

bool Lt::LtInterface::setConfig(const configOption& config_map)
{
    if (cfgMap.isEmpty()) {
        cfgMap = config_map;
    }

    else {
        return false;
    }

    return true;
}
