#include "OptionsWindow.h"
#include "ui_OptionsWindow.h"

#include <QDir>

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

void OptionsWindow::SetControlsEnabled(bool enabled)
{
    ui->pomodoroTimeSlider->setEnabled(enabled);
    ui->shortBreakTimeSlider->setEnabled(enabled);
    ui->longBreakTimeSlider->setEnabled(enabled);
}

void OptionsWindow::SetPomodoroTime(int time)
{
    ui->pomodoroTimeLabel->setText(QString::number(time));
    emit sg_PomodoroTimeChanged(time);
}

void OptionsWindow::SetShortBreakTime(int time)
{
    ui->shortBreakTimeLabel->setText(QString::number(time));
    emit sg_ShortBreakTimeChanged(time);
}

void OptionsWindow::SetLongBreakTime(int time)
{
    ui->longBreakTimeLabel->setText(QString::number(time));
    emit sg_LongBreakTimeChanged(time);
}

void OptionsWindow::ResetValues()
{
    ui->pomodoroTimeSlider->setValue(25);
    ui->shortBreakTimeSlider->setValue(5);
    ui->longBreakTimeSlider->setValue(20);
    //SetPomodoroTime(25);
    //SetShortBreakTime(25);
    //SetLongBreakTime(25);
}
