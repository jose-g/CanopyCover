#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>

#include "imageviewer.h"
#include "ui_imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent,std::shared_ptr<ClsMngPictures> cmp) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
     mp = cmp;
    labelStatusBar = new QLabel;
    ui->statusbar->addWidget(labelStatusBar);
// configuramos la posicion de la ventana
    this->move(30,100);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}
void ImageViewer::openImage(QString fileName)
{
    if (!fileName.isEmpty()) {
        // ------------------------------------------------------------------------------------------------------------------------------------------------------
        // existe un conflicto entre las librerias del OpenCV y QImage, el codigo de abajo es un artificio
        // para cargar una imagen en un QImage
            QFile file(fileName);

            QByteArray  rawImageFileInRAM;
            if (file.open(QIODevice::ReadOnly))
            {
                rawImageFileInRAM = file.readAll();
                file.close();
            }
            std::vector<uchar> buffInRAM(rawImageFileInRAM.data(),rawImageFileInRAM.data()+rawImageFileInRAM.size());
            cv::Mat imgMatFromRAM = cv::imdecode(cv::Mat(buffInRAM),CV_LOAD_IMAGE_COLOR);

            cv::Mat cvRGBLogoImage(imgMatFromRAM.rows,imgMatFromRAM.cols,CV_8UC3);
            cv::cvtColor(imgMatFromRAM,cvRGBLogoImage,CV_BGR2RGB); //Convert BGR->RGB
            QImage image((const unsigned char*)cvRGBLogoImage.data,cvRGBLogoImage.cols,cvRGBLogoImage.rows,cvRGBLogoImage.step,QImage::Format_RGB888);

        // ------------------------------------------------------------------------------------------------------------------------------------------------------

            imgMatFromRAM.copyTo(myImage);

//        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();


        labelStatusBar->setText(fileName);
        //statusBar()->showMessage(fileName);
    }
}
void ImageViewer::print()
 {
     Q_ASSERT(imageLabel->pixmap());
 #ifndef QT_NO_PRINTER
     QPrintDialog dialog(&printer, this);
     if (dialog.exec()) {
         QPainter painter(&printer);
         QRect rect = painter.viewport();
         QSize size = imageLabel->pixmap()->size();
         size.scale(rect.size(), Qt::KeepAspectRatio);
         painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
         painter.setWindow(imageLabel->pixmap()->rect());
         painter.drawPixmap(0, 0, *imageLabel->pixmap());
     }
 #endif
 }

 void ImageViewer::zoomIn()
 {
     scaleImage(1.25);
 }

 void ImageViewer::zoomOut()
 {
     scaleImage(0.8);
 }

 void ImageViewer::normalSize()
 {
     imageLabel->adjustSize();
     scaleFactor = 1.0;
 }

 void ImageViewer::fitToWindow()
 {
     bool fitToWindow = fitToWindowAct->isChecked();
     scrollArea->setWidgetResizable(fitToWindow);
     if (!fitToWindow) {
         normalSize();
     }
     updateActions();
 }
void ImageViewer::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    flipAct = new QAction(tr("&Flip"), this);
    flipAct->setShortcut(tr("Ctrl+F"));
    connect(flipAct, SIGNAL(triggered()), this, SLOT(flip()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

}
void ImageViewer::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    imageMenu = new QMenu(tr("&Image"), this);
    imageMenu->addAction(flipAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(imageMenu);
    menuBar()->addMenu(viewMenu);
}

void ImageViewer::showImageFromOpenCV(QImage image)
{
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();


        //labelStatusBar->setText(fileName);
}

void ImageViewer::open()
 {
     QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());
     openImage(fileName);
 }
void ImageViewer::flip()
 {
    cv::flip(myImage,myImage,1);
    cv::Mat imgResult;
    myImage.copyTo(imgResult);
    switch (myImage.type()) {
          case CV_8UC1:
              cv::cvtColor(imgResult,imgResult, CV_GRAY2RGB);
              break;
          case CV_8UC3:
              cv::cvtColor(imgResult,imgResult, CV_BGR2RGB);
              break;
          }
    QImage img=QImage((const unsigned char*)(imgResult.data),imgResult.cols,imgResult.rows,QImage::Format_RGB888);
    showImageFromOpenCV(img);
 }
void ImageViewer::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}
void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}
void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}
void ImageViewer::mousePressEvent(QMouseEvent */* unused */)
//void ImageViewer::mousePressEvent(QMouseEvent *event)
{
     setCursor(Qt::ClosedHandCursor);
}
void ImageViewer::mouseReleaseEvent(QMouseEvent */* unused */)
//void ImageViewer::mouseReleaseEvent(QMouseEvent *event)
{
     setCursor(Qt::OpenHandCursor);
}
