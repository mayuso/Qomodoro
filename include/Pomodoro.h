#ifndef POMODORO_H
#define POMODORO_H

#include "nlohmann/json.hpp"
#include <QObject>
#include <QTimer>
#include <time.h>


class Pomodoro : public QObject
{
    Q_OBJECT

public:
    explicit Pomodoro(QObject *parent = nullptr);
    ~Pomodoro();

    int GetTimeLeft();
    bool IsActive();

    void StartPomodoro();

    void Reset();

    QString GetName() const;
    void SetName(const QString &value);

    int GetPomodoroDurationMinutes() const;
    void SetPomodoroDurationMinutes(int value);

    int GetShortBreakDurationMinutes() const;
    void SetShortBreakDurationMinutes(int value);

    int GetLongBreakDurationMinutes() const;
    void SetLongBreakDurationMinutes(int value);

signals:
    void sg_Tick(bool isPomodoroRunning);
    void sg_Timeout();
    void sg_BreakStarted();
    void sg_BreakFinished();
    void sg_PomodoroStarted();
    void sg_PomodoroFinished();

private slots:
    void TimerTicked();

private:
    nlohmann::json MergeJSons(const nlohmann::json &a, const nlohmann::json &b);
    void StartBreak();
    void StartShortBreak();
    void StartLongBreak();

private:
    int m_TimeLeft;
    QTimer* m_Timer;
    QString m_Name;

    int m_PomodoroDurationMinutes, m_ShortBreakDurationMinutes, m_LongBreakDurationMinutes;

    int m_PomodoroCounter;
    bool m_IsPomodoroRunning;
};

#endif // POMODORO_H
