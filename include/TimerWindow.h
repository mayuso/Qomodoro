#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QWidget>
#include "Pomodoro.h"

namespace Ui {
class TimerWindow;
}

class TimerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWindow(QWidget *parent = nullptr);
    ~TimerWindow();

signals:
    void sg_PomodoroFinished();

public slots:
    void StartPomodoro();

    void Reset();
    void TimeOut();
    void UpdateTime(bool isPomodoroRunning);
    void PomodoroSelected(const QString & pomodoroName);

    void SetPomodoroTime(int time);
    void SetShortBreakTime(int time);
    void SetLongBreakTime(int time);


private:
    Ui::TimerWindow *ui;
    Pomodoro* m_Pomodoro;

    void StartShortBreak();
    void StartLongBreak();
};

#endif // TIMERWINDOW_H
