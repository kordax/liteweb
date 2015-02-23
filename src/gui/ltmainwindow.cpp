#include <QWidget>
#include "ltmainwindow.h"
#include <string>
#include <typeinfo>

Lt::LtMainWindow::LtMainWindow(QWidget *parent) : QWidget(parent)
{
    setObjectName("Lt Main Window");

    std::string ip = "127.0.0.1";
    QSize appSize(640, 480);
    pCore = new (std::nothrow) LtCore();

    if (pCore == NULL) {
        qDebug("pCore creation error");
    }

    logWindow     = new QPlainTextEdit;
    logWindow->setObjectName("Log Console");

    mainLayout  = new QGridLayout;
    mainLayout->setObjectName("Main Layout");

    rMenu       = new QVBoxLayout;
    rMenu->setObjectName("Right Menu");

    rSubMenu    = new QHBoxLayout;
    rSubMenu->setObjectName("Right Submenu");

    ipLabel     = new QLabel("IP Address: ");
    ipLabel->setObjectName("IP Address Label");

    ipLine      = new QLineEdit;
    ipLine->setObjectName("IP Input Line");

    portLabel   = new QLabel("Port: ");
    portLabel->setObjectName("Port Label");

    portLine    = new QLineEdit;
    portLine->setObjectName("Port Input Line");

    mainLayout  = new QGridLayout;
    mainLayout->setObjectName("Main Layout");

    startButton = new LtButton("Start");
    startButton->setObjectName("Start Button");

    stopButton  = new LtButton("Stop");
    stopButton->setObjectName("Stop Button");

    addOption(*ipLine);
    addOption(*portLine);

    if (!QObject::connect(startButton, SIGNAL(pressed()), this, SLOT(onStart()))) {
        qDebug("%s: connection error", qPrintable(startButton->objectName()));
    }

    if (!QObject::connect(this, SIGNAL(doCoreStart(const configOption&)), pCore, SLOT(coreStart(const configOption&)))) {
        qDebug("%s: connection error", qPrintable(this->objectName()));
    }

    rSubMenu->addWidget(startButton);
    rSubMenu->addWidget(stopButton);
    rSubMenu->setSpacing(10);
    rSubMenu->setMargin(4);

    startButton->setGeometry(0, 0, 40, 10);
    startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    startButton->setEnabled(false);
    stopButton->setGeometry(0, 0, 40, 10);
    stopButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    stopButton->setEnabled(false);

    portLine->setMaxLength(5);
    portLine->setText(0);

    this->setFixedSize(appSize);

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnMinimumWidth(1, 200);

    rMenu->addWidget(ipLabel, 0);
    rMenu->addWidget(ipLine, 0);
    rMenu->addWidget(portLabel, 0);
    rMenu->addWidget(portLine, 0);
    rMenu->addLayout(rSubMenu);
    rMenu->setSpacing(2);
    rMenu->setMargin(2);

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    logWindow->setReadOnly(true);

    mainLayout->addWidget(logWindow, 0, 0);
    mainLayout->addLayout(rMenu, 0, 1, Qt::AlignTop | Qt::AlignRight);

    mainLayout->setSpacing(4);
    mainLayout->setMargin(2);

    this->setLayout(mainLayout);
}

Lt::LtMainWindow::~LtMainWindow()
{
    if (pCore != NULL) {
        delete pCore;
    }
}

void Lt::LtMainWindow::onStart()
{
    qDebug("%s: onStart()", qPrintable(this->objectName()));

    configOption config = makeConfig();
    pCore->setMainWindow(this);

    emit doCoreStart(config);

    QPushButton* button = qobject_cast<QPushButton*> (sender());

    button->setEnabled(false);
    button->setText("Running");
}

void Lt::LtMainWindow::onTextChanged(const QString& text)
{
    if (text.isEmpty()) {
        return;
    }

    if (!ipLine->text().isEmpty() && !portLine->text().isEmpty()) {
        startButton->setEnabled(true);
    }

    else {
        startButton->setEnabled(false);
    }
}

void Lt::LtMainWindow::addOption(QLineEdit& option)
{
    optionsList.push_back(&option);

    if (!QObject::connect(&option, SIGNAL(textEdited(QString)), this, SLOT(onTextChanged(const QString&)))) {
        qDebug("%s: connection error", qPrintable(ipLine->objectName()));
    }
}

void Lt::LtMainWindow::onInterfaceStarted(Lt::LtInterface* interface)
{
    stopButton->setEnabled(true);
    startButton->setEnabled(false);
}

Lt::configOption Lt::LtMainWindow::makeConfig()
{
    Lt::configOption tempCfg;
    QString ipAddr;

    tempCfg.insert("Address", ipLine->text());
    tempCfg.insert("Port", portLine->text());

    return tempCfg;
}
