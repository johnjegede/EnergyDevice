#include "log.h"
#include <QDate>
#include <QTime>

Log::Log(QString treat, int pwrlvl, int timing)
{
    QDate * date = new QDate();
    QTime * ctime = new QTime();

    day = date->currentDate().toString();
    time = ctime->currentTime().toString("hh:mm AP");
    treatment = treat;
    powerLevel = pwrlvl;
    duration = timing ;

}

Log::~Log(){

}

QString Log::logOutput(){
    QString output = "";
    output += day + ",  ";
    output += time + " "  + "\n";
    output += " Treatment: " + treatment + "\n";
    output += " Power Level: " + QString::number(powerLevel) + "\n";
    int durMin = duration/60;
    int durSec = duration%60;
    output += " Duration: " + QString::number(durMin) + "min " + QString::number(durSec) + "sec\n\n";
    return output;
}
