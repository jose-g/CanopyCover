#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirWork=QApplication::applicationDirPath();
    QDir::setCurrent(QDir::homePath());
//    setBackground();
    mp = std::make_shared<ClsMngPictures>();

    iv=new ImageViewer(this,mp);
    iv->setWindowFlags(iv->windowFlags() & ~(Qt::WindowMinimizeButtonHint) & ~(Qt::WindowMaximizeButtonHint));
    iv->hide();
    frmRep = new frmReport(this,mp,iv);
    frmRep->hide();

    frmC = new frmCond(this,mp);
    frmC->setWindowFlags(frmC->windowFlags() & ~(Qt::WindowMinimizeButtonHint) & ~(Qt::WindowMaximizeButtonHint));
    frmC->show();

// set background
    m_pPalette	= new QPalette();
    m_pPixmap	= new QPixmap(":/icons_rec/images/bgfoliar.jpg");

    m_pPalette->setBrush(QPalette::Background,QBrush(*m_pPixmap));
    setPalette(*m_pPalette);

    showMaximized();

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setBackground()
{
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// existe un conflicto entre las librerias del OpenCV y QImage, el codigo de abajo es un artificio
// para cargar una imagen en un QImage


//    QFile file(":/icons_rec/images/bgfoliar.jpg");

//    QByteArray  rawImageFileInRAM;
//    if (file.open(QIODevice::ReadOnly))
//    {
//        rawImageFileInRAM = file.readAll();
//        file.close();
//    }
//    std::vector<uchar> buffInRAM(rawImageFileInRAM.data(),rawImageFileInRAM.data()+rawImageFileInRAM.size());
//    cv::Mat imgMatFromRAM = cv::imdecode(cv::Mat(buffInRAM),CV_LOAD_IMAGE_COLOR);

//    cv::Mat cvRGBLogoImage(imgMatFromRAM.rows,imgMatFromRAM.cols,CV_8UC3);
//    cv::cvtColor(imgMatFromRAM,cvRGBLogoImage,CV_BGR2RGB); //Convert BGR->RGB
//    QImage myImage((const unsigned char*)cvRGBLogoImage.data,cvRGBLogoImage.cols,cvRGBLogoImage.rows,cvRGBLogoImage.step,QImage::Format_RGB888);
//// ------------------------------------------------------------------------------------------------------------------------------------------------------
// ui->label->setPixmap(QPixmap::fromImage(myImage));

//    QPalette palette;
//    palette.setBrush(this->backgroundRole(),QBrush(QImage(":/icons_rec/images/bgfoliar.jpg")));
//   QPixmap* m_pPixmap	= new QPixmap(":/icons_rec/images/bgfoliar.jpg");
//    palette.setBrush(this->backgroundRole(),QBrush(m_pPixmap->scaled(width(),height())));
//   palette.setBrush(this->backgroundRole(),QBrush(m_pPixmap->scaled(width(),height())));


//    this->setPalette(palette);

}
void MainWindow::on_actionShow_report_triggered()
{
    frmRep->show();
}
void MainWindow::on_actionOpen_image_triggered()
{
    QStringList ls = QFileDialog::getOpenFileNames(this,tr("Open Files"), QDir::currentPath());
    if(ls.length()>0)
    {
        for(int i=0;i<ls.length();i++)
        {
          mp->addPicture(ls.at(i).toUtf8().constData());
        }
        frmRep->poblateGrid();
        if(!frmRep->isVisible()) frmRep->show();
        QFileInfo fi=ls.at(0);
        QDir::setCurrent(fi.path());
    }
}

void MainWindow::on_actionOpen_image_folder_triggered()
{
    QString direc = "";
    direc = QFileDialog::getExistingDirectory(this, tr("Open files from directory"),
                                                 QDir::currentPath(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    if(direc!="")
    {
        QDir dir(direc);
    //    const QStringList ls = dir.entryList(QDir::Files);
        const QStringList ls = dir.entryList(QDir::Files);

        if(ls.length()>0)
        {
            for(int i=0;i<ls.length();i++)
            {
              //mp->addPicture(QDir::currentPath().toUtf8().constData()+"//"+ls.at(i).toUtf8().constData());
              mp->addPicture((direc+"/"+ls.at(i)).toUtf8().constData());
            }
            frmRep->poblateGrid();
            if(!frmRep->isVisible()) frmRep->show();
            QFileInfo fi=ls.at(0);
            QDir::setCurrent(fi.path());
        }
        QDir::setCurrent(direc);
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}



void MainWindow::on_actionClose_all_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm !!!", "Are you sure that you want to clear all information?",
                                    QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        int numreg=mp->size();
        mp->clear();
        if(numreg>0)
        {
          frmRep->poblateGrid();
          if(iv->isVisible()) iv->hide();
        }
        frmC->putValuesOnForm(mp);
    }
}

void MainWindow::on_actionOpen_image_in_new_window_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath());
    if (!fileName.isEmpty())
    {
      mp->addPicture(fileName.toUtf8().constData());
      iv_other = new ImageViewer(this);
      iv_other->setWindowFlags(iv->windowFlags() & ~(Qt::WindowMinimizeButtonHint) & ~(Qt::WindowMaximizeButtonHint));
      iv_other->openImage(fileName);
      iv_other->show();
      frmRep->poblateGrid();
      if(!frmRep->isVisible()) frmRep->show();
      QFileInfo fi=fileName;
      QDir::setCurrent(fi.path());
    }
}

void MainWindow::on_actionEstimate_canopy_cover_triggered()
{
    mp->readPicture();
    mp->segment(mp->getThreshold());
    mp->saveOutputImage(mp->getOutputDir(),"out");
    int numPx;
    float area=0.0,cc=0.0;
    for(int i=0;i<mp->size();i++)
    {
        numPx=mp->getNumPx(i);
        mp->setNumPx(numPx);
        area=mp->calculateArea();
        cc=mp->calculateCc();
        mp->setArea(i,area);
        mp->setCc(i,cc);
    }
    frmRep->poblateGrid(1);
// message
    QMessageBox msgBox;
    msgBox.setWindowTitle("Finished !!!");
    msgBox.setText("Segmentation process finished, check output directory.");
    msgBox.exec();
}

