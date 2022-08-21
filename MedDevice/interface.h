#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QObject>



QT_BEGIN_NAMESPACE
class QLabel;
class QCheckBox;
class QPushButton;
class QListWidget;
class QSlider;
class QProgressBar;
class QLCDNumber;
QT_END_NAMESPACE


class Interface: public QWidget
{
    Q_OBJECT

public:
    Interface( QWidget *parent = nullptr,bool = false,bool = false,bool= true,bool= true,bool= false,bool= true,bool= false,bool = true,bool = false);//
    ~Interface();   
    void showWindow();
    bool getDecreaseButtonSel();
    bool getIncreaseButtonSel();
    bool getPrevButtonSel();
    bool getHistorySel();
    bool getBiofeedbackSel();

     QListWidget* screenView;
    QPushButton* switchButton;
    QPushButton* selctButton;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* leftButton;
    QPushButton* rightButton;
    QPushButton* previousButton;
    QPushButton* mainMenuButton;
    QPushButton* increasePowerButton;
    QPushButton* decreasePowerButton;

    QCheckBox* electrodeCheck;

    QProgressBar* batteryLevel;
    QLCDNumber* powerLevel;
    QSlider* batterySlider;
    QSlider* skinSimSlider;

private:
    bool mainMenuSel;

    bool navLeftSel;
    bool prevButtonSel;

    bool navRightRadioSel;
    bool increaseButtonSel;

    bool navLeftRadioSel;
    bool decreaseButtonSel;

    bool historySel;
    bool biofeedbackSel;
};
#endif // INTERFACE_H
