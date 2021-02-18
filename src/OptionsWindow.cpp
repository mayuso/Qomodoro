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

    connect(ui->pomodoroTime, SIGNAL(valueChanged(int)), this, SLOT(SetPomodoroTime(int)));
    connect(ui->shortBreakTime, SIGNAL(valueChanged(int)), this, SLOT(SetShortBreakTime(int)));
    connect(ui->longBreakTime, SIGNAL(valueChanged(int)), this, SLOT(SetLongBreakTime(int)));

}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::SetControlsEnabled(bool enabled)
{
    ui->pomodoroTime->setEnabled(enabled);
    ui->shortBreakTime->setEnabled(enabled);
    ui->longBreakTime->setEnabled(enabled);
}

void OptionsWindow::SetPomodoroTime(int time)
{
    emit sg_PomodoroTimeChanged(time);
}

void OptionsWindow::SetShortBreakTime(int time)
{
    emit sg_ShortBreakTimeChanged(time);
}

void OptionsWindow::SetLongBreakTime(int time)
{
    emit sg_LongBreakTimeChanged(time);
}
