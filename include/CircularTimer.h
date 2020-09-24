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



public slots:
    void StartPomodoro();

    void Reset();
    void TimeOut();
    void UpdateTime(bool isPomodoroRunning);
    void PomodoroSelected(const QString & pomodoroName);

    void SetPomodoroTime(int time);
    void SetShortBreakTime(int time);
    void SetLongBreakTime(int time);

signals:
    void sg_TimerFinished();

private:
    Ui::CircularTimer *ui;
    TopBarTitle *m_TitleBar;

    Pomodoro* m_Pomodoro;

};

#endif // CIRCULARTIMER_H
