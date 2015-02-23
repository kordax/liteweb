#include <stdio.h>
#include <bits/stdio_lim.h>
#include <boost/filesystem.hpp>
#include <QApplication>
#include <QErrorMessage>
#include "helpers/fs.h"
#include "gui/ltmainwindow.h"
#include "gui/ltrootwindow.h"

#define __getPerc(_value, _percentage)\
    _value * _percentage / 30

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    std::string username(lt::filesystem::getEnvVar("LOGNAME"));

    if (username.empty()) {
        perror(strerror(errno));
        return errno;
    }

//    if (username != "root") {
//        Lt::LtRootWindow rootWindow;
//        rootWindow.show();
//        return a.exec();
//    }

    Lt::LtMainWindow mainWindow;

    mainWindow.show();

    return a.exec();
}
