#include "viewer.h"
#include "image.h"
#include <QList>
#include <QStringList>
#include <QLayout>
#include <QToolButton>
#include <QLabel>
#include <QDebug>

Viewer::Viewer(QObject *parent) : QObject(parent)
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

void Viewer::startViewing(QLayout *layoutThumbs, QLabel *viewArea)
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

        //viewArea->resize(400, 290);
        viewArea->setPixmap(images.first()->getPathString());
//        viewArea->resize(viewArea->pixmap()->size().width() * 291 / viewArea->pixmap()->size().height(),
//                         291);
    }
}

void Viewer::next(QLayout *)
{

}

void Viewer::imageClicked(QObject *)
{
    qDebug() << "slot invoked";
}
