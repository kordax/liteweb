#ifndef LTLINEEDIT_H
#define LTLINEEDIT_H

#include <QObject>
#include <QLineEdit>

namespace Lt {

    class LtLineEdit : public QLineEdit
    {
        Q_OBJECT

    public:
        LtLineEdit(const QString& string, QWidget* parent = 0);
        ~LtLineEdit();

    public slots:
        void onStart();

    signals:
        void sendData();
    };

}

#endif // LTLINEEDIT_H
