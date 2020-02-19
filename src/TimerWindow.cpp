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
    auto rows = model->rowCount(QModelIndex());
    for (int i = 0; i < rows; ++i) {
    QModelIndex index = model->index(i, 0);
    model->setData(index, QSize(50, 50), Qt::SizeHintRole);
    }



    connect(ui->pomodoroButton, &QPushButton::clicked, this, &TimerWindow::StartPomodoro);
    connect(ui->pauseButton, &QPushButton::clicked, this, &TimerWindow::Pause);
    connect(ui->pomodoroNameComboBox, &QComboBox::currentTextChanged, this, &TimerWindow::PomodoroSelected);
    connect(m_Pomodoro, &Pomodoro::sg_Tick, this, &TimerWindow::UpdateTime);
    connect(m_Pomodoro, &Pomodoro::sg_Timeout, this, &TimerWindow::TimeOut);

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

void TimerWindow::PomodoroSelected(const QString& pomodoroName)
{
    m_Pomodoro->SetName(pomodoroName);

    ui->pomodoroButton->setEnabled(pomodoroName != QString(""));
}

void TimerWindow::TimeOut()
{
    ui->pomodoroButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    emit sg_PomodoroFinished();
}

void TimerWindow::UpdateTime(bool isPomodoroRunning)
{
    ui->timeLabel->SetTime(m_Pomodoro->GetTimeLeft(), isPomodoroRunning);
}

void TimerWindow::StartPomodoro()
{
    ui->pomodoroButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    m_Pomodoro->StartPomodoro();
}

void TimerWindow::Pause()
{
    if (m_Pomodoro->IsActive()) {
        m_Pomodoro->Pause();
        ui->pauseButton->setText(QString("Resume"));
    } else {
        Resume();
        ui->pauseButton->setText(QString("Pause"));
    }
}

void TimerWindow::Resume()
{
    m_Pomodoro->Resume();
}
