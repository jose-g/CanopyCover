#ifndef FRMCOND_H
#define FRMCOND_H
#include <QMainWindow>
#include "clsmngpictures.h"
//#include "pseCanopyCover.h"
namespace Ui {
class frmCond;
}

class frmCond : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmCond(QWidget *parent = 0,std::shared_ptr<ClsMngPictures> cmp=0);
    ~frmCond();
    void putValuesOnForm(std::shared_ptr<ClsMngPictures> cmp);
    void saveValuesOnObj(std::shared_ptr<ClsMngPictures> cmp);
    void validateValuesOnForm();
private slots:

    void on_leRlp_textChanged(const QString &arg1);

    void on_leRlc_textChanged(const QString &arg1);

    void on_lePd_textChanged(const QString &arg1);

    void on_leRd_textChanged(const QString &arg1);

    void on_lePxp_textChanged(const QString &arg1);

    void on_dsbThre_valueChanged(double arg1);

    void on_but_outputDir_clicked();

    void on_but_openDir_clicked();

private:
    Ui::frmCond *ui;
    std::shared_ptr<ClsMngPictures> mp;
//    pseCanopyCover* cc;
};
#endif // FRMCOND_H
