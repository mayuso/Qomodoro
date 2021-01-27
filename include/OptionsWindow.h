#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

public slots:
    void SetControlsEnabled(bool enabled);

    void SetPomodoroTime(int time);
    void SetShortBreakTime(int time);
    void SetLongBreakTime(int time);

signals:
    void sg_PomodoroTimeChanged(int);
    void sg_ShortBreakTimeChanged(int);
    void sg_LongBreakTimeChanged(int);

private:
    Ui::OptionsWindow *ui;


};

#endif // OPTIONSWINDOW_H
