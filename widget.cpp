#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "image.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    currentImage(new QLabel),
    currentIndex(-6)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10, 0, 10, 0);
    ui->frameThumnailArea->setLayout(layout);

    layout = new QHBoxLayout;
    ui->viewArea->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

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
    viewer.add(path + "japanese-airplane-doubilet_18505_990x742.jpg");
    viewer.add(path + "golden-gate.jpg");
    viewer.add(path + "353_87-1280x1024.jpg");
    viewer.add(path + "Single-White-Oak-Great-Smoky-Mountains-National-Park-Tennessee.jpg");
    viewer.add(path + "wp6_medium.jpg");
}

void Widget::next()
{
    ++currentIndex;
    QString str = viewer.nextImage()->getPathString();
    currentImagePath = str;
    //QPixmap pixmap = QPixmap(str).scaledToHeight(ui->viewArea->height());
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

void Widget::previous()
{
    --currentIndex;
    QString str = viewer.previousImage()->getPathString();
    currentImagePath = str;
//    QPixmap pixmap = QPixmap(str).scaledToHeight(ui->viewArea->height());
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

void Widget::showNextThumbnails()
{
    currentIndex += 5;
    QList<Image *> list = viewer.getImageList(currentIndex, 5);

    QPixmap pixmap;
    QToolButton *button;
    Image *image;

    QLayoutItem *child;
    while ((child = ui->frameThumnailArea->layout()->takeAt(0)) != 0) {
        delete child->widget();
    }

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
    QList<Image *> list = viewer.getImageList(currentIndex - 5, 5);
    currentIndex -= 5;
    if (currentIndex < 0)
        currentIndex = list.size() - 5;

    QPixmap pixmap;
    QToolButton *button;
    Image *image;

    QLayoutItem *child;
    while ((child = ui->frameThumnailArea->layout()->takeAt(0)) != 0)
        delete child->widget();

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

void Widget::on_buttonPreviousThumbs_clicked()
{
    showPreviousThumbnails();
}
