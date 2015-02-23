#include <QtCore/QtGlobal>

#ifndef LT_INTERFACE_H
#define LT_INTERFACE_H

#if defined(LTINTERFACE_LIBRARY)
#  define LTINTERFACE_EXPORT Q_DECL_EXPORT
#else
#  define LTINTERFACE_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <netinet/in.h>
#include "modules/ltcore.h"
#include "modules/ltsocket.h"
#include "const/types.h"
#include "modules/ltworker.h"

namespace Lt {

    class LtCore;
    class LtSocket;
    class LtWorker;

    class LtInterface : public QObject
    {
        Q_OBJECT

    public:
        explicit LtInterface(const configOption& confMap = configOption(), QObject* parent = 0);
        virtual ~LtInterface();

        void attachToCore(LtCore*);
        bool setConfig(const configOption&);
        sockaddr_in getAddr();
        bool isListening = false;

    public slots:
        void startListen();

    signals:
        void interfaceStarted(Lt::LtInterface*);

    private:
        int maxclients;
        int clients;
        int interfaceSocket;
        int port;
        struct timeval timeout;
        struct sockaddr_in interfaceAddress;
        LtCore* pCore;
        LtSocket pSocket;
        configOption cfgMap;
        std::vector<LtWorker*> wrkList;
    };

}

#endif // LT_INTERFACE_H
