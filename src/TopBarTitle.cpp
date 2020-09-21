#include "TopBarTitle.h"
#include "MainWindow.h"

#include <QWindow>
#include <QMouseEvent>
#include <QDebug>

TopBarTitle::TopBarTitle(QWidget *parent) :
     QLabel(parent)
{

    setText("Qomodoro");
    setFixedHeight(35);
    setAlignment(Qt::AlignCenter);
    setAccessibleName("titleLabel");
}


void TopBarTitle::mousePressEvent(QMouseEvent *event)
{
    m_Start = mapToGlobal(event->pos());
    m_Pressing = true;
}


void TopBarTitle::mouseMoveEvent(QMouseEvent *event)
{
    if(m_Pressing && !parentWidget()->parentWidget()->parentWidget()->isMaximized())
    {
        m_End = mapToGlobal(event->pos());
        QPoint movement = m_End-m_Start;
        parentWidget()->parentWidget()->parentWidget()->setGeometry(mapToGlobal(movement).x(),
                            mapToGlobal(movement).y(),
                            ((MainWindow*)parentWidget()->parentWidget()->parentWidget())->width(),
                            ((MainWindow*)parentWidget()->parentWidget()->parentWidget())->height());
        m_Start = m_End;
    }

}




void  TopBarTitle::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressing = false;
}


void  TopBarTitle::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(parentWidget()->parentWidget()->parentWidget()->isMaximized())
        parentWidget()->parentWidget()->parentWidget()->showNormal();
    else
        parentWidget()->parentWidget()->parentWidget()->showMaximized();;
}

