#include "startwindow.h"
#include "ui_startwindow.h"

#include <QPixmap>

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    ui->pageLoginVerticalLayout->setAlignment(Qt::AlignCenter);

    // ui->labelLoginLogo->setStyleSheet("border: 2px solid red;");
    ui->labelLoginLogo->setScaledContents(true);
    QPixmap logoImg(":/icon/resources/img/icon/placeholder-img-user.png");
    ui->labelLoginLogo->setPixmap(logoImg.scaled(200, 200, Qt::KeepAspectRatio));

    connect(ui->pageLoginBtnLogin, SIGNAL(clicked()), this, SLOT(onLoginRequested()));
    connect(ui->pageLoginBtnSignUp, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));
}

StartWindow::~StartWindow()
{
    delete ui;
}

// slots
void StartWindow::onLoginPageRequested(){
    // 로그인 페이지로 이동
}

void StartWindow::onSignUpPageRequested(){
    // 회원가입 페이지로 이동
    ui->pageStack->setCurrentWidget(ui->pageSignUp);
}

void StartWindow::onLoginRequested(){
    // 로그인 확인 후 메인윈도우로 이동

    // TODO : 로그인 확인 로직 추가

    accept();
}