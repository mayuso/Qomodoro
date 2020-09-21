#ifndef TOPBARTITLE_H
#define TOPBARTITLE_H

#include <QLabel>


class TopBarTitle : public QLabel
{
    Q_OBJECT

public:
    explicit TopBarTitle(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void mouseDoubleClickEvent(QMouseEvent * event) override;

private:
    QPoint m_Start, m_End;
    bool m_Pressing;
};

#endif // TOPBARTITLE_H
