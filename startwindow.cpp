#include "startwindow.h"
#include "ui_startwindow.h"

#include <QPixmap>
#include <QGraphicsDropShadowEffect>

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("Roboto");
    font.setBold(true);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30);
    shadow->setXOffset(0);
    shadow->setYOffset(10);
    shadow->setColor(QColor(0, 0, 0, 40));
    onLoginPageRequested();
    ui->pageStack->setGraphicsEffect(shadow);

    // set login page
    ui->pageLoginVerticalLayout->setAlignment(Qt::AlignCenter);

    ui->labelLoginLogo->setScaledContents(true);
    QPixmap logoImg(":/icon/resources/img/icon/placeholder-img-user.png");
    ui->labelLoginLogo->setPixmap(logoImg.scaled(200, 200, Qt::KeepAspectRatio));

    ui->pageLoginLabelID->setFont(font);
    ui->pageLoginLabelID->setFixedHeight(10);

    ui->pageLoginEditID->setFixedHeight(50);

    ui->pageLoginLabelPW->setFont(font);
    ui->pageLoginLabelPW->setFixedHeight(10);

    ui->pageLoginEditPW->setFixedHeight(50);

    ui->pageLoginBtnLogin->setFixedHeight(60);
    ui->pageLoginBtnLogin->setBackgroundColor(QColor("#F37321"));
    ui->pageLoginBtnLogin->setForegroundColor(Qt::black);
    ui->pageLoginBtnLogin->setOverlayColor(QColor("#E96917"));
    ui->pageLoginBtnLogin->setOverlayStyle(Material::TintedOverlay);
    ui->pageLoginBtnLogin->setCornerRadius(15);
    ui->pageLoginBtnLogin->setFont(font);
    ui->pageLoginBtnLogin->setFontSize(15);

    ui->pageLoginBtnSignUp->setFixedHeight(60);
    ui->pageLoginBtnSignUp->setBackgroundColor(QColor("#E0E0E0"));
    ui->pageLoginBtnSignUp->setForegroundColor(Qt::black);
    ui->pageLoginBtnSignUp->setCornerRadius(15);
    ui->pageLoginBtnSignUp->setFont(font);
    ui->pageLoginBtnSignUp->setFontSize(15);


    // set slots
    connect(ui->pageLoginBtnLogin, SIGNAL(clicked()), this, SLOT(onLoginRequested()));
    connect(ui->pageLoginBtnSignUp, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    connect(ui->pageSignUpBtnNext, SIGNAL(clicked()), this, SLOT(onSignUpNextBtnClicked()));
    connect(ui->pageSignUpBtnPrev, SIGNAL(clicked()), this, SLOT(onLoginPageRequested()));
    connect(ui->pageSignUpCheckBoxPW, SIGNAL(clicked()), this, SLOT(onSignUpCheckBoxPWClicked()));
    connect(ui->pageSignUpCheckBoxPWC, SIGNAL(clicked()), this, SLOT(onSignUpCheckBoxPWCClicked()));

    connect(ui->pageProfileBtnCreate, SIGNAL(clicked()), this, SLOT(onProfileCreateBtnClicked()));
    connect(ui->pageProfileBtnPrev, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    // TODO : 연결 이후 자동 로그인을 체크해두었는지 확인
}

StartWindow::~StartWindow()
{
    delete ui;
}

// private

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

void onLoginFinished(bool success, QString message){

}


// slots

// 로그인 페이지로 이동
void StartWindow::onLoginPageRequested(){
    ui->pageStack->setCurrentWidget(ui->pageLogin);
    ui->pageLoginEditID->clear();
    ui->pageLoginEditPW->clear();
}

// 회원가입 페이지로 이동
void StartWindow::onSignUpPageRequested(){
    ui->pageStack->setCurrentWidget(ui->pageSignUp);
    ui->pageSignUpEditID->clear();
    ui->pageSignUpEditPW->clear();
    ui->pageSignUpEditPWC->clear();
    ui->pageSignUpCheckBoxPW->setCheckState(Qt::Unchecked);
    ui->pageSignUpCheckBoxPWC->setCheckState(Qt::Unchecked);
}

// 로그인 확인 후 메인윈도우로 이동
void StartWindow::onLoginRequested(){
    id = ui->pageLoginEditID->text();
    pw = ui->pageLoginEditPW->text();

    // TODO : 로그인 확인 로직 추가

    accept();
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

void StartWindow::onSignUpCheckBoxPWClicked(){
    if (ui->pageSignUpCheckBoxPW->isChecked() == true){
        ui->pageSignUpEditPW->setEchoMode(QtMaterialTextField::Normal);
    }
    else{
        ui->pageSignUpEditPW->setEchoMode(QtMaterialTextField::Password);
    }
}

void StartWindow::onSignUpCheckBoxPWCClicked(){
    if (ui->pageSignUpCheckBoxPWC->isChecked() == true){
        ui->pageSignUpEditPWC->setEchoMode(QtMaterialTextField::Normal);
    }
    else{
        ui->pageSignUpEditPWC->setEchoMode(QtMaterialTextField::Password);
    }
}

// TODO : 서버에 새 계정 정보 추가하는 로직
void StartWindow::onProfileCreateBtnClicked(){
    onLoginPageRequested();
}

