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

    void Pause();
    void Resume();
    void TimeOut();
    void UpdateTime(bool isPomodoroRunning);
    void PomodoroSelected(const QString & pomodoroName);

private:
    Ui::TimerWindow *ui;
    Pomodoro* m_Pomodoro;

    void StartShortBreak();
    void StartLongBreak();
};

#endif // TIMERWINDOW_H
