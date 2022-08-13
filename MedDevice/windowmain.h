#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include "interface.h"
#include "mainmenu.h"
#include <vector>
#include <QObject>
#include <QTime>
#include <QTimer>
#include "log.h"

class Interface;

class windowmain: public QObject
{
    Q_OBJECT
public:
    windowmain(Interface *uiVal);
    ~windowmain();
    void displayMenu(bool, int);
    void decreaseBattery();
    void endTreatment();

private:
    Interface *userInterface;
    mainMenu* programs;
    mainMenu* frequency;
    mainMenu* history;
    mainMenu* biofeedback;
    QTimer* objTimer;
    QTime*  objTime;
    vector<menuOptions> next;
    vector<mainMenu*> menus;
    QTime start;
    QTime stop;
    vector<Log*> logHistory;
    bool isOn;
    bool treatment;
    int level;
    int selectedOption;
    int row;
    int subOption;
    int parentVal;
    int powerlevel;
    float maxBatteryPerSecond;
    float maxBatteryval;


public slots:
    void selectPressed();
    void switchPressed();
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void previousPressed();
    void mainMenuPressed();
    void increasePressed();
    void decreasePressed();
    void programTimer();
    void startTreat();
    void setRection();
};

#endif // WINDOWMAIN_H
