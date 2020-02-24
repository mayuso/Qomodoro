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
    m_Pomodoro = new Pomodoro();
    ui->setupUi(this);
    setStyleSheet("background-color: #222; color: white");

    ui->timeLabel->setText(QString::number(m_Pomodoro->GetPomodoroDurationMinutes())+":00");

    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);
    QList<QString> pomodoroNames;
    foreach(QString filename, pomodoroDataFiles) {
        pomodoroNames.append(filename.replace(".json", ""));
    }
    ui->pomodoroNameComboBox->addItems(pomodoroNames);
    ui->pomodoroNameComboBox->setEditText("");
    ui->pomodoroNameComboBox->setStyleSheet("background-color: #444; color: white");
    QAbstractItemModel* model = ui->pomodoroNameComboBox->model();
    for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
        QModelIndex index = model->index(i, 0);
        model->setData(index, QSize(50, 50), Qt::SizeHintRole);
    }


    connect(ui->pomodoroButton, &QPushButton::clicked, this, &TimerWindow::StartPomodoro);
    connect(ui->resetButton, &QPushButton::clicked, this, &TimerWindow::Reset);
    connect(ui->pomodoroNameComboBox, &QComboBox::currentTextChanged, this, &TimerWindow::PomodoroSelected);

    connect(ui->pomodoroTime, SIGNAL(valueChanged(int)), this, SLOT(SetPomodoroTime(int)));
    connect(ui->shortBreakTime, SIGNAL(valueChanged(int)), this, SLOT(SetShortBreakTime(int)));
    connect(ui->longBreakTime, SIGNAL(valueChanged(int)), this, SLOT(SetLongBreakTime(int)));

    connect(m_Pomodoro, &Pomodoro::sg_Tick, this, &TimerWindow::UpdateTime);
    connect(m_Pomodoro, &Pomodoro::sg_Timeout, this, &TimerWindow::TimeOut);

    ui->pomodoroButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    QString foreground = "white";
    QString background = "#444";
    QString disabledForeground = "grey";
    QString disabledBackground = "#222";

    QString darkStyleSheet = ":enabled { color: " + foreground
            + "; background-color: " + background
            + " } :disabled { color: " + disabledForeground
            + "; background-color: " + disabledBackground + " }";
    ui->pomodoroButton->setStyleSheet(darkStyleSheet);
    ui->resetButton->setStyleSheet(darkStyleSheet);
    ui->pomodoroTime->setStyleSheet(darkStyleSheet);
    ui->shortBreakTime->setStyleSheet(darkStyleSheet);
    ui->longBreakTime->setStyleSheet(darkStyleSheet);


    ui->pomodoroButton->setEnabled(ui->pomodoroNameComboBox->currentText() != QString(""));

}

TimerWindow::~TimerWindow()
{
    delete ui;
}

void TimerWindow::PomodoroSelected(const QString& pomodoroName)
{
    m_Pomodoro->SetName(pomodoroName);

    ui->pomodoroButton->setEnabled(pomodoroName != QString(""));
}

void TimerWindow::SetPomodoroTime(int time)
{
    m_Pomodoro->SetPomodoroDurationMinutes(time);
    ui->timeLabel->SetTime(m_Pomodoro->GetTimeLeft(), true);
}

void TimerWindow::SetShortBreakTime(int time)
{
    m_Pomodoro->SetShortBreakDurationMinutes(time);
}

void TimerWindow::SetLongBreakTime(int time)
{
    m_Pomodoro->SetLongBreakDurationMinutes(time);
}

void TimerWindow::TimeOut()
{
    ui->pomodoroTime->setEnabled(true);
    ui->shortBreakTime->setEnabled(true);
    ui->longBreakTime->setEnabled(true);
    ui->pomodoroButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
    emit sg_PomodoroFinished();
}

void TimerWindow::UpdateTime(bool isPomodoroRunning)
{
    ui->timeLabel->SetTime(m_Pomodoro->GetTimeLeft(), isPomodoroRunning);
}

void TimerWindow::StartPomodoro()
{
    ui->pomodoroTime->setEnabled(false);
    ui->shortBreakTime->setEnabled(false);
    ui->longBreakTime->setEnabled(false);
    ui->pomodoroButton->setEnabled(false);
    ui->resetButton->setEnabled(true);
    m_Pomodoro->StartPomodoro();
}

void TimerWindow::Reset()
{
    ui->pomodoroTime->setEnabled(true);
    ui->shortBreakTime->setEnabled(true);
    ui->longBreakTime->setEnabled(true);
    ui->pomodoroButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
    m_Pomodoro->Reset();
    ui->timeLabel->SetTime(m_Pomodoro->GetTimeLeft(), true);
}
