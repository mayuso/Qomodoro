#ifndef CIRCULARTIMER_H
#define CIRCULARTIMER_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "Pomodoro.h"
#include "TopBarTitle.h"

namespace Ui {
class CircularTimer;
}

class CircularTimer : public QWidget
{
    Q_OBJECT

public:
    explicit CircularTimer(QWidget *parent = nullptr);
    ~CircularTimer();

    qreal p; // progress 0.0 to 1.0

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void upd(qreal pp);

    void SetCircularBarColor(QColor*);


public slots:
    void StartPomodoro();

    void Reset();
    void TimeOut();
    void UpdateTime();
    void PomodoroSelected(const QString & pomodoroName);

    void SetPomodoroTime(int time);
    void SetShortBreakTime(int time);
    void SetLongBreakTime(int time);

    void PomodoroFinished();
    void BreakFinished();
    void PomodoroStarted();
    void BreakStarted();


signals:
    void sg_TimerFinished();

private:
    Ui::CircularTimer *ui;
    TopBarTitle *m_TitleBar;

    Pomodoro* m_Pomodoro;
    QColor *m_CircularBarColor;

};

#endif // CIRCULARTIMER_H
