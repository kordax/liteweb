#ifndef CORE_H
#define CORE_H

#include "gui/ltmainwindow.h"
#include "modules/ltinterface.h"
#include "const/types.h"
#include "vector"
#include <error.h>
#include <errno.h>

namespace Lt {

    class LtInterface;
    class LtMainWindow;

    class LtCore : public QObject
    {
        Q_OBJECT

    public:
        explicit LtCore(QObject* parent = 0);
        virtual ~LtCore();

        bool setConfig(const configOption&, unsigned short);
        void attachInterface(LtInterface*);
        bool setMainWindow(LtMainWindow* = 0);

    public slots:
        void coreStart(const configOption& configMap);

    private:
        unsigned short numOfItfc = 0;

        std::vector<LtInterface*> itfcList;
        LtMainWindow* mainWindow;
    };

}

#endif
