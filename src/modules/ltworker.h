#ifndef WORKER_H
#define WORKER_H

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QMap>
#include <QString>
#include "modules/ltinterface.h"
#include "modules/ltsocket.h"
#include "http/http.h"

namespace Lt {

    class LtInterface;

    class LtWorker : public QThread
    {
        Q_OBJECT

    public:
        LtWorker(LtInterface* itfc = 0, QThread* parent = 0);
        virtual ~LtWorker();

        void startListening();

    public slots:
        void handleConnection();

    protected:
        void run();

    private:
        short workerId = 0;
        std::vector<int> clients;
        LtInterface* pItfc;
        LtSocket* sock;

        httpRequest* HandleInput(const int&);
        void HandleRequest(httpRequest*);
        std::string HandleDestination(const std::string&);
        httpResponse* MakeResponse(httpRequest*);
    };

}

#endif // WORKER_H
