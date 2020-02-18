#include "StatsWindow.h"
#include "ui_StatsWindow.h"

#include "charts/WeekChart.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <QDir>
#include <QDebug>
#include <QLabel>


using json = nlohmann::json;

StatsWindow::StatsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #222; color: white");

    QDir directory("data");
    QStringList pomodoroDataFiles = directory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);
    ui->contentsLayout->addWidget(new WeekChart(pomodoroDataFiles, this));
}

StatsWindow::~StatsWindow()
{
    delete ui;
}
