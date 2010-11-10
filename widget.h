#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "viewer.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void start();

    Ui::Widget *ui;
    Viewer viewer;
};

#endif // WIDGET_H
