#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

class QImage;
class QPixmap;
class Image
{
public:
    Image();
    Image(QString &pathString);

    void setPath(QString pathString);
    QString getPathString() const;
    QImage getThubnailImage() const;
    QPixmap getThumbnailPixmap() const;

private:
    QString path;
};

#endif // IMAGE_H
