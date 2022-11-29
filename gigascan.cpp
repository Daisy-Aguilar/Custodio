#include "gigascan.h"
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

/* void gigaScan::finished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (!isRunning) return;
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    emit output("Completed");
} */

void gigaScan::stateChanged(QProcess::ProcessState newState) {
    switch(newState) {
        case QProcess::NotRunning:
            emit output("Not Running");
            break;
        case QProcess::Starting:
            emit output("Starting...");
            break;
        case QProcess::Running:
            emit output("Running");
            startScan();
            break;
    }
}

QString gigaScan::enterCmd() {
    QByteArray command;
    QByteArray clamavPath = "..\\TestingClamAV_FullScan\\clamAVFiles\\";

    command.append(clamavPath+"clamscan -r C:\\");
    command.append("\r");
    command.append("\n");
    return command;
}

void gigaScan::startScan() {
    cmdPrompt.write(enterCmd().toUtf8());
}

void gigaScan::readyReadStandardOutput() {
    if (!isRunning) return;
    QByteArray data = cmdPrompt.readAllStandardOutput();
    emit output(data);
}
