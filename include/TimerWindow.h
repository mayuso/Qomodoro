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
    void startPomodoro();

    void pause();
    void resume();
    void timeOut();
    void updateTime(bool isPomodoroRunning);
    void PomodoroSelected(const QString & pomodoroName);

private:
    Ui::TimerWindow *ui;
    Pomodoro* pomodoro;

    void startShortBreak();
    void startLongBreak();



};

#endif // TIMERWINDOW_H
