#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sideBar->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 이벤트 필터 구현
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->sideBar) {
        if (event->type() == QEvent::Enter) {
            // 애니메이션으로 width를 200으로 확장
            QPropertyAnimation *anim = new QPropertyAnimation(ui->sideBar, "minimumWidth");
            anim->setDuration(100);
            anim->setEndValue(200);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        } else if (event->type() == QEvent::Leave) {
            // 다시 80으로 축소
            QPropertyAnimation *anim = new QPropertyAnimation(ui->sideBar, "minimumWidth");
            anim->setDuration(100);
            anim->setEndValue(80);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    return QMainWindow::eventFilter(obj, event);
}