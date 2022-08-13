#include "mainmenu.h"

mainMenu::mainMenu(QString parentMenu): parentMenu(parentMenu)
{

}

void mainMenu::setChildOptions(QString suboption = "", int minutes = 0, int seconds = 0)
{
    menuOptions subChild(suboption,minutes,seconds);
    childOptions.push_back(subChild);
}

void mainMenu::setChildOptions(QString suboption = "", int minutes = 0)
{
    menuOptions subChild(suboption,minutes);
    childOptions.push_back(subChild);
}

void mainMenu::setChildOptions(QString suboption = "")
{
    menuOptions subChild(suboption);
    childOptions.push_back(subChild);
}

QString mainMenu::getParentMenu()
{
    return parentMenu;
}

vector<menuOptions> mainMenu::getChildOptions()
{
    return childOptions;
}

