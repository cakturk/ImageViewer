#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "viewer.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    void start();
    void startSlideShow();
    void stopSlideShow();
    void timerEvent(QTimerEvent *);

    Ui::Widget *ui;
    Viewer viewer;
    QLabel *currentImage;
    QSignalMapper signalMapper;
    QString currentImagePath;
    QList<const Image *> currentImages;
    int currentIndex;
    int thumbnailIndex;
    int timerId;
    bool fullScreen;

private slots:
    void on_buttonSlideshow_clicked();
    void on_buttonFullscreen_clicked();
    void on_buttonPreviousThumbs_clicked();
    void on_buttonNextThumbs_clicked();
    void on_buttonPrevious_clicked();
    void on_buttonNext_clicked();
    void next();
    void previous();
    void showNextThumbnails();
    void showPreviousThumbnails();
    void imageClicked(QObject *obj);
};

#endif // WIDGET_H
