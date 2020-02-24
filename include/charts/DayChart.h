#ifndef DAYCHART_H
#define DAYCHART_H

#include <QWidget>
#include <QChartView>
#include <QBarSeries>


QT_CHARTS_USE_NAMESPACE


class DayChart: public QChartView
{
    Q_OBJECT

public:
    explicit DayChart(QStringList pomodoroDataFiles, QWidget *parent = nullptr);
    ~DayChart();

private:
    QBarSeries* LoadData(QStringList pomodoroDataFiles);
    QChart* CreateChart(QBarSeries *series);
};

#endif // DAYCHART_H
