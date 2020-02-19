#ifndef WEEKCHART_H
#define WEEKCHART_H

#include <QWidget>
#include <QChartView>
#include <QBarSeries>


QT_CHARTS_USE_NAMESPACE


class WeekChart: public QChartView
{
    Q_OBJECT

public:
    explicit WeekChart(QStringList pomodoroDataFiles, QWidget *parent = nullptr);
    ~WeekChart();

private:
    QBarSeries* LoadData(QStringList pomodoroDataFiles);
    QChart* CreateChart(QBarSeries *series);
};

#endif // WEEKCHART_H
