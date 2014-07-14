#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QMessageBox>
#include "frmreport.h"
#include "ui_frmreport.h"
const int numCol = 7; // number of columns of QTableWidget
frmReport::frmReport(QWidget *parent,std::shared_ptr<ClsMngPictures> cmp,ImageViewer *imgviewer) : QMainWindow(parent), ui(new Ui::frmReport)
{
    ui->setupUi(this);
    mp = cmp;
    iv=imgviewer;
// configurar ventana
    this->setFixedSize(this->width(),this->height()-26);

    QDesktopWidget* desktop = QApplication::desktop();

    int width = desktop->width();
    int height = desktop->height();
    int widthWindow=this->width();

    this->move(width-widthWindow-30,100); // locate window on screen

    ui->tableWidget->setColumnCount(7);

      ui->tableWidget->setColumnWidth (0, 200);
      ui->tableWidget->setColumnWidth (1, 150);
      ui->tableWidget->setColumnWidth (2, 120);
      ui->tableWidget->setColumnWidth (3, 125);
      ui->tableWidget->setColumnWidth (4, 127);
      ui->tableWidget->setColumnWidth (5, 115);
      ui->tableWidget->setColumnWidth (6, 100);

      /*
      QTableWidgetItem *itemOne = new QTableWidgetItem("one");
      ui->tableWidget->setItem(0,0,itemOne);
      ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
      ui->tableWidget->verticalHeader()->resizeSection(0, 200);
     */

      //      ui->tableWidget->horizontalHeader()->resizeSection(1, 100);
      //ui->tableWidget->horizontalHeader()->resizeSection(2, 100);
      //ui->tableWidget->verticalHeader()->resizeSection(0, 200);

      //QString data=QString::number(borrar);
      //ui->label->setText(data);

      ui->tableWidget->verticalHeader()->setVisible(true);
      ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // no permite editar las celdas
      ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // permite seleccionar toda la file
      ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); // pemite seleccion de filas uno por uno
      ui->tableWidget->setShowGrid(true);

      ui->tableWidget->setAlternatingRowColors(true);

      ui->tableWidget->setStyleSheet("QTableView {selection-background-color: rgb(57, 98, 66);}"); // define el color de la celda seleccionada
      ui->tableWidget->setStyleSheet("alternate-background-color: gray;background-color: darkGray;");

      QString styleSheet = "::section {" // "QHeaderView::section {"
                           "spacing: 10px;"
                           "background-color: rgb(46, 79, 53);"
                           "color: white;"
                           "border: 1px solid rgb(46, 79, 53);"
                           "margin: 1px;"
                           "text-align: center;"
                           "font-family: arial;"
                           "font-size: 10px; }";

      ui->tableWidget->horizontalHeader()->setStyleSheet(styleSheet); // tableWidget->verticalHeader()->setStyleSheet(styleSheet);
      ui->tableWidget->verticalHeader()->setStyleSheet(styleSheet);
      //insert data
      ui->tableWidget->show();

      poblateGrid();


//    ui->tableWidget->setWindowModality(Qt::ApplicationModal);		//tableWidget->setSizePolicy(Expanding, Expanding, 0,0);
    //ui->tableWidget->setSortingEnabled(true);
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}
frmReport::~frmReport()
{
    delete ui;
}
void frmReport::on_butDelete_clicked()
{
    int index=ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(index);
    mp->erase(index);

//    QStringList entities;
//    for(int i=0;i<mp->size();i++)
//    {
//      entities.push_back(QString::fromStdString(mp->getFilename(i)));
//    }
//    QStringListModel *model = new QStringListModel(this);
//    model->setStringList(entities);
//    ui->listView->setModel(model);
}
void frmReport::on_butClose_clicked()
{
    close();
}
void frmReport::on_tableWidget_clicked(const QModelIndex &index)
{
    int ind=index.row();
    int numreg=mp->size();
    if(numreg>=ind+1)
    {
      QString fn=QString::fromStdString(mp->getFilename(ind));
      if(!fn.isEmpty())
      {
          QFile fcheck(fn);
          if(!fcheck.exists())
          {
              QFont myFont;
              QBrush color(Qt::red);
              for(int i=0;i<numCol;i++)
              {
                  myFont=ui->tableWidget->item(ind,i)->font();
                  myFont.setStrikeOut(true);
                  ui->tableWidget->item(ind,i)->setFont(myFont);
                  ui->tableWidget->item(ind,i)->setForeground(color);
              }
              QMessageBox msgBox;
              msgBox.setWindowTitle("Warning !!!");
              QString msg="File " + fn + " does not exists !!!";
              msgBox.setText(msg);
              msgBox.exec();
          }
          else
          { // if file exists show it
            iv->openImage(fn);
            if(!iv->isVisible()) iv->show();
          }
      }
    }
}
void frmReport::poblateGrid(int icol)
{
    ui->tableWidget->clear();
    QStringList m_TableHeader;
    m_TableHeader<<"Directory"<<"Filename"<<"Image width (Pixels)"<<"Image height (Pixels)"<<"Canopy cover (Pixels)"<<"Canopy cover (%)"<<"Area cm2";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    int numreg=mp->size();
    if(numreg==0)
    {
        ui->tableWidget->setRowCount(9);
    }
    else
    {
        ui->tableWidget->setRowCount(mp->size());
    }
// poblamos la grilla

    for(int i=0;i<numreg;i++)
    {
      std::string dato=mp->getFilename(i);
      QString filename=QString::fromStdString(dato);
      QFileInfo fi=filename;
      ui->tableWidget->setItem(i,0, new QTableWidgetItem(fi.path()));
      ui->tableWidget->setItem(i,1, new QTableWidgetItem(fi.fileName()));
      if(icol==1)
      {
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(QString::number(mp->getHeight(i))));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(QString::number(mp->getWidth(i))));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(QString::number(mp->getNumPx(i))));
        ui->tableWidget->setItem(i,5, new QTableWidgetItem(QString::number(mp->getCc(i))));
        ui->tableWidget->setItem(i,6, new QTableWidgetItem(QString::number(mp->getArea(i))));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,4)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,5)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,6)->setTextAlignment(Qt::AlignCenter);
      }
    }
}








