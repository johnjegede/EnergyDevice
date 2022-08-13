#ifndef FORMLAYOUT_H
#define FORMLAYOUT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QCheckBox;
class QRadioButton;
QT_END_NAMESPACE

//! [class definition]
class OptionForm : public QWidget
{
    Q_OBJECT

public:
    OptionForm(QWidget *parent = nullptr);

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
};
//! [class definition]

#endif // FORMLAYOUT_H
