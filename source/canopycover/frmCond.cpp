#include <QDesktopServices>
#include "frmCond.h"
#include "ui_frmCond.h"
#include    <QFileDialog>
frmCond::frmCond(QWidget *parent,std::shared_ptr<ClsMngPictures> cmp) : QMainWindow(parent),ui(new Ui::frmCond)
{
    ui->setupUi(this);
    this->move(5,100);
    ui->leRlp->setValidator( new QIntValidator(0, 10000, this) );
    ui->leRlc->setValidator( new QIntValidator(0, 100, this) );
    ui->lePd->setValidator(new QDoubleValidator(0, 100,2, this));
    ui->leRd->setValidator(new QDoubleValidator(0, 100,2, this) );
    ui->lePxp->setValidator( new QIntValidator(0, 100, this) );
    mp = cmp;
    //cc = new pseCanopyCover();
    putValuesOnForm(mp);
//    cc->clone(mp->);
//    putValuesOnForm();
}
frmCond::~frmCond()
{
    delete ui;
//    delete cc;
}
void frmCond::putValuesOnForm(std::shared_ptr<ClsMngPictures> cmp)
{
  ui->dsbThre->setValue((double)cmp->getThreshold());
  ui->leRlp->setText(QString::number(cmp->getRulerLengthPx()));
  ui->leRlc->setText(QString::number(cmp->getRulerLengthCm()));
  ui->lePd->setText(QString::number(cmp->getPlantDistance()));
  ui->leRd->setText(QString::number(cmp->getRowDistance()));
  ui->lePxp->setText(QString::number(cmp->getNumPlantxPicture()));
  ui->leOutDir->setText(QString::fromStdString(cmp->getOutputDir()));
}


void frmCond::on_leRlp_textChanged(const QString &arg1)
{
    mp->setRulerLengthPx(arg1.toInt());
}

void frmCond::on_leRlc_textChanged(const QString &arg1)
{
    mp->setRulerLengthCm(arg1.toInt());
}

void frmCond::on_lePd_textChanged(const QString &arg1)
{
    mp->setPlantDistance(arg1.toFloat());
}

void frmCond::on_leRd_textChanged(const QString &arg1)
{
    mp->setRowDistance(arg1.toFloat());
}

void frmCond::on_lePxp_textChanged(const QString &arg1)
{
    mp->setNumPlantxPicture(arg1.toInt());
}

void frmCond::on_dsbThre_valueChanged(double arg1)
{
    mp->setThreshold((float)arg1);
}

void frmCond::on_but_outputDir_clicked()
{
    QString path=ui->leOutDir->text();
    QString openPath="";
    if(path=="") openPath=QDir::currentPath();
    else openPath=path;
    QString direc ="";
    direc = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 openPath,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(direc!="")
    {
        ui->leOutDir->setText(direc);
        mp->setOutputDir(direc.toUtf8().constData());
    }
}

void frmCond::on_but_openDir_clicked()
{
    QDesktopServices::openUrl(QUrl(QString::fromStdString(mp->getOutputDir())));
}
