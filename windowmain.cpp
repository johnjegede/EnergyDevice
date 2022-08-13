#include "windowmain.h"
#include <QtWidgets>
#include <QString>
//#include "interface.h"

windowmain::windowmain(Interface *uiVal):QObject(),userInterface(uiVal), isOn(false),treatment(false),level(0),selectedOption(0)
{
    //Create the main menu
    programs = new mainMenu("PROGRAMS");
    frequency = new mainMenu("FREQUENCY");
    history = new mainMenu("HISTORY");
    biofeedback = new mainMenu("BIOFEEDBACK");

    //Create menu option
    programs->setChildOptions("Head",5,0);
    programs->setChildOptions("Throat",10,0);
    programs->setChildOptions("Cough",4,0);
    programs->setChildOptions("Cold",2,0);

    frequency->setChildOptions("125Hz",0);
    frequency->setChildOptions("140Hz",0);
    frequency->setChildOptions("200Hz",0);
    frequency->setChildOptions("350Hz",0);

    history->setChildOptions("VIEW");
    history->setChildOptions("CLEAR");

    biofeedback->setChildOptions("Start");


    menus.push_back(programs);
    menus.push_back(frequency);

    //If user wants the history menu
    if(userInterface->getHistorySel())
        menus.push_back(history);

    //If user wants the biofeedback menu
    if(userInterface->getBiofeedbackSel())
        menus.push_back(biofeedback);

    //Setup time
    objTimer = new QTimer();

    //Intilize power level
    powerlevel = 20;
    userInterface->powerLevel->display(powerlevel);

    //Connect signal  from components to slots
    connect(userInterface->selctButton, SIGNAL(pressed()), this, SLOT(selectPressed()));
    connect(userInterface->switchButton, SIGNAL(pressed()), this, SLOT(switchPressed()));
    connect(userInterface->upButton, SIGNAL(pressed()), this, SLOT(upPressed()));
    connect(userInterface->downButton, SIGNAL(pressed()), this, SLOT(downPressed()));
    connect(userInterface->leftButton, SIGNAL(pressed()), this, SLOT(leftPressed()));
    connect(userInterface->rightButton, SIGNAL(pressed()), this, SLOT(rightPressed()));
    connect(userInterface->previousButton, SIGNAL(pressed()), this, SLOT(previousPressed()));
    connect(userInterface->mainMenuButton, SIGNAL(pressed()), this, SLOT(mainMenuPressed()));
    connect(userInterface->increasePowerButton, SIGNAL(pressed()), this, SLOT(increasePressed()));
    connect(userInterface->decreasePowerButton, SIGNAL(pressed()), this, SLOT(decreasePressed()));
    connect(userInterface->electrodeCheck, SIGNAL(pressed()), this, SLOT(startTreat()));
    connect(userInterface->skinSimSlider, SIGNAL(valueChanged(int)), this, SLOT(setRection()));
    connect(objTimer, SIGNAL(timeout()), this,SLOT(programTimer()));
}

windowmain::~windowmain()
{
    delete userInterface;
}

void windowmain::displayMenu(bool on,int level)
{
    //Switch off Device
    if(on == false)
    {
        if(treatment == true)
        {
            objTimer->stop();
            treatment = false;
            //logHistory.clear();
        }

        userInterface->screenView->clear();
        return;
    }


    if(level == 0)
    {
        //Display the main menu options
        userInterface->screenView->clear();
        for(unsigned long i =0 ; i < menus.size(); i++)
        {
            const QString val = menus[i]->parentMenu;
            userInterface->screenView->addItem(val);
        }

        selectedOption = 0;
        userInterface->screenView->setCurrentRow(selectedOption);

    }else if (level == 1)
    {
        //Display the sub menu of each menu
        parentVal = userInterface->screenView->currentRow();
        next = menus[parentVal]->getChildOptions();
        userInterface->screenView->clear();

        for(int i =0; i < (int)next.size(); i++)
        {
            const QString suboption = next[i].menuOption;
            userInterface->screenView->addItem(suboption);
        }

        selectedOption = 0;
        userInterface->screenView->setCurrentRow(selectedOption);

    }else if(level == 2)
    {
        //Display the action required for that sub menu
        int sec = 0;
        int min =0;
        treatment = true;
        subOption = userInterface->screenView->currentRow();
        userInterface->screenView->clear();
        maxBatteryPerSecond = userInterface->batteryLevel->value();


        if (next[subOption].menuOption == "Start")
        {
            objTime = new QTime (0,min,sec,0);
            start = QTime::fromString(objTime->toString("mm:ss"),"mm:ss");

            //Start timer if on skin
            if(userInterface->electrodeCheck->checkState() == 2 and treatment)
            {
                objTimer->start(1000);
            }

            //Set up the timer in the display
            userInterface->screenView->addItem("");
            QFont f = userInterface->screenView->item(0)->font();
            f.setPixelSize(70);
            userInterface->screenView->item(0)->setFont(f);
            userInterface->screenView->item(0)->setText(objTime->toString("mm:ss"));

            //Set up initial reaction value
            userInterface->screenView->addItem("");
            QString initial = "inital value: "+ QString::number(userInterface->skinSimSlider->value());
            userInterface->screenView->item(1)->setText(initial);

            //Set up ongoing reaction value
            userInterface->screenView->addItem("");
            userInterface->screenView->item(2)->setText("Ongoing value: ");
            return;
        }

        if( next[subOption].menuOption == "VIEW")
        {
            //Display the history of activities on the screen
            for(int i =0; i < (int)logHistory.size(); i++)
            {
                const QString logOut = logHistory[i]->logOutput();
                std::string logval = logHistory[i]->logOutput().toStdString() ;
                qInfo( "logOut %s",logval.c_str());
                userInterface->screenView->addItem(logOut);
            }
            if (logHistory.size() == 0) userInterface->screenView->addItem("No Records to display.");
            return;
        }
        else if (next[subOption].menuOption == "CLEAR" ) {
            //Clear the history
            logHistory.clear();
            return;
        }

        if (parentVal == 1)
        {

            min = next[subOption].minutes;
        }else {
            sec = next[subOption].seconds;
            min = next[subOption].minutes;
        }
        //Set the timer for each action
        objTime = new QTime (0,min,sec,0);
        start = QTime::fromString(objTime->toString("mm:ss"),"mm:ss");

        if(userInterface->electrodeCheck->checkState() == 2 and treatment)
        {
            objTimer->start(1000);
        }

        //Set up the timer in the display
        userInterface->screenView->addItem("");
        QFont f = userInterface->screenView->item(0)->font();
        f.setPixelSize(70);
        userInterface->screenView->item(0)->setFont(f);
        userInterface->screenView->item(0)->setText(objTime->toString("mm:ss"));

    }

}

//Get and set the reaction of the skin from the simulation
void windowmain::setRection()
{
    QString initial = "Ongoing value: "+ QString::number(userInterface->skinSimSlider->value());
    userInterface->screenView->item(2)->setText(initial);
}

//Pause or continue the treatment depending on if its on the skin
void windowmain::startTreat()
{
    if(userInterface->electrodeCheck->checkState() == 2 and treatment )
    {
        objTimer->stop();
        stop = QTime::fromString(objTime->toString("mm:ss"),"mm:ss");
    }

    if(userInterface->electrodeCheck->checkState() == 0 and treatment)
    {
        objTimer->start(1000);
    }
}

//Countdown on countup timer depending on the action required
void windowmain::programTimer()
{
    if(parentVal ==0)
    {
        objTime->setHMS (0, objTime->addSecs (-1).minute (), objTime->addSecs (-1).second ());
    }else if (parentVal == 1 or parentVal == 3)
    {
        objTime->setHMS (0, objTime->addSecs (1).minute (), objTime->addSecs (1).second ());
    }

    userInterface->screenView->item(0)->setText(objTime->toString("mm:ss"));

    if(objTime->toString("mm:ss") == "00:00")
    {
        endTreatment();
    }

    // As activity takes place decrease battery
    decreaseBattery();
}

// End treatment and save the action
void windowmain::endTreatment()
{
    objTimer->stop();
    treatment = false;
    stop = QTime::fromString(objTime->toString("mm:ss"),"mm:ss");
    int result =0; start.secsTo(stop);
    if(parentVal == 0)
    {
        result = stop.secsTo(start);
    }else
    {
        result = start.secsTo(stop);
    }
    // Log the activity that has just ended
    Log* temp = new Log(next[subOption].menuOption, userInterface->powerLevel->value(), result);
    logHistory.push_back(temp);

}

//Called by Action every second of treatment
void windowmain::decreaseBattery() {
    maxBatteryPerSecond = maxBatteryPerSecond - 0.5;

    //if battery is empty switchoff device
    if(maxBatteryPerSecond <= 0)
    {
        userInterface->batteryLevel->setValue(0);
        displayMenu(false,0);
    }
    userInterface->batteryLevel->setValue(round(maxBatteryPerSecond));
}

void windowmain::selectPressed()
{
    //Increase the level
    level++;
    if(isOn)
    {
        displayMenu(isOn,level);
        //row = userInterface->screenView->currentRow();
    }
}

void windowmain::switchPressed()
{
    //Switch on or off the device
    level = 0;
    isOn = !isOn;
    int batteryVal = userInterface->batterySlider->value();
    if(batteryVal > 0 )
    {
        displayMenu(isOn,level);
    }else{
        userInterface->screenView->addItem("Battery Low");
    }
}

void windowmain::upPressed()
{
    //Select the option above
    if(selectedOption == 0)
    {
        return;
    }

    selectedOption--;
    userInterface->screenView->setCurrentRow(selectedOption);


}

void windowmain::downPressed()
{
    //Select the option below
    if((selectedOption == (int)menus.size()-1) and level == 0)
    {
        return;
    }else if (row < 0 and level == 1 and (selectedOption == (int)menus[row]->getChildOptions().size()-1) )
    {
        return;
    }

    selectedOption++;
    userInterface->screenView->setCurrentRow(selectedOption);


}

void windowmain::leftPressed()
{

    if(!userInterface->getDecreaseButtonSel())
    {
        //Decrease the power if the decrease button is selected
        decreasePressed();
    }else if(!userInterface->getPrevButtonSel())
    {
        //Go to the previous menu
        previousPressed() ;
    }

}

void windowmain::rightPressed()
{
    //Increase the power
    if(!userInterface->getIncreaseButtonSel())
    {
        increasePressed();
    }

}

void windowmain::previousPressed()
{
    //If off do nothing
    if(isOn == false)
    {
        return;
    }
    //end treatment
    if(treatment == true)
    {
        endTreatment();
    }
    if(level == 0)
    {
        return;
    }
    level--;

    //Go to main menu
    if(level == 0)
    {
        userInterface->screenView->clear();
        for(unsigned long i =0 ; i < menus.size(); i++)
        {
            const QString val = menus[i]->parentMenu;
            userInterface->screenView->addItem(val);
        }

        selectedOption = 0;
        userInterface->screenView->setCurrentRow(selectedOption);

    }else if (level == 1)
    {
        //Go to sub menu
        next = menus[parentVal]->getChildOptions();
        userInterface->screenView->clear();

        for(int i =0; i < (int)next.size(); i++)
        {
            const QString suboption = next[i].menuOption;
            userInterface->screenView->addItem(suboption);
        }

        selectedOption = 0;
        userInterface->screenView->setCurrentRow(selectedOption);
        row = userInterface->screenView->currentRow();

    }

}

void windowmain::mainMenuPressed()
{

    //If main menu is pressed display it
    if(treatment == true)
    {
        endTreatment();
    }
    displayMenu(isOn,0);
    level = 0;

}

void windowmain::increasePressed()
{
    //increase the power level
    if(treatment == true)
    {
        userInterface->powerLevel->display(++powerlevel);
    }


}

void windowmain::decreasePressed()
{
    //Decrease the power level
    if(treatment == true)
    {
        userInterface->powerLevel->display(--powerlevel);
    }

}
