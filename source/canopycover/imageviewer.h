#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "clsmngpictures.h"
#include <QMainWindow>
#include <QPrinter>
#include <QLabel>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = 0,std::shared_ptr<ClsMngPictures> cmp=0);
    ~ImageViewer();
    void openImage(QString);
    void showImageFromOpenCV(QImage);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void open();
    void print();
    void flip();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

private:
    Ui::ImageViewer *ui;
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    cv::Mat myImage;

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    std::shared_ptr<ClsMngPictures> mp;
#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *flipAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QMenu *fileMenu;
    QMenu *imageMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QLabel *labelStatusBar;
};

#endif // IMAGEVIEWER_H
