#include "mainwindow.h"
#include <QApplication>
#include "dialogintro.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogIntro dialog;
    if(dialog.exec() == 0)
        return -1;

    MainWindow w;
    w.show();

    return a.exec();
}
