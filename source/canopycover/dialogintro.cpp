#include <QFile>
#include "dialogintro.h"
#include "ui_dialogintro.h"
DialogIntro::DialogIntro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogIntro)
{
    ui->setupUi(this);

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// existe un conflicto entre las librerias del OpenCV y QImage, el codigo de abajo es un artificio
// para cargar una imagen en un QImage
    QFile file(":/icons_rec/images/introimage.jpg");

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
    QImage myImage((const unsigned char*)cvRGBLogoImage.data,cvRGBLogoImage.cols,cvRGBLogoImage.rows,cvRGBLogoImage.step,QImage::Format_RGB888);

    ui->label_3->setPixmap(QPixmap::fromImage(myImage));
// ------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// existe un conflicto entre las librerias del OpenCV y QImage, el codigo de abajo es un artificio
// para cargar una imagen en un QImage
        QFile file2(":/icons_rec/images/logo.bmp");

        QByteArray  rawImageFileInRAM2;
        if (file2.open(QIODevice::ReadOnly))
        {
            rawImageFileInRAM2 = file2.readAll();
            file2.close();
        }
        std::vector<uchar> buffInRAM2(rawImageFileInRAM2.data(),rawImageFileInRAM2.data()+rawImageFileInRAM2.size());
        cv::Mat imgMatFromRAM2 = cv::imdecode(cv::Mat(buffInRAM2),CV_LOAD_IMAGE_COLOR);

        cv::Mat cvRGBLogoImage2(imgMatFromRAM2.rows,imgMatFromRAM2.cols,CV_8UC3);
        cv::cvtColor(imgMatFromRAM2,cvRGBLogoImage2,CV_BGR2RGB); //Convert BGR->RGB
        QImage myImage2((const unsigned char*)cvRGBLogoImage2.data,cvRGBLogoImage2.cols,cvRGBLogoImage2.rows,cvRGBLogoImage2.step,QImage::Format_RGB888);

        ui->label_4->setPixmap(QPixmap::fromImage(myImage2));
// ------------------------------------------------------------------------------------------------------------------------------------------------------


/*  Este codigo genera un conflicto entre QImage y OpenCV
    QImage myImage;
    myImage.load(":/icons_rec/images/logo.bmp");
    ui->label_4->setPixmap(QPixmap::fromImage(myImage));
*/
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

DialogIntro::~DialogIntro()
{
    delete ui;
}
