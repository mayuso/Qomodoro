#include "TimerWindow.h"
#include "ui_TimerWindow.h"

#include "nlohmann/json.hpp"

#include <QVBoxLayout>
#include <QShortcut>
#include <QDir>
#include <fstream>


using json = nlohmann::json;

TimerWindow::TimerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWindow)
{
    this->pomodoro = new Pomodoro();
    ui->setupUi(this);
    setStyleSheet("background-color: #222; color: white");


    ui->timeLabel->setText(QString::number(this->pomodoro->GetPomodoroDurationMinutes())+":00");


    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);
    QList<QString> pomodoroNames;
    foreach(QString filename, pomodoroDataFiles) {
        pomodoroNames.append(filename.replace(".json", ""));
    }

    ui->name->addItems(pomodoroNames);
    ui->name->setEditable(true);
    ui->name->setEditText("");
    ui->name->setStyleSheet("background-color: #444; color: white");

    connect(ui->pomodoroButton, &QPushButton::clicked, this, &TimerWindow::startPomodoro);
    connect(ui->pauseButton, &QPushButton::clicked, this, &TimerWindow::pause);
    connect(ui->name, &QComboBox::currentTextChanged, this, &TimerWindow::PomodoroSelected);
    connect(this->pomodoro, &Pomodoro::tick, this, &TimerWindow::updateTime);
    connect(this->pomodoro, &Pomodoro::timeout, this, &TimerWindow::timeOut);

    ui->pomodoroButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);

    QString foreground = "white";
    QString background = "#444";
    QString disabledForeground = "grey";
    QString disabledBackground = "#222";


    ui->pomodoroButton->setStyleSheet(":enabled { color: " + foreground
                                 + "; background-color: " + background
                                 + " } :disabled { color: " + disabledForeground
                                 + "; background-color: " + disabledBackground + " }");
    ui->pauseButton->setStyleSheet(":enabled { color: " + foreground
                                 + "; background-color: " + background
                                 + " } :disabled { color: " + disabledForeground
                                 + "; background-color: " + disabledBackground + " }");
}

TimerWindow::~TimerWindow()
{
    delete ui;
}

void TimerWindow::PomodoroSelected(const QString & pomodoroName)
{
    this->pomodoro->SetName(pomodoroName);

    ui->pomodoroButton->setEnabled(pomodoroName != QString(""));

}

void TimerWindow::timeOut()
{
    ui->pomodoroButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    emit sg_PomodoroFinished();
}

void TimerWindow::updateTime(bool isPomodoroRunning)
{
    ui->timeLabel->setTime(pomodoro->getTimeLeft(), isPomodoroRunning);
}

void TimerWindow::startPomodoro() {

    ui->pomodoroButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    pomodoro->startPomodoro();
}

void TimerWindow::pause() {

    if (pomodoro->isActive()) {
        pomodoro->pause();
        ui->pauseButton->setText(QString("Resume"));
    } else {
        resume();
        ui->pauseButton->setText(QString("Pause"));
    }
}

void TimerWindow::resume() {
    pomodoro->resume();
}
