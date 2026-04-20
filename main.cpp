#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

static bool DEBUG = true;

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
    w.show();
    return QCoreApplication::exec();
}
