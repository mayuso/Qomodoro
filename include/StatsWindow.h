#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include <QWidget>
#include <QChartView>
#include <QPushButton>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class StatsWindow;
}

class StatsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatsWindow(QWidget *parent = nullptr);
    ~StatsWindow();

private:
    Ui::StatsWindow *ui;

};

#endif // STATSWINDOW_H
