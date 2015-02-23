#ifndef LTMAINWINDOW_H
#define LTMAINWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "gui/ltbutton.h"
#include "const/types.h"
#include "modules/ltcore.h"
#include "modules/ltinterface.h"

namespace Lt {

    class LtCore;
    class LtInterface;

    class LtMainWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit LtMainWindow(QWidget *parent = 0);
        virtual ~LtMainWindow();

        Lt::configOption makeConfig();

    public slots:
        void onStart();
        void onTextChanged(const QString&);
        void onInterfaceStarted(Lt::LtInterface*);

    signals:
        void doCoreStart(const configOption&);

    private:
        void addOption(QLineEdit&);

        LtCore* pCore = NULL;

        QToolBar* toolbar;
        QPlainTextEdit* logWindow;
        QVBoxLayout* rMenu;
        QHBoxLayout* rSubMenu;
        QLabel* ipLabel;
        QLineEdit* ipLine;
        QLabel* portLabel;
        QLineEdit* portLine;
        QGridLayout* mainLayout;
        LtButton* startButton;
        LtButton* stopButton;

        QList<LtInterface*> interfacesList;
        QList<QLineEdit*> optionsList;
    };

}

#endif // LTMAINWINDOW_H
