#ifndef WEEKCHART_H
#define WEEKCHART_H

#include <QWidget>
#include <QChartView>
#include <QHorizontalBarSeries>


QT_CHARTS_USE_NAMESPACE


class WeekChart: public QChartView
{
    Q_OBJECT

public:
    explicit WeekChart(QStringList pomodoroDataFiles, QWidget *parent = nullptr);
    ~WeekChart();

private:
    QHorizontalBarSeries* LoadData(QStringList pomodoroDataFiles);
    QChart* CreateChart(QHorizontalBarSeries *series);
};

#endif // WEEKCHART_H
