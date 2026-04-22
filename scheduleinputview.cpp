#include "scheduleinputview.h"
#include "ui_ScheduleInputView.h"
#include <QMessageBox>

ScheduleInputView::ScheduleInputView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleInputView)
{
    ui->setupUi(this);

    // Cancel 버튼 -> 창 닫기
    connect(ui->cancelButton, &QPushButton::clicked, this, &ScheduleInputView::close);

    // Save 버튼 -> 데이터 수집 슬롯 연결
    connect(ui->saveButton, &QPushButton::clicked, this, &ScheduleInputView::onSaveClicked);

    // 색상 버튼 그룹화 (한 번에 하나만 선택되도록)
    m_colorGroup = new QButtonGroup(this);
    m_colorGroup->setExclusive(true);

    m_colorGroup->addButton(ui->redColorButton);
    m_colorGroup->addButton(ui->orangeColorButton);
    m_colorGroup->addButton(ui->yellowColorButton);
    m_colorGroup->addButton(ui->greenColorButton);
    m_colorGroup->addButton(ui->blueColorButton);

    // 버튼들을 Checkable(토글 가능) 상태로 변경
    ui->redColorButton->setCheckable(true);
    ui->orangeColorButton->setCheckable(true);
    ui->yellowColorButton->setCheckable(true);
    ui->greenColorButton->setCheckable(true);
    ui->blueColorButton->setCheckable(true);

    // 스타일시트 템플릿 정의 (%1 자리에 나중에 색상이 들어갑니다)
        QString styleTemplate = "QPushButton { background-color: %1; border: 2px solid transparent; border-radius: 5px; } "
          "QPushButton:checked { border: 2px solid black; }";

    // 각 버튼에 템플릿을 사용하여 스타일 적용 (arg 함수가 %1 자리에 색상 코드를 쏙 넣어줍니다)
    ui->redColorButton->setStyleSheet(styleTemplate.arg("#F44336"));
    ui->orangeColorButton->setStyleSheet(styleTemplate.arg("#FF9800"));
    ui->yellowColorButton->setStyleSheet(styleTemplate.arg("#FFEB3B"));
    ui->greenColorButton->setStyleSheet(styleTemplate.arg("#4CAF50"));
    ui->blueColorButton->setStyleSheet(styleTemplate.arg("#2196F3"));;

    // 기본 선택값 설정
    ui->orangeColorButton->setChecked(true);
    m_selectedColor = QColor("#FF9800");

    // 버튼이 클릭되었을 때 색상 값을 변수(m_selectedColor)에 저장하도록 시그널 연결
    connect(m_colorGroup, &QButtonGroup::buttonClicked, this, &ScheduleInputView::onColorButtonClicked);
}

ScheduleInputView::~ScheduleInputView()
{
    delete ui;
}

void ScheduleInputView::showNextTo(QWidget *targetWidget) {
    // 자신의 창 속성 설정
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);

    // 사이드바의 위치를 바탕으로 내 위치 계산
    QPoint targetGlobalPos = targetWidget->mapToGlobal(QPoint(0, 0));
    int targetX = targetGlobalPos.x() - this->width();
    int targetY = targetGlobalPos.y();

    // 이동 및 출력
    this->move(targetX, targetY);
    this->show();
}

void ScheduleInputView::onColorButtonClicked(QAbstractButton *button) {
    if (button == ui->redColorButton) {
        m_selectedColor = QColor("#F44336");
    } else if (button == ui->orangeColorButton) {
        m_selectedColor = QColor("#FF9800");
    } else if (button == ui->yellowColorButton) {
        m_selectedColor = QColor("#FFEB3B");
    } else if (button == ui->greenColorButton) {
        m_selectedColor = QColor("#4CAF50");
    } else if (button == ui->blueColorButton) {
        m_selectedColor = QColor("#2196F3");
    }
}

void ScheduleInputView::setDefaultDate(const QDate &date) {
    ui->dateEdit->setDate(date);
    ui->dateEdit_2->setDate(date);
    ui->timeEdit->setTime(QTime::currentTime());
    ui->timeEdit_2->setTime(QTime::currentTime().addSecs(3600)); // 종료는 1시간 뒤로 세팅
}

void ScheduleInputView::setEditData(const ScheduleData &data) {
    m_isEditMode = true;
    m_originalData = data;
    m_selectedColor = data.color;

    ui->lineEdit->setText(data.title);
    ui->dateEdit->setDate(data.startDate);
    ui->timeEdit->setTime(data.startTime);
    ui->dateEdit_2->setDate(data.endDate);
    ui->timeEdit_2->setTime(data.endTime);
    ui->textEdit->setPlainText(data.memo);

    // 색상 버튼 선택 상태 반영
    QString hex = data.color.name(QColor::HexRgb).toUpper();
    if (hex == "#F44336") ui->redColorButton->setChecked(true);
    else if (hex == "#FFEB3B") ui->yellowColorButton->setChecked(true);
    else if (hex == "#4CAF50") ui->greenColorButton->setChecked(true);
    else if (hex == "#2196F3") ui->blueColorButton->setChecked(true);
    else ui->orangeColorButton->setChecked(true); // 기본값
}

void ScheduleInputView::onSaveClicked() {
    if (ui->lineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "입력 오류", "일정 제목을 입력해주세요.");
        return;
    }

    ScheduleData newData;
    newData.title = ui->lineEdit->text();
    newData.color = m_selectedColor;
    newData.startDate = ui->dateEdit->date();
    newData.startTime = ui->timeEdit->time();
    newData.endDate = ui->dateEdit_2->date();
    newData.endTime = ui->timeEdit_2->time();
    newData.memo = ui->textEdit->toPlainText();

    if (m_isEditMode) {
        emit editRequested(m_originalData, newData); // 수정 모드일 때
    } else {
        emit saveRequested(newData); // 새 일정일 때
    }
    this->close();
}