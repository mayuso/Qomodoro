#ifndef TimerWindow_H
#define TimerWindow_H

#include "Pomodoro.h"
#include "TopBarTitle.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSystemTrayIcon>


namespace Ui {
class TimerWindow;
}

class TimerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TimerWindow(QWidget *parent = nullptr);
    ~TimerWindow();

    void paintEvent(QPaintEvent *) override;
    void updateProgress(qreal newProgress);
    void SetCircularBarColor(QColor*);

    qreal m_Progress; // progress 0.0 to 1.0

public slots:
    void StartPomodoro();

    void Reset();
    void TimeOut();
    void UpdateTime();

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
    void UpdateTimeLabel();

    Ui::TimerWindow *ui;
    TopBarTitle *m_TitleBar;

    Pomodoro* m_Pomodoro;
    QColor *m_CircularBarColor;

};

#endif // TimerWindow_H
