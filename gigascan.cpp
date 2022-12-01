#include "gigascan.h"
#include <QFileDialog>

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

    command.append(clamavPath+"clamscan -r -o -l ..\\Custodio\\clamAVLog --move=..\\Custodio\\Quarantine C:\\ \r \n");
    return command;
}

void gigaScan::inputCommand() { // depending on page index, return different scan function
    if(getIndex() == 3) {
        cmdPrompt.write(fullScanCmd().toUtf8());
    }
    if(getIndex() == 4) {
        cmdPrompt.write(folderCommand().toUtf8());
    }
    if(getIndex() == 5) {
        // cmdPrompt.wrie(scheduledCommand Function);
    }
}


QString gigaScan::folderCommand() {
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";
    command.append(clamavPath+ "clamscan -r -o -l ..\\Custodio\\clamAVLog --move=..\\Custodio\\Quarantine '"+getPath().toUtf8()+ "' \r \n");
    return command;
}

void gigaScan::readyReadStandardOutput() { // returns data from cmd to qprocess
    if (!isRunning) return;
    QByteArray data = cmdPrompt.readAllStandardOutput();
    emit output(data);
}

void gigaScan::setPath(const QString &newPath) {
    folderScanPath = newPath;
}

QString gigaScan::getPath() const { // set and getPath are a proxy to get the path from the UI
    return folderScanPath;          // to be used in folder scanning
}
