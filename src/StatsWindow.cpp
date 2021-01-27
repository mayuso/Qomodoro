#include "StatsWindow.h"
#include "ui_StatsWindow.h"

#include "charts/WeekChart.h"
#include "charts/DayChart.h"

#include <fstream>
#include <QDir>


StatsWindow::StatsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);

    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);

    //ui->statsLayout->insertWidget(0,new DayChart(pomodoroDataFiles, this));
    ui->statsLayout->insertWidget(0,new WeekChart(pomodoroDataFiles, this));
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
