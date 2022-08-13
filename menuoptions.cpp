#include "menuoptions.h"

menuOptions::menuOptions(QString menuOption, int minutes, int seconds): menuOption(menuOption), minutes(minutes), seconds(seconds)
{}
menuOptions::menuOptions(QString menuOption, int time): menuOption(menuOption), minutes(time)
{}
 menuOptions::menuOptions(QString menuOption): menuOption(menuOption)
{}



