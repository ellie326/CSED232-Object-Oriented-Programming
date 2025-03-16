#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>

class Widget : public QWidget
{
public:
    Widget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFocusPolicy(Qt::StrongFocus); // Enable keyboard focus for the widget
    }

protected:

};

#endif // WIDGET_H
