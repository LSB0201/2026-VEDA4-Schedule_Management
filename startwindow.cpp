#include "startwindow.h"
#include "ui_startwindow.h"

#include <QPixmap>

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    QPixmap logoImg;
    logoImg.load(":/icon/resources/img/icon/placeholder-img-user.png");
    ui->labelLoginLogo->setPixmap(logoImg.scaled(266, 266, Qt::KeepAspectRatio));
}

StartWindow::~StartWindow()
{
    delete ui;
}
