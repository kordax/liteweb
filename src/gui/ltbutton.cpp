#include "gui/ltbutton.h"

Lt::LtButton::LtButton(QWidget* parent)
    :QPushButton(parent)
{

}

Lt::LtButton::~LtButton()
{

}

Lt::LtButton::LtButton(const QString& string, QWidget* parent)
    :QPushButton(string, parent)
{
    this->setText(string);
}
