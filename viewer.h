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

    void next(QLayout *layout);
    void previous(QLayout *layout);
    void add(QString path);
    void add(QStringList path);
    void startViewing(QLayout *layoutThumbs, QLayout *layoutView);

private:
    QList<Image *> images;
    QStringList pathList;
    QSignalMapper mapper;

    quint16 pointer;

private slots:
    void imageClicked(QObject *);
};

#endif // VIEWER_H
