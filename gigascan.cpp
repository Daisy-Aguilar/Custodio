#include "gigascan.h"
#include "widget.h"
#include <QFileDialog>

gigaScan::gigaScan(QObject *parent)
    : QObject{parent}
{
    connect(&cmdPrompt,&QProcess::stateChanged,this,&gigaScan::stateChanged);
    connect(&cmdPrompt,&QProcess::readyReadStandardOutput,this,&gigaScan::readyReadStandardOutput);
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
    //if(ui->stackedWidget) {
        cmdPrompt.write(fullScanCmd().toUtf8());
    //}
}

void gigaScan::readyReadStandardOutput() {
    if (!isRunning) return;
    QByteArray data = cmdPrompt.readAllStandardOutput();
    emit output(data);
}
