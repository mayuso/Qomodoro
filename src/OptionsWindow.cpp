#include "OptionsWindow.h"
#include "ui_OptionsWindow.h"
#include "DataIO.h"

#include <QDir>

using json = nlohmann::json;

OptionsWindow::OptionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    QFile styleFile( ":/stylesheets/OptionsWindow.qss" );
    styleFile.open( QFile::ReadOnly );
    setStyleSheet( styleFile.readAll() );

    connect(ui->pomodoroTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(SetPomodoroTime(int)));
    connect(ui->shortBreakTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(SetShortBreakTime(int)));
    connect(ui->longBreakTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLongBreakTime(int)));
    connect(ui->resetValuesButton, &QPushButton::clicked, this, &OptionsWindow::ResetValues);
}



OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::LoadConfig()
{
    json config = DataIO::LoadConfig();
    if(config.size() == 0)
    {
        config["pomodoro_time"] = 25;
        config["short_break_time"] = 5;
        config["long_break_time"] = 20;

        DataIO::SaveConfig(config);
    }

    ui->pomodoroTimeSlider->setValue(config["pomodoro_time"]);
    ui->shortBreakTimeSlider->setValue(config["short_break_time"]);
    ui->longBreakTimeSlider->setValue(config["long_break_time"]);
}

void OptionsWindow::SetControlsEnabled(bool enabled)
{
    ui->pomodoroTimeSlider->setEnabled(enabled);
    ui->shortBreakTimeSlider->setEnabled(enabled);
    ui->longBreakTimeSlider->setEnabled(enabled);

}

void OptionsWindow::SetPomodoroTime(int time)
{
    ui->pomodoroTimeLabel->setText(QString::number(time));

    json config = DataIO::LoadConfig();
    config["pomodoro_time"] = time;
    DataIO::SaveConfig(config);

    emit sg_PomodoroTimeChanged(time);
}

void OptionsWindow::SetShortBreakTime(int time)
{
    ui->shortBreakTimeLabel->setText(QString::number(time));

    json config = DataIO::LoadConfig();
    config["short_break_time"] = time;
    DataIO::SaveConfig(config);

    emit sg_ShortBreakTimeChanged(time);
}

void OptionsWindow::SetLongBreakTime(int time)
{
    ui->longBreakTimeLabel->setText(QString::number(time));

    json config = DataIO::LoadConfig();
    config["long_break_time"] = time;
    DataIO::SaveConfig(config);

    emit sg_LongBreakTimeChanged(time);
}

void OptionsWindow::ResetValues()
{
    ui->pomodoroTimeSlider->setValue(25);
    ui->shortBreakTimeSlider->setValue(5);
    ui->longBreakTimeSlider->setValue(20);


    json config;
    config["pomodoro_time"] = 25;
    config["short_break_time"] = 5;
    config["long_break_time"] = 20;

    DataIO::SaveConfig(config);
}
