#ifndef FRMREPORT_H
#define FRMREPORT_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "imageviewer.h"
#include "clsmngpictures.h"

namespace Ui {
class frmReport;
}
class frmReport : public QMainWindow
{
    Q_OBJECT
public:
    explicit frmReport(QWidget *parent = 0,std::shared_ptr<ClsMngPictures> cmp=0,ImageViewer* imgviewer=0);
    ~frmReport();
    void poblateGrid(int icol=0);
private slots:
    void on_butClose_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_butDelete_clicked();


private:
    Ui::frmReport *ui;
    QStandardItemModel *model;
    std::shared_ptr<ClsMngPictures> mp; // manage pictures
    ImageViewer* iv;
};

#endif // FRMREPORT_H
