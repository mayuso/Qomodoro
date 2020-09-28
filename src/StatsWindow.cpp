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
    ui->contentsLayout->addWidget(new WeekChart(pomodoroDataFiles, this));
    ui->contentsLayout->addWidget(new DayChart(pomodoroDataFiles, this));
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
