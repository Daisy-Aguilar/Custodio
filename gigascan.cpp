#include "gigascan.h"
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <QDate>

gigaScan::gigaScan(QObject *parent)
    : QObject{parent}
{
    connect(&cmdPrompt,&QProcess::stateChanged,this,&gigaScan::stateChanged);
    connect(&cmdPrompt,&QProcess::readyReadStandardOutput,this,&gigaScan::readyReadStandardOutput);

    folderScanPath = ""; // default folder path
}

void gigaScan::startCmd() { // opens command prompt
    if(isRunning) stopCmd();
    isRunning = true;
    cmdPrompt.start("cmd");
}

void gigaScan::stopCmd() { // closes command prompt
    isRunning = false;
    cmdPrompt.kill();
    cmdPrompt.close();
}

void gigaScan::stateChanged(QProcess::ProcessState newState) { //tracks state of commandprompt
        switch(newState) {
            case QProcess::NotRunning:
                emit output("Stopped");
                break;
            case QProcess::Starting:
                emit output("Starting");
                break;
            case QProcess::Running:
                emit output("Running");
                inputCommand(); // when running, call our input commands.
                break;
    }
}

QString gigaScan::fullScanCmd() { // creates the command to run a fullscan to enter in cmd prompt
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";

    command.append(clamavPath+"clamscan -r -i -l ..\\Custodio\\clamAVLog --move=..\\Custodio\\Quarantine C:\\ \n \r");
    emit output(command);
    return command;
}

QString gigaScan::updateDatabase() {
    QByteArray update = "..\\Custodio\\clamAVFiles\\freshclam";
    return update;
}

QString gigaScan::deleteQuarantine() {
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";
    command.append(clamavPath+"clamscan -i --remove=yes ..\\Custodio\\Quarantine \n \r");
    return command;
}

void gigaScan::inputCommand() { // depending on page index, return different scan function
   if(getIndex() == 3) {
        cmdPrompt.write(fullScanCmd().toUtf8());
    }
    if(getIndex() == 4) {
       cmdPrompt.write(folderCommand().toUtf8());
    }
    if(getIndex() == 0) {
       cmdPrompt.write(scheduledScan().toUtf8());
    }
    if(getIndex() == 1) {
        cmdPrompt.write(updateDatabase().toUtf8());
    }
    if(getIndex() == 7) {
        cmdPrompt.write(deleteQuarantine().toUtf8());
    }
}


QString gigaScan::folderCommand() { // returns commands with the specific file directory
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";
    command.append(clamavPath+ "clamscan -r -i -l ..\\Custodio\\clamAVLog --move=..\\Custodio\\Quarantine '"+getPath().toUtf8()+ "' \r \n");
    return command;
}

void gigaScan::readyReadStandardOutput() { // returns data from cmd to qprocess
    if (!isRunning) return;
    QByteArray data = cmdPrompt.readAllStandardOutput();
    emit output(data.trimmed());
}

void gigaScan::setPath(const QString &newPath) {
    folderScanPath = newPath;
}

QString gigaScan::getPath() const { // set and getPath are a proxy to get the path from the UI
    return folderScanPath;          // to be used in folder scanning
}

void gigaScan::savePath(QString pathToSave) {
    pathToSave.replace(" ","_");
    std::string pathToWrite = pathToSave.toStdString();
    std::fstream file;
    file.open("..\\Custodio\\savedPath.txt", std::fstream::out | std::fstream::trunc);
    file << pathToWrite;
    file.close();
}


QString gigaScan::scheduledScan() { // scheduled scan to run at launch
    std::fstream file;
    file.open("..\\Custodio\\dateChecksAndFlags\\month.txt");
    std::string str;
     while (1) {
        file >> str;
        if (file.eof())
            break;
     }
    file.close();
    file.open("..\\Custodio\\dateChecksAndFlags\\date.txt");
    std::string date;
    while (1) {
        file >> date;
        if (file.eof())
            break;
    }
    file.close();
    file.open("..\\Custodio\\dateChecksAndFlags\\weekNum.txt");
    std::string week;
     while (1) {
        file >> week;
        if (file.eof())
            break;
     }
    file.close();
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";
    QString savedMonth = QString::fromStdString(str);
    QString savedDate = QString::fromStdString(date);
    int savedWeek = std::stoi(week);
    command.append(clamavPath+"clamscan -r -i -l ..\\Custodio\\clamAVLog --move=..\\Custodio\\Quarantine '"+readPath().toUtf8()+ "' \r \n");
    if (isDailyChecked() == 1) {
        if(savedDate != giveDate().replace(" ","")) {
            std::string newDate = giveDate().replace(" ","").toStdString();
            std::ofstream file;
            file.open("..\\Custodio\\dateChecksAndFlags\\date.txt");
            file << newDate;
            file.close();
            return command;
        }
    }
    QString savedWeekQ = QString::number(savedWeek);
    QString giveWeekQ = QString::number(giveWeekNum());
    if (isWeeklyChecked() == 1) {
        if(giveWeekNum() != savedWeek) {
            std::string weekNum = std::to_string(giveWeekNum());
            std::ofstream file;
            file.open("..\\Custodio\\dateChecksAndFlags\\weekNum.txt");
            file << weekNum;
            file.close();
            return command;
        }
    }
    if (isMonthlyChecked() == 1) {
       if(savedMonth != QString::number(giveMonth())) {
           std::string s = std::to_string(giveMonth());
           std::ofstream file;
           file.open("..\\Custodio\\dateChecksAndFlags\\month.txt");
           file << s;
           file.close();
           return command;

        }
    }

    return "";
}
