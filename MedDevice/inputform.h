#ifndef INPUTFORM_H
#define INPUTFORM_H


#include <QWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "interface.h"
#include "mainwindow.h"
#include "windowmain.h"


QT_BEGIN_NAMESPACE
class QLabel;
class QCheckBox;
class QRadioButton;
class Interface;
QT_END_NAMESPACE

//! [class definition]
class InputForm : public QWidget
{
    Q_OBJECT

public:
    InputForm(QWidget *parent = nullptr);
    QWidget *getwidget();
    windowmain *win;
    QVBoxLayout* rows;

public slots:
    void dialogOkPressed();
    void dialogCancelPressed();


private:
    QCheckBox *mainMenu;

    QCheckBox *navLeftCheck;
    QCheckBox *prevButton;

    QCheckBox *historyCheck;
    QCheckBox *biofeedbackCheck;

    QRadioButton *navRightRadio;
    QRadioButton *increaseButton;

    QRadioButton *navLeftRadio;
    QRadioButton *decreaseButton;

    QDialogButtonBox* m_buttons;


    Interface* mainVal;


};
//! [class definition]

#endif // INPUTFORM_H
