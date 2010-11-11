#ifndef VIEWER_H
#define VIEWER_H

#include <QList>
#include <QStringList>
#include <QSignalMapper>

class QLabel;
class Image;
class QLayout;
class Viewer : public QObject
{
    Q_OBJECT

public:
    Viewer(QObject *parent = 0);

    Image* nextImage();
    Image* previousImage();
    Image* getImage(int index);
    Image* getImage(QString &str);
    QList<Image *> getImageList(int from, int size) const;

    void add(QString path);
    void add(QStringList path);
    void startViewing(QLayout *layoutThumbs, QLayout *layoutView);
    void setCurrentIndexTo(QString &path);

private:
    QList<Image *> images;
    QStringList pathList;
    QSignalMapper mapper;
    quint16 currentIndex;

private slots:
    void imageClicked(QObject *);
};

#endif // VIEWER_H
