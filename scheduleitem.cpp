#include "scheduleitem.h"
#include "ui_scheduleitem.h"
#include <QMouseEvent>

ScheduleItem::ScheduleItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleItem)
{
    ui->setupUi(this);
}

ScheduleItem::~ScheduleItem()
{
    delete ui;
}


void ScheduleItem::setScheduleData(const ScheduleData &data) {
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

// 클릭 이벤트 감지
void ScheduleItem::mousePressEvent(QMouseEvent *event) {
    emit itemClicked(); // 클릭 시 시그널 발생
    QWidget::mousePressEvent(event);
}