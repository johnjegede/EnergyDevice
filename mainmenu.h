#ifndef MAINMENU_H
#define MAINMENU_H

#include "menuoptions.h"
#include <QString>
#include <vector>
using namespace std;


class mainMenu
{
public:
    mainMenu(QString);
    QString parentMenu;
    vector<menuOptions > childOptions;

    void setChildOptions(QString suboption, int minutes, int seconds);
    void setChildOptions(QString suboption, int minutes);
    void setChildOptions(QString suboption);
    QString getParentMenu();
    vector<menuOptions> getChildOptions();
};

#endif // MAINMENU_H
