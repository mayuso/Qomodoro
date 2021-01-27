#include "charts/DayChart.h"

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

DayChart::DayChart(QStringList pomodoroDataFiles, QWidget *parent) :
    QChartView(parent)
{
    setMaximumHeight(300);
    setMaximumWidth(parent->width());
    QBarSeries *series = LoadData(pomodoroDataFiles);
    QChart* chart = CreateChart(series);
    setChart(chart);

    setRenderHint(QPainter::Antialiasing);
}

DayChart::~DayChart()
{
}

QBarSeries* DayChart::LoadData(QStringList pomodoroDataFiles)
{
    QBarSeries *series = new QBarSeries();

    foreach(QString filename, pomodoroDataFiles) {

        try {
            std::ifstream ifs("./data/" + filename.toStdString());
            json data =  json::parse(ifs);

            int* amountOfPomodorosPerHour = new int[24]{0};
            for (json& pomodoroData : data) {
                QString time = QString::fromStdString(pomodoroData["end_time"]);

                int hour = time.split(":")[0].toInt();

                //00:00 == 0, 00:01 == 1, and so on ...
                amountOfPomodorosPerHour[hour] += 1;
            }

            QBarSet *set = new QBarSet(filename.replace(".json", ""));
            for(int hourIndex = 0; hourIndex < 24; ++hourIndex)
            {
                *set << amountOfPomodorosPerHour[hourIndex];
            }

            series->append(set);
        } catch (json::exception& e) {
        }
    }
    return series;
}

QChart* DayChart::CreateChart(QBarSeries *series)
{
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pomodoros by hour");
    chart->setBackgroundVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "00:00" << "01:00" << "02:00" << "03:00" << "04:00" << "05:00" << "06:00";
    categories << "07:00" << "08:00" << "09:00" << "10:00" << "11:00" << "12:00" << "13:00";
    categories << "14:00" << "15:00" << "16:00" << "17:00" << "18:00" << "19:00" << "20:00";
    categories << "21:00" << "22:00" << "23:00" << "24:00";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->setMinimumHeight(minimumHeight());
    chart->setMaximumHeight(maximumHeight());
    return chart;
}
