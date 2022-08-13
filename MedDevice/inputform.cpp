#include <QtWidgets>
#include "inputform.h"
#include <QDialog>
#include <QObject>
#include <QDebug>
#include "interface.h"
#include "mainwindow.h"
#include "windowmain.h"

//Components selection form interface
InputForm::InputForm(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* row = new QHBoxLayout();
    rows = new QVBoxLayout();

    QGroupBox *mandatory = new QGroupBox(tr("Mandatory Components"));
    QLabel *screen = new QLabel(tr("Screen,"));
    QLabel *okButton = new QLabel(tr("Select,"));
    QLabel *Electrode = new QLabel(tr("Electrode,"));
    QLabel *switchButton = new QLabel(tr("ON/OFF button,"));
    QLabel *navUp = new QLabel(tr("Navigate Up,"));
    QLabel *navDown = new QLabel(tr("Navigate Down,"));
    QVBoxLayout* mandatoryBox = new QVBoxLayout();

    row->addWidget(screen);
    row->addWidget(okButton);
    row->addWidget(Electrode);
    mandatoryBox->addLayout(row);
    row = new QHBoxLayout();
    row->addWidget(switchButton);
    row->addWidget(navUp);
    row->addWidget(navDown);
     mandatoryBox->addLayout(row);
     mandatory->setLayout(mandatoryBox);
    rows->addWidget(mandatory);

    mainMenu = new QCheckBox(tr("Main Menu"));
    rows->addWidget(mainMenu);



    QGroupBox *menu = new QGroupBox(tr("Menu"));
    historyCheck = new QCheckBox(tr("History Menu"));
    biofeedbackCheck = new QCheckBox(tr("Biofeedback Menu"));
    historyCheck->setChecked(true);
    QVBoxLayout* mcheckbox = new QVBoxLayout();
    mcheckbox->addWidget(historyCheck);
    mcheckbox->addWidget(biofeedbackCheck);
    mcheckbox->addStretch(2);
    menu->setLayout(mcheckbox);
    rows->addWidget(menu);

    QGroupBox *previous = new QGroupBox(tr("Previous"));
    navLeftCheck = new QCheckBox(tr("Navigate Left"));
    prevButton = new QCheckBox(tr("Previous Button"));
    prevButton->setChecked(true);
    QVBoxLayout* vcheckbox = new QVBoxLayout();
    vcheckbox->addWidget(navLeftCheck);
    vcheckbox->addWidget(prevButton);
    vcheckbox->addStretch(2);
    previous->setLayout(vcheckbox);
    rows->addWidget(previous);

    QGroupBox *increasePower = new QGroupBox(tr("Increase Power"));
    navRightRadio = new QRadioButton(tr("Navigate Right"));
    increaseButton = new QRadioButton(tr("Increase Button"));
    navRightRadio->setChecked(true);
    QVBoxLayout* vRadioInc = new QVBoxLayout();
    vRadioInc->addWidget(navRightRadio);
    vRadioInc->addWidget(increaseButton);
    vRadioInc->addStretch(2);
    increasePower->setLayout(vRadioInc);
    rows->addWidget(increasePower);


    QGroupBox *decreasePower = new QGroupBox(tr("Decrease Power"));
    navLeftRadio = new QRadioButton(tr("Navigate Left"));
    decreaseButton = new QRadioButton(tr("Decrease Button"));
    navLeftRadio->setChecked(true);
    QVBoxLayout* vRadioDec = new QVBoxLayout();
    vRadioDec->addWidget(navLeftRadio);
    vRadioDec->addWidget(decreaseButton);
    vRadioDec->addStretch(2);
    decreasePower->setLayout(vRadioDec);
    rows->addWidget(decreasePower);

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    rows->addWidget(m_buttons);

    QObject::connect(m_buttons, SIGNAL(accepted()), this, SLOT(dialogOkPressed()));
    QObject::connect(m_buttons, SIGNAL(rejected()), this, SLOT(dialogCancelPressed()));

    setLayout(rows);
    setWindowTitle(tr("Medical Device"));
}



void InputForm::dialogOkPressed()
{
    //Input user setup
   mainVal= new Interface(nullptr,mainMenu->isChecked(),navLeftCheck->isChecked(),prevButton->isChecked(),navRightRadio->isChecked(),
                          increaseButton->isChecked(),navLeftRadio->isChecked(),decreaseButton->isChecked(),historyCheck->isChecked(),biofeedbackCheck->isChecked());
   mainVal->showWindow();
   win = new windowmain(mainVal);

    this->close();
}

void InputForm::dialogCancelPressed()
{
    //Input default setup
    mainVal= new Interface(nullptr,false,false,true,true,false,true,false,true,false);
    mainVal->showWindow();
    win = new windowmain(mainVal);

    this->close();
}
