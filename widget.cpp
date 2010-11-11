#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "image.h"

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

    currentImage = new QLabel;
    ui->viewArea->layout()->addWidget(currentImage);

    connect(&signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(imageClicked(QObject*)));
    start();
    next();
    showNextThumbnails();

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
    viewer.add(path + "iss.jpg");
}

void Widget::next()
{
    QString str = viewer.nextImage()->getPathString();
    currentImagePath = str;
    //QPixmap pixmap = QPixmap(str).scaledToHeight(ui->viewArea->height());
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

void Widget::previous()
{
    QString str = viewer.previousImage()->getPathString();
    currentImagePath = str;
//    QPixmap pixmap = QPixmap(str).scaledToHeight(ui->viewArea->height());
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

void Widget::showNextThumbnails()
{
    QList<Image *> list = viewer.getImageList(0, 5);
    QPixmap pixmap;
    QToolButton *button;
    Image *image;

    for (int j = 0; j < list.size(); ++j) {
        image = list.at(j);
        pixmap = image->getThumbnailPixmap();
        button = new QToolButton;
        button->setFixedSize(pixmap.size());
        button->setAccessibleDescription(image->getPathString());
        button->setIcon(pixmap);
        button->setIconSize(pixmap.size());

        connect(button, SIGNAL(clicked()),&signalMapper, SLOT(map()));
        signalMapper.setMapping(static_cast<QObject *>(button), static_cast<QObject *>(button));

        ui->frameThumnailArea->layout()->addWidget(button);
    }
}

void Widget::showPreviousThumbnails()
{
}

void Widget::imageClicked(QObject *obj)
{
    QLabel *label = static_cast<QLabel *>(obj);
    QString str = label->accessibleDescription();

    if (str.isEmpty())
        return;
    Image *image = viewer.getImage(str);
    QString path = image->getPathString();
//    QPixmap pixmap = QPixmap(path).scaledToHeight(ui->viewArea->height());
    QPixmap pixmap = QPixmap(path).scaled(400, 300, Qt::KeepAspectRatio);
    currentImage->setPixmap(pixmap);

    viewer.setCurrentIndexTo(str);
}

void Widget::on_buttonNext_clicked()
{
    next();
}

void Widget::on_buttonPrevious_clicked()
{
    previous();
}

void Widget::on_buttonNextThumbs_clicked()
{
    showNextThumbnails();
}
