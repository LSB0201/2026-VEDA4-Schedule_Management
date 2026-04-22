#include "startwindow.h"
#include "ui_startwindow.h"

#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

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
    connect(authManager, &AuthManager::loginFinished, this, &StartWindow::onLoginFinished);
    connect(ui->pageLoginBtnSignUp, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    connect(ui->pageSignUpBtnNext, SIGNAL(clicked()), this, SLOT(onSignUpNextBtnClicked()));
    connect(authManager, &AuthManager::idCheckFinished, this, &StartWindow::onIdCheckFinished);

    connect(ui->pageSignUpBtnPrev, SIGNAL(clicked()), this, SLOT(onLoginPageRequested()));
    connect(ui->pageSignUpCheckBoxPW, SIGNAL(clicked()), this, SLOT(onSignUpCheckBoxPWClicked()));
    connect(ui->pageSignUpCheckBoxPWC, SIGNAL(clicked()), this, SLOT(onSignUpCheckBoxPWCClicked()));

    connect(ui->pageProfileBtnCreate, SIGNAL(clicked()), this, SLOT(onProfileCreateBtnClicked()));
    connect(authManager, &AuthManager::registerFinished, this, &StartWindow::onRegisterFinished);
    connect(ui->pageProfileBtnPrev, SIGNAL(clicked()), this, SLOT(onSignUpPageRequested()));

    // TODO : 연결 이후 자동 로그인을 체크해두었는지 확인
}

StartWindow::~StartWindow()
{
    delete ui;
}

// private

void StartWindow::onLoginFinished(bool success, QString message, QString userName){
    if (success) {
        qDebug() << "로그인 성공: " << userName;
        accept(); // 성공 시 다이얼로그를 닫고 메인윈도우로 진입
    } else {
        QMessageBox::warning(this, "로그인 실패", message);
    }
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
    ui->pageSignUpTooltip->setText("Create your Account !");
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
    if(id.isEmpty() || pw.isEmpty()){
        QMessageBox::warning(this, "로그인 실패", "ID와 PW를 입력해주세요");
        return;
    }

    // TODO : 자동 로그인 확인 로직 추가

    authManager->login(id, pw);
}

void StartWindow::onSignUpNextBtnClicked(){
    id = ui->pageSignUpEditID->text();
    pw = ui->pageSignUpEditPW->text();
    pwc = ui->pageSignUpEditPWC->text();

    QRegularExpression idRegex("^[a-zA-Z0-9]{4,12}$");
    if (!idRegex.match(id).hasMatch()) {
        ui->pageSignUpTooltip->setText("아이디는 4~12자 영문/숫자만 가능합니다.");
        return;
    }

    if(pw.length() < 8){
        ui->pageSignUpTooltip->setText("비밀번호는 8자리 이상이어야 합니다.");
        return;
    }

    if (pw!=pwc){
        ui->pageSignUpTooltip->setText("비밀번호가 일치하지 않습니다.");
        return;
    }

    authManager->checkId(id);
}

// AuthManager로부터 ID 체크 결과를 받았을 때
void StartWindow::onIdCheckFinished(bool available, QString message) {
    if (available) {
        onProfilePageRequested();
    } else {
        // 서버에서 온 에러 메시지(중복 등) 표시
        QMessageBox::warning(this, "확인", message);
    }
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

void StartWindow::onProfileCreateBtnClicked(){
    nickname = ui->pageProfileEditNickname->text();
    if(nickname.isEmpty()) {
        QMessageBox::warning(this, "알림", "닉네임을 입력해주세요.");
        return;
    }
    authManager->registerUser(id, pw, nickname);
}

void StartWindow::onRegisterFinished(bool success, QString message) {
    if (success) {
        QMessageBox::information(this, "가입 완료", "회원가입이 완료되었습니다. 로그인해주세요.");
        onLoginPageRequested(); // 로그인 페이지로 이동
    } else {
        QMessageBox::critical(this, "가입 실패", message);
    }
}
