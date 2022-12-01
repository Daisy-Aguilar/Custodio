#include "gigascan.h"
#include "widget.h"
#include <QFileDialog>

gigaScan::gigaScan(QObject *parent)
    : QObject{parent}
{
    connect(&cmdPrompt,&QProcess::stateChanged,this,&gigaScan::stateChanged);
    connect(&cmdPrompt,&QProcess::readyReadStandardOutput,this,&gigaScan::readyReadStandardOutput);

    folderScanPath = "";
}

void gigaScan::startCmd() {
    if(isRunning) stopCmd();
    isRunning = true;
    cmdPrompt.start("cmd");
}

void gigaScan::stopCmd() {
    isRunning = false;
    cmdPrompt.kill();
    cmdPrompt.close();
}

void gigaScan::finished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (!isRunning) return;
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    emit output("Completed");
}

void gigaScan::stateChanged(QProcess::ProcessState newState) {
    switch(newState) {
        case QProcess::NotRunning:
            emit output("Stopped");
            break;
        case QProcess::Starting:
            emit output("Starting");
            break;
        case QProcess::Running:
            emit output("Running");
            inputCommand();
            //folderScan();
            break;
    }
}

QString gigaScan::fullScanCmd() {
    QByteArray command;
    QByteArray clamavPath = "..\\Custodio\\clamAVFiles\\";

    command.append(clamavPath+"clamscan -r --move=..\\Custodio\\Quarantine C:\\ \r \n");
    //command.append("\r");
    //command.append("\n");
    return command;
}

void gigaScan::inputCommand() {
    if(getIndex() == 3) { // if page is fullscan page, full scan
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
    command.append(clamavPath+ "clamscan -r --move=..\\Custodio\\Quarantine '"+getPath().toUtf8()+ "' \r \n");

    return command;
}

void gigaScan::readyReadStandardOutput() {
    if (!isRunning) return;
    QByteArray data = cmdPrompt.readAllStandardOutput();
    emit output(data);
}

void gigaScan::setPath(const QString &newPath) {
    folderScanPath = newPath;
}

QString gigaScan::getPath() const {
    return folderScanPath;
}
