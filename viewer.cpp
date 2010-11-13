#include "viewer.h"
#include "image.h"
#include <QList>
#include <QStringList>
#include <QLayout>
#include <QToolButton>
#include <QLabel>
#include <QDebug>

Viewer::Viewer(QObject *parent) : QObject(parent), currentIndex(-1)
{
    connect(&mapper, SIGNAL(mapped(QObject*)), this, SLOT(imageClicked(QObject *)));
}

void Viewer::add(QString path)
{
    Image *image = NULL;

    if (path.isEmpty())
        return;

    pathList.append(path);

    image = new Image(path);
    if (image != NULL)
        images.append(image);
}

void Viewer::add(QStringList path)
{
    QString pathString;
    Image *image = NULL;
    pathList = path;

    for (int j = 0; j < path.size(); ++j) {
        pathString = path.at(j);
        image = new Image(pathString);
        if (image != NULL)
            images.append(image);
    }
}

void Viewer::startViewing(QLayout *layoutThumbs, QLayout *layoutView)
{
    QToolButton *widget = NULL;
    QPixmap pixmap;
    QImage image;

    if (images.size()) {
        if (images.size() > 5) {
            for (int j = 0; j < 5; ++j ) {
                image = images.at(j)->getThubnailImage();
                widget = new QToolButton;
                widget->setFixedSize(image.size());
                widget->setAccessibleDescription(images.at(j)->getPathString());
                pixmap = QPixmap::fromImage(image);
                widget->setIcon(pixmap);
                widget->setIconSize(pixmap.size());
                layoutThumbs->addWidget(widget);

                connect(widget, SIGNAL(clicked()), &mapper, SLOT(map()));
                mapper.setMapping(static_cast<QObject *>(widget), static_cast<QObject *>(widget));
            }
        } else {
            for (int j = 0; j < images.size(); ++j) {
                image = images.at(j)->getThubnailImage();
                widget = new QToolButton;
                widget->setFixedSize(image.size());
                widget->setAccessibleDescription(images.at(j)->getPathString());
                pixmap = QPixmap::fromImage(image);
                widget->setIcon(pixmap);
                widget->setIconSize(pixmap.size());
                layoutThumbs->addWidget(widget);

                connect(widget, SIGNAL(clicked()), &mapper, SLOT(map()));
                mapper.setMapping(static_cast<QObject *>(widget), static_cast<QObject *>(widget));
            }
        }

        QPixmap pixmap("/home/cihangir/Pictures/b.jpg");
        QLabel *label = new QLabel;
        label->setPixmap(pixmap.scaledToHeight(291));
        layoutView->addWidget(label);
    }
}

Image* Viewer::nextImage()
{
    if (currentIndex == (images.size() - 1))
        currentIndex = 0;
    else
        ++currentIndex;

    return images.at(currentIndex);
}

Image* Viewer::previousImage()
{
    if (currentIndex == 0)
        currentIndex = images.size() - 1;
    else
        --currentIndex;
    return images.at(currentIndex);
}

Image* Viewer::getImage(int index)
{
    currentIndex = index;
    return images.at(index);
}

Image* Viewer::getImage(QString &str)
{
    int index = pathList.indexOf(str);
    if (index != -1)
        return getImage(index);
    else
        return NULL;
}

QList<Image *> Viewer::getImageList(int from, int size) const
{
    if (from < 0 || from >= images.size())
        return QList<Image *>();

    int to = ((from + size) >= images.size()) ? images.size() : (from + size);
    QList<Image *> imageList;
    Image *image;
    for (int index = from; index < to; ++index) {
        image = images.at(index);
        imageList.append(image);
    }

    return imageList;
}

void Viewer::setCurrentIndexTo(QString &path)
{
    int index = pathList.indexOf(path);
    if (index == -1)
        return;
    currentIndex = index;
}

void Viewer::imageClicked(QObject *obj)
{
    QToolButton *button = static_cast<QToolButton *>(obj);
    QString path = button->accessibleDescription();

    qDebug() << path;
}
