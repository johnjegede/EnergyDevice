#include "mainwindow.h"
#include "inputform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputForm inputVal;
    inputVal.show();
    
    return a.exec();
}
