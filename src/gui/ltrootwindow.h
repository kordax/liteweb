#ifndef LTROOTLOGINWINDOW_H
#define LTROOTLOGINWINDOW_H

#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QInputDialog>

namespace Lt
{
    class LtRootWindow : public QMessageBox
    {
        Q_OBJECT

    public:
        explicit LtRootWindow(QWidget *parent = 0);
        ~LtRootWindow();
    };
}

#endif // LTROOTLOGINWINDOW_H
