#ifndef QTIMELABEL_H
#define QTIMELABEL_H

#include <QLabel>

class TimeLabel : public QLabel
{
    Q_OBJECT

public:
    TimeLabel(QWidget* parent = nullptr);
    ~TimeLabel();

    void setTime(time_t time, bool isPomodoroRunning);
    void setText(const QString &);


private:
    QString formatTime(time_t seconds);

    QFont* font;

};

#endif // QTIMELABEL_H
