#include <iostream>
#include "modules/ltcore.h"
#include "gui/ltmainwindow.h"

Lt::LtCore::LtCore(QObject* parent)
    :QObject(parent)
{
    setObjectName(this->metaObject()->className());
}

Lt::LtCore::~LtCore()
{
    std::cout << "~LtCore()" << std::endl;
}

void Lt::LtCore::attachInterface(Lt::LtInterface* interface)
{
    interface->attachToCore(this);
    itfcList.push_back(interface);
    numOfItfc++;
}

bool Lt::LtCore::setMainWindow(Lt::LtMainWindow* mainWindow)
{
    this->mainWindow = mainWindow;

    return true;
}

bool Lt::LtCore::setConfig(const Lt::configOption& configMap, unsigned short itfcNum)
{
    if (!itfcList[itfcNum]->setConfig(configMap)) {
        return false;
    }

    return true;
}

void Lt::LtCore::coreStart(const Lt::configOption& config_map)
{
    qDebug("%s: start()", qPrintable(this->objectName()));

    Lt::LtInterface* itfc = new Lt::LtInterface(config_map);
    if (!QObject::connect(itfc, SIGNAL(interfaceStarted(Lt::LtInterface*)), this->mainWindow, SLOT(onInterfaceStarted(Lt::LtInterface*)))) {
        qDebug("%s: connection error", qPrintable(itfc->objectName()));
    }
    attachInterface(itfc);

    itfc->startListen();
}
