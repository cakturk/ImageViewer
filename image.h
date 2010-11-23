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

    void setPath(QString &pathString);
    QString getPathString() const;
    QImage getThubnailImage() const;
    QPixmap getThumbnailPixmap() const;
    QImage scaled() const;
    QPixmap scaledPixmap() const;

private:
    QString path;
    int value;
};

#endif // IMAGE_H
