#ifndef LTLABEL_H
#define LTLABEL_H

#include <QObject>
#include <QLabel>
#include <QString>

class LtLabel : public QLabel
{
public:
    LtLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~LtLabel();
};

#endif // LTLABEL_H
