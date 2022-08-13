#include <QtWidgets>
#include <interface.h>
#include "windowmain.h"

//The Medical device GUI
Interface::Interface(QWidget *parent,
                     bool mainB,bool navleftB,bool prevB,bool navrightRB, bool inceB, bool nevleftRB, bool decB,bool historyB, bool biofeedbackB)
    :QWidget(parent),
      mainMenuSel(mainB),navLeftSel(navleftB),prevButtonSel(prevB),
      navRightRadioSel(navrightRB),increaseButtonSel(inceB),navLeftRadioSel(nevleftRB),
      decreaseButtonSel(decB), historySel(historyB), biofeedbackSel(biofeedbackB)
{

    QHBoxLayout* row = new QHBoxLayout();

    QLabel* device = new QLabel(tr("DEVICE"));
    switchButton = new QPushButton("ON/OFF");

    row->addWidget(device);
    row->addWidget(switchButton);

    screenView = new QListWidget();


    selctButton = new QPushButton("SELECT");
    upButton = new QPushButton("UP");
    downButton = new QPushButton("DOWN");
    leftButton = new QPushButton("LEFT");
    rightButton = new QPushButton("RIGHT");
    previousButton = new QPushButton("PREVIOUS");
    mainMenuButton = new QPushButton("MENU");
    increasePowerButton = new QPushButton("+");
    decreasePowerButton = new QPushButton("-");

    QGridLayout *buttonLayout = new QGridLayout;
    if(increaseButtonSel)
    {
        buttonLayout->addWidget(increasePowerButton,0,0);
    }
    if(decreaseButtonSel)
    {
        buttonLayout->addWidget(decreasePowerButton,0,2);
    }
    if(prevButtonSel)
    {
        buttonLayout->addWidget(previousButton,1,0);
    }
    if(mainMenuSel)
    {
        buttonLayout->addWidget(mainMenuButton,1,2);
    }
    if(navRightRadioSel)
    {
        buttonLayout->addWidget(rightButton,3,2);
    }
    if(navLeftRadioSel or navLeftSel)
    {
        buttonLayout->addWidget(leftButton,3,0);
    }

    buttonLayout->addWidget(upButton,2,1);
    buttonLayout->addWidget(selctButton,3,1);
    buttonLayout->addWidget(downButton,4,1);

    QVBoxLayout* rows = new QVBoxLayout();

    rows->addLayout(row);
    rows->addWidget(screenView);
    rows->addLayout(buttonLayout);



    electrodeCheck = new QCheckBox(tr("electrode (touching skin)"));

    skinSimSlider = new QSlider();
    skinSimSlider->setOrientation(Qt::Horizontal);
    skinSimSlider->setRange(0,100);
    skinSimSlider->setSliderPosition(36);
    QLabel* skinSim = new QLabel(tr("Skin Simulation"));



    batteryLevel = new QProgressBar();
    batteryLevel->setRange(0,100);
    batteryLevel->setValue(100);
    QLabel* batteryBar = new QLabel(tr("Battery Bar"));


    batterySlider = new QSlider();
    batterySlider->setOrientation(Qt::Horizontal);
    batterySlider->setRange(0,100);
    batterySlider->setSliderPosition(100);
    QLabel* batterySim = new QLabel(tr("Battery control"));

    powerLevel = new QLCDNumber();
    //powerLevel->display("20");
    QLabel* powerLabel = new QLabel(tr("Power Level"));
    QHBoxLayout* powerLabelRow = new QHBoxLayout();
    powerLabelRow->addWidget(powerLabel);
    powerLabelRow->addWidget(powerLevel);



    QLabel* frequency = new QLabel(tr("Frequency"));
    QLabel* frequencyLabel = new QLabel(tr("120hz"));
    QHBoxLayout* frequencyRow = new QHBoxLayout();
    frequencyRow->addWidget(frequency);
    frequencyRow->addWidget(frequencyLabel);

    QVBoxLayout* rowsB = new QVBoxLayout();
    rowsB->addWidget(electrodeCheck);
    if(biofeedbackSel)
    {
        rowsB->addWidget(skinSim);
        rowsB->addWidget(skinSimSlider);
    }
    rowsB->addWidget(batteryBar);
    rowsB->addWidget(batteryLevel);
    rowsB->addWidget(batterySim);
    rowsB->addWidget(batterySlider);
    rowsB->addLayout(powerLabelRow);
    rowsB->addLayout(frequencyRow);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(rows);
    mainLayout->addLayout(rowsB);

    setLayout(mainLayout);
    setWindowTitle(tr("Medical device"));

    connect(batterySlider, SIGNAL(valueChanged(int)), batteryLevel, SLOT(setValue(int)));
}

Interface::~Interface()
{

}

bool Interface::getDecreaseButtonSel()
{
    return decreaseButtonSel;
}
bool Interface::getIncreaseButtonSel()
{
    return increaseButtonSel;
}
bool Interface::getPrevButtonSel()
{
    return prevButtonSel;
}

bool Interface::getHistorySel()
{
    return historySel;
}
bool Interface::getBiofeedbackSel()
{
    return biofeedbackSel;
}

void Interface::showWindow()
{
    this->show();
}
