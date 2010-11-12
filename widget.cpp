#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QDebug>
#include "image.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    currentImage(new QLabel),
    currentIndex(-1),
    thumbnailIndex(-5),
    fullScreen(false)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10, 0, 10, 0);
    ui->frameThumnailArea->setLayout(layout);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    ui->viewArea->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

    ui->viewArea->layout()->addWidget(currentImage);
    currentImage->installEventFilter(this);

    connect(&signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(imageClicked(QObject*)));
    start();
    showNextThumbnails();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    QString pathToImage = "/home/cihangir/Pictures/";
    viewer.add(pathToImage + "a.jpg");
    viewer.add(pathToImage + "b.jpg");
    viewer.add(pathToImage + "c.jpg");
    viewer.add(pathToImage + "iss.jpg");
    viewer.add(pathToImage + "japanese-airplane-doubilet_18505_990x742.jpg");
    viewer.add(pathToImage + "golden-gate.jpg");
    viewer.add(pathToImage + "353_87-1280x1024.jpg");
    viewer.add(pathToImage + "Single-White-Oak-Great-Smoky-Mountains-National-Park-Tennessee.jpg");
    viewer.add(pathToImage + "wp6_medium.jpg");
}

void Widget::next()
{
    if (currentIndex == currentImages.size() - 1) {
        showNextThumbnails();
        currentIndex = -1;
    }
    ++currentIndex;

    QString str = currentImages.at(currentIndex)->getPathString();

    currentImagePath = str;
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

void Widget::previous()
{
    if (currentIndex == 0) {
        showPreviousThumbnails();
        currentIndex = currentImages.size() - 2;
    }
    --currentIndex;

    QString str = currentImages.at(currentIndex)->getPathString();
    currentImagePath = str;
    QPixmap pixmap = QPixmap(str).scaled(400, 300, Qt::KeepAspectRatio, Qt::FastTransformation)
                     .scaled(ui->viewArea->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    currentImage->setPixmap(pixmap);
}

void Widget::showNextThumbnails()
{
    int viewersize = viewer.size();
    if (thumbnailIndex >= viewersize) {
        thumbnailIndex = 0;
    } else {
        if ((thumbnailIndex + 5) >= viewersize)
            thumbnailIndex = 0;
        else
            thumbnailIndex += 5;
    }

    currentImages = viewer.getImageList(thumbnailIndex, 5);

    QPixmap pixmap;
    QToolButton *button;
    Image *image;

    QLayoutItem *child;
    while ((child = ui->frameThumnailArea->layout()->takeAt(0)) != 0) {
        delete child->widget();
    }

    for (int j = 0; j < currentImages.size(); ++j) {
        image = currentImages.at(j);
        pixmap = image->getThumbnailPixmap();
        button = new QToolButton;
        button->setFixedSize(pixmap.size());
        button->setAccessibleName(QString::number(j));
        button->setAccessibleDescription(image->getPathString());
        button->setIcon(pixmap);
        button->setIconSize(pixmap.size());
        button->setAutoRaise(true);

        connect(button, SIGNAL(clicked()),&signalMapper, SLOT(map()));
        signalMapper.setMapping(static_cast<QObject *>(button), static_cast<QObject *>(button));

        ui->frameThumnailArea->layout()->addWidget(button);
    }

    currentIndex = 0;
    image = currentImages.at(currentIndex);
    QString path = image->getPathString();
    pixmap = QPixmap(path).scaled(400, 300, Qt::KeepAspectRatio);
    currentImage->setPixmap(pixmap);
}

void Widget::showPreviousThumbnails()
{
    int viewersize = viewer.size();
    if (thumbnailIndex <= 0 && (viewersize - 5) >= 0) {
        thumbnailIndex = viewersize - 5;
    } else {
        if ((thumbnailIndex - 5) < 0)
            thumbnailIndex = 0;
        else
            thumbnailIndex -= 5;
    }

    currentImages = viewer.getImageList(thumbnailIndex, 5);

    QPixmap pixmap;
    QToolButton *button;
    Image *image;

    QLayoutItem *child;
    while ((child = ui->frameThumnailArea->layout()->takeAt(0)) != 0)
        delete child->widget();

    for (int j = 0; j < currentImages.size(); ++j) {
        image = currentImages.at(j);
        pixmap = image->getThumbnailPixmap();
        button = new QToolButton;
        button->setFixedSize(pixmap.size());
        button->setAccessibleName(QString::number(j));
        button->setAccessibleDescription(image->getPathString());
        button->setIcon(pixmap);
        button->setIconSize(pixmap.size());
        button->setAutoRaise(true);

        connect(button, SIGNAL(clicked()),&signalMapper, SLOT(map()));
        signalMapper.setMapping(static_cast<QObject *>(button), static_cast<QObject *>(button));

        ui->frameThumnailArea->layout()->addWidget(button);
    }

    currentIndex = currentImages.size() - 1;
    image = currentImages.at(currentIndex);
    QString path = image->getPathString();
    pixmap = QPixmap(path).scaled(400, 300, Qt::KeepAspectRatio);
    currentImage->setPixmap(pixmap);
}

void Widget::imageClicked(QObject *obj)
{
    QLabel *label = static_cast<QLabel *>(obj);
    QString str = label->accessibleDescription();
    currentIndex = label->accessibleName().toInt();

    if (str.isEmpty())
        return;
    Image *image = currentImages.at(currentIndex);
    QString path = image->getPathString();
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

void Widget::on_buttonFullscreen_clicked()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QSize size = desktop->size();
    ui->frameToolbar->hide();
    ui->frameBottom->hide();
    this->showFullScreen();
    ui->viewArea->resize(size);
    ui->viewArea->move(0, 0);

    QString str = currentImages.at(currentIndex)->getPathString();
    QPixmap pixmap = QPixmap(str).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    currentImage->setPixmap(pixmap);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (fullScreen == false) {
            fullScreen = true;
            on_buttonFullscreen_clicked();
        } else {
            qDebug() << "exit from fullscreen";
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}
