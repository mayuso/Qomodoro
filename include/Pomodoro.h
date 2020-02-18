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

    time_t getTimeLeft();
    bool isActive();

    void startPomodoro();
    void startShortBreak();
    void startLongBreak();
    void pause();
    void resume();

    QString GetName() const;
    void SetName(const QString &value);

    int pomodoroCounter;
    bool isPomodoroRunning;

    int GetPomodoroDurationMinutes() const;
    void SetPomodoroDurationMinutes(int value);

    int GetShortBreakDurationMinutes() const;
    void SetShortBreakDurationMinutes(int value);

    int GetLongBreakDurationMinutes() const;
    void SetLongBreakDurationMinutes(int value);

signals:
    void tick(bool isPomodoroRunning);
    void timeout();

private slots:
    void timerTicked();


private:
    nlohmann::json MergeJSons(const nlohmann::json &a, const nlohmann::json &b);

    time_t time_left;
    QTimer* timer;
    QString name;
    nlohmann::json jsonData;

    int pomodoroDurationMinutes, shortBreakDurationMinutes, longBreakDurationMinutes;


};

#endif // POMODORO_H
