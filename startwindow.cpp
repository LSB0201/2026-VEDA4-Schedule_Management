#include "startwindow.h"
#include "ui_startwindow.h"

#include <QPixmap>

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    onLoginPageRequested();

    ui->pageLoginVerticalLayout->setAlignment(Qt::AlignCenter);

    // ui->labelLoginLogo->setStyleSheet("border: 2px solid red;");
    ui->labelLoginLogo->setScaledContents(true);
    QPixmap logoImg(":/icon/resources/img/icon/placeholder-img-user.png");
    ui->labelLoginLogo->setPixmap(logoImg.scaled(200, 200, Qt::KeepAspectRatio));

    connect(ui->pageLoginBtnLogin, SIGNAL(clicked()), this, SLOT(onLoginRequested()));
    connect(ui->pageLoginBtnSignUp, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    connect(ui->pageSignUpBtnNext, SIGNAL(clicked()), this, SLOT(onSignUpNextBtnClicked()));
    connect(ui->pageSignUpBtnPrev, SIGNAL(clicked()), this, SLOT(onLoginPageRequested()));

    connect(ui->pageProfileBtnCreate, SIGNAL(clicked()), this, SLOT(onProfileCreateBtnClicked()));
    connect(ui->pageProfileBtnPrev, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    // TODO : 연결 이후 자동 로그인을 체크해두었는지 확인
}

StartWindow::~StartWindow()
{
    delete ui;
}

// slots
void StartWindow::onLoginPageRequested(){
    // 로그인 페이지로 이동
    ui->pageStack->setCurrentWidget(ui->pageLogin);
    ui->pageLoginEditID->clear();
    ui->pageLoginEditPW->clear();
}

void StartWindow::onSignUpPageRequested(){
    // 회원가입 페이지로 이동
    ui->pageStack->setCurrentWidget(ui->pageSignUp);
    ui->pageSignUpEditID->clear();
    ui->pageSignUpEditPW->clear();
    ui->pageSignUpEditPWC->clear();
}

void StartWindow::onLoginRequested(){
    // 로그인 확인 후 메인윈도우로 이동
    id = ui->pageLoginEditID->text();
    pw = ui->pageLoginEditPW->text();

    // TODO : 로그인 확인 로직 추가

    accept();
}

bool StartWindow::valid_chk(){
    id = ui->pageSignUpEditID->text();
    pw = ui->pageSignUpEditPW->text();
    pwc = ui->pageSignUpEditPWC->text();

    // TODO : 아이디가 이미 존재하는지 검사하는 로직
    // if (이미 존재){
    //     ui->pageSignUpTooltip->setText("이미 존재하는 아이디입니다.");
    // }

    // TODO : 존재 로직 추가 후 else if로 수정하여 일관성 있게 사용
    if (pw!=pwc){
        ui->pageSignUpTooltip->setText("비밀번호가 일치하지 않습니다.");
        return false;
    }

    else {
        return true;
    }
}

void StartWindow::onSignUpNextBtnClicked(){
    if(valid_chk())
        onProfilePageRequested();
}

void StartWindow::onProfilePageRequested(){
    ui->pageStack->setCurrentWidget(ui->pageProfile);
    ui->pageProfileEditNickname->clear();
    ui->pageProfileEdit_1->clear();
    ui->pageProfileEdit_2->clear();
}

void StartWindow::onProfileCreateBtnClicked(){
    // TODO : 서버에 새 계정 정보 추가하는 로직
    onLoginPageRequested();
}
