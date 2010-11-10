#include "image.h"
#include <QImage>
#include <QPixmap>

Image::Image()
{
}

Image::Image(QString &pathString) : path(pathString)
{
}

void Image::setPath(QString pathString)
{
    path = pathString;
}

QString Image::getPathString() const
{
    return path;
}

QImage Image::getThubnailImage() const
{
    QImage image(path), result;
    result = image.scaled(400, 300, Qt::KeepAspectRatio).scaled(
            140, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation
            );

    return result;
}

QPixmap Image::getThumbnailPixmap() const
{
    return QPixmap::fromImage(getThubnailImage());
}
