#include "charts/WeekChart.h"

#include "../vendor/json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <QDir>
#include <QLabel>


#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>

#include <ctime>
#include <iostream>

using json = nlohmann::json;

WeekChart::WeekChart(QStringList pomodoroDataFiles, QWidget *parent) :
    QChartView(parent)
{
    QHorizontalBarSeries *series = LoadData(pomodoroDataFiles);
    QChart* chart = CreateChart(series);
    setChart(chart);

    setRenderHint(QPainter::Antialiasing);
    setMaximumHeight(500);
    setMaximumWidth(400);
}

WeekChart::~WeekChart()
{
}

QHorizontalBarSeries* WeekChart::LoadData(QStringList pomodoroDataFiles)
{
    QHorizontalBarSeries *series = new QHorizontalBarSeries();

    foreach(QString filename, pomodoroDataFiles) {

        try {
            std::ifstream ifs("./data/" + filename.toStdString());
            json data =  json::parse(ifs);

            int* amountOfPomodorosPerWeekday = new int[7]{0,0,0,0,0,0,0};
            for (json& pomodoroData : data) {
                QString date = QString::fromStdString(pomodoroData["date"]);

                int year = date.split("-")[0].toInt();
                int month = date.split("-")[1].toInt();
                int day = date.split("-")[2].toInt();

                std::tm time_in = { 0, 0, 0, day, month - 1, year - 1900 };
                std::time_t time_temp = std::mktime(&time_in);
                const std::tm * time_out = std::localtime(&time_temp);

                //Monday == 0, Tuesday = 1, and so on ...
                amountOfPomodorosPerWeekday[time_out->tm_wday] += 1;
            }

            QBarSet *set = new QBarSet(filename.replace(".json", ""));
            *set << amountOfPomodorosPerWeekday[1] << amountOfPomodorosPerWeekday[2] << amountOfPomodorosPerWeekday[3] << amountOfPomodorosPerWeekday[4];
            *set << amountOfPomodorosPerWeekday[5] << amountOfPomodorosPerWeekday[6] << amountOfPomodorosPerWeekday[0];

            series->append(set);
        } catch (json::exception& e) {
        }
    }
    return series;
}

QChart* WeekChart::CreateChart(QHorizontalBarSeries *series)
{
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pomodoros by day");
    chart->setBackgroundVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QStringList categories;
    categories << "Mon" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat" << "Sun";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->setMinimumHeight(minimumHeight());
    chart->setMaximumHeight(maximumHeight());
    return chart;
}
