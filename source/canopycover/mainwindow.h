#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include <QLabel>
#include "imageviewer.h"
#include "frmreport.h"
#include "frmCond.h"

#include "clsmngpictures.h"

#include <opencv2/imgproc/imgproc.hpp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent (QResizeEvent* event)
    {
        m_pPalette->setBrush(QPalette::Background,QBrush(m_pPixmap->scaled(width(),height())));
        setPalette(*m_pPalette);
    };
private slots:

    void on_actionShow_report_triggered();

    void on_actionOpen_image_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_image_folder_triggered();

    void on_actionClose_all_triggered();

    void on_actionOpen_image_in_new_window_triggered();



    void on_actionEstimate_canopy_cover_triggered();



private:
    Ui::MainWindow *ui;
    void setBackground();
    frmReport *frmRep;
    ImageViewer *iv;
    ImageViewer *iv_other;
    std::shared_ptr<ClsMngPictures> mp;
    frmCond* frmC;
    QString dirWork;

    QPixmap* m_pPixmap;
    QPalette* m_pPalette;
};

#endif // MAINWINDOW_H
