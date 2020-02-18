#ifndef BARCHART_H
#define BARCHART_H

#include <QWidget>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE


class WeekChart: public QChartView
{
    Q_OBJECT

public:
    explicit WeekChart(QStringList pomodoroDataFiles, QWidget *parent = nullptr);
    ~WeekChart();
};

#endif // BARCHART_H
