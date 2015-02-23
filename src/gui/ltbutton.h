#ifndef LTBUTTON_H
#define LTBUTTON_H

#include <QObject>
#include <QPushButton>

namespace Lt {

    class LtButton : public QPushButton
    {
        Q_OBJECT

    public:
        LtButton(QWidget* parent = 0);
        LtButton(const QString& string, QWidget* parent = 0);
        ~LtButton();
    };

}

#endif // LTBUTTON_H
