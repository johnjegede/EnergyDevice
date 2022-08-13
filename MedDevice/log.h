#ifndef LOG_H
#define LOG_H


#include <QString>


class Log
{
public:
    Log(QString="", int=0, int=0);
    ~Log();
    QString logOutput();
private:
    QString day;
    QString time;
    QString treatment;
    int powerLevel;
    int duration;

};

#endif // LOG_H
