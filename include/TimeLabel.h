#ifndef QTIMELABEL_H
#define QTIMELABEL_H

#include <QLabel>

class TimeLabel : public QLabel
{
    Q_OBJECT

public:
    TimeLabel(QWidget* parent = nullptr);
    ~TimeLabel();

    void SetTime(time_t time, bool isPomodoroRunning);
    void SetText(const QString &);


private:
    QString FormatTime(time_t seconds);
};

#endif // QTIMELABEL_H
