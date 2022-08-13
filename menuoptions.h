#ifndef MENUOPTIONS_H
#define MENUOPTIONS_H

#include <QString>

using namespace std;

class menuOptions
{
public:
    menuOptions(QString , int, int);
    menuOptions(QString , int);
    menuOptions(QString);
    QString menuOption;
    int minutes;
    int seconds;
};

#endif // MENUOPTIONS_H
