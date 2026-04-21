#include "mainwindow.h"
#include "startwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

static bool DEBUG = true;
static bool ON_STARTWINDOW = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // stylesheet 적용
    QFile file(":/resources/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream ts(&file);
        a.setStyleSheet(ts.readAll());
        file.close();
        if(DEBUG){
            qDebug() << "style sheet load";
        }
    }

    MainWindow w;
    if (ON_STARTWINDOW){
        StartWindow start;
        if (start.exec() == QDialog::Accepted){
            w.show();
            return a.exec();
        }
        else return 0;
    }
    else {
        w.show();
    }

    return a.exec();
}
