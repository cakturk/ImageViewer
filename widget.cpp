#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10, 0, 10, 0);
    ui->frameThumnailArea->setLayout(layout);

    layout = new QHBoxLayout;
    ui->viewArea->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

    connect(ui->buttonNext,SIGNAL(clicked()), this, SLOT(next()));

    start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    QString path = "/home/cihangir/Pictures/";
    viewer.add(path + "a.jpg");
    viewer.add(path + "b.jpg");
    viewer.add(path + "c.jpg");
    viewer.startViewing(ui->frameThumnailArea->layout(), ui->viewArea->layout());
}

void Widget::next()
{
    viewer.next(ui->viewArea->layout());
}

void Widget::previous()
{
}

void Widget::imageClicked(QObject *)
{
}
