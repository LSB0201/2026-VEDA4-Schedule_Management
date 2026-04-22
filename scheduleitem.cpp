#include "scheduleitem.h"
#include "ui_scheduleitem.h"
#include <QMouseEvent>

ScheduleItem::ScheduleItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}


void ScheduleItem::setScheduleData(const ScheduleData &data) {
    m_data = data;
    // 텍스트 데이터 세팅
    QString timeStr = data.startTime.toString("HH:mm") + " - " + data.endTime.toString("HH:mm");
    ui->timeLabel->setText(timeStr);
    ui->titleLabel->setText(data.title);
    ui->descLabel->setText(data.memo);

    // 색상 데이터 세팅 (기존 디자인 로직 유지)
    QString hexColor = data.color.name();

    // 왼쪽 포인트 바(colorBar) 색상 적용
    ui->colorBar->setStyleSheet(QString(
                                    "background-color: %1;"
                                    "border-radius: 2px;"
                                    ).arg(hexColor));

    // 시간 텍스트(timeLabel) 색상 적용
    ui->timeLabel->setStyleSheet(QString(
                                     "color: %1;"
                                     "font-weight: bold;"
                                     "font-size: 11px;"
                                     ).arg(hexColor));
}

// 클릭 및 더블 클릭 이벤트
void ScheduleItem::mousePressEvent(QMouseEvent *event) {
    emit itemClicked(this); // 나 자신(포인터)을 보냄
    QWidget::mousePressEvent(event);
}

void ScheduleItem::mouseDoubleClickEvent(QMouseEvent *event) {
    emit itemDoubleClicked(m_data); // 수정창을 띄우기 위해 데이터를 보냄
    QWidget::mouseDoubleClickEvent(event);
}

void ScheduleItem::setSelectedStyle(bool selected) {
    if (selected) {
        this->setStyleSheet("ScheduleItem { background-color: #E0E0E0; border-radius: 5px; }");
    } else {
        this->setStyleSheet("ScheduleItem { background-color: transparent; }");
    }
}