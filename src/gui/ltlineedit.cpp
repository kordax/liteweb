#include "ltlineedit.h"

Lt::LtLineEdit::LtLineEdit(const QString& string, QWidget* parent)
    :QLineEdit(parent)
{
    this->setText(string);
}

Lt::LtLineEdit::~LtLineEdit()
{

}

void Lt::LtLineEdit::onStart()
{

}
