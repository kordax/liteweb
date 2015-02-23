#ifndef LTLOGWINDOW_H
#define LTLOGWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>

namespace Lt {

class LtLogWindow : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LtLogWindow(QWidget *parent = 0);

signals:

public slots:
    void logMessage(const QString &);
};

}

#endif // LTLOGWINDOW_H
