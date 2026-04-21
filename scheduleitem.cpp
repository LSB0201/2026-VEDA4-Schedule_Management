#include "scheduleitem.h"
#include "ui_scheduleitem.h"

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

void ScheduleItem::setItemColor(const QColor &color)
{
    // 색상을 HEX 코드 문자열로 변환
    QString hexColor = color.name();

    // 왼쪽 포인트 바(colorBar) 색상 동적 적용
    ui->colorBar->setStyleSheet(QString(
                                    "background-color: %1;"
                                    "border-radius: 2px;"
                                    ).arg(hexColor));

    // 시간 텍스트(timeLabel) 색상 동적 적용
    ui->timeLabel->setStyleSheet(QString(
                                     "color: %1;"
                                     "font-weight: bold;"
                                     "font-size: 11px;"
                                     ).arg(hexColor));
}