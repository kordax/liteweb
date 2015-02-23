#include "ltrootwindow.h"
#include "const/messages.h"
#include <QSizePolicy>

Lt::LtRootWindow::LtRootWindow(QWidget *parent) :QMessageBox(parent)
{
    this->setText(QString(LT_NO_ROOT));
}

Lt::LtRootWindow::~LtRootWindow()
{

}
