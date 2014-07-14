#ifndef DIALOGINTRO_H
#define DIALOGINTRO_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDialog>

namespace Ui {
class DialogIntro;
}

class DialogIntro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogIntro(QWidget *parent=0);
    ~DialogIntro();

private slots:

private:
    Ui::DialogIntro *ui;
};

#endif // DIALOGINTRO_H
