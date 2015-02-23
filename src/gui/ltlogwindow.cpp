#include "ltlogwindow.h"
#include "const/types.h"

Lt::LtLogWindow::LtLogWindow(QWidget *parent) : QPlainTextEdit(parent)
{
    QPlainTextEdit* logWindow = new QPlainTextEdit;

    logWindow->setReadOnly(true);
    logWindow->setPlainText("Test");
}

void Lt::LtLogWindow::logMessage(const QString &logMessage)
{
    this->insertPlainText(logMessage);
}
