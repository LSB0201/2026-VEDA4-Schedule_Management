#include "ScheduleSearchResultItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ScheduleSearchResultItem::ScheduleSearchResultItem(const ScheduleData &data, QWidget *parent) : QWidget(parent) {
    this->setFixedHeight(110);
    this->setObjectName("ScheduleSearchResultItem");

    this->setStyleSheet(
        "QWidget#ScheduleSearchResultItem {"
        "   background-color: white;"
        "   border: 1px solid #e0e0e0;"
        "   border-radius: 15px;"
        "}"
        "QWidget#ScheduleSearchResultItem:hover {"
        "   border: 1px solid #ef6c00;"
        "}"
        );

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(20, 15, 20, 15);
    layout->setSpacing(20);

    // 1. Date Badge (왼쪽 사각형 영역)
    QWidget *dateBadge = new QWidget(this);
    dateBadge->setFixedSize(60, 70);
    // 구조체의 color를 배경색으로 활용 (투명도 조절)
    dateBadge->setStyleSheet(QString("background-color: %1; border-radius: 12px;").arg(data.color.name()));

    QVBoxLayout *dateLayout = new QVBoxLayout(dateBadge);
    dateLayout->setSpacing(0);
    dateLayout->setContentsMargins(0, 5, 0, 5);

    QLabel *monthLabel = new QLabel(data.startDate.toString("MMM").toUpper());
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("color: white; font-weight: bold; font-size: 11px;");

    QLabel *dayLabel = new QLabel(QString::number(data.startDate.day()));
    dayLabel->setAlignment(Qt::AlignCenter);
    dayLabel->setStyleSheet("color: white; font-weight: bold; font-size: 18px;");

    dateLayout->addWidget(monthLabel, 0, Qt::AlignCenter);
    dateLayout->addWidget(dayLabel, 0, Qt::AlignCenter);
    layout->addWidget(dateBadge);

    // 2. Text Info
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(4);

    QLabel *timeLabel = new QLabel(data.startDate.toString("yyyy. MM. dd") + "  " + data.startTime.toString("hh:mm"));
    timeLabel->setStyleSheet("color: #888; font-size: 11px;");

    QLabel *titleLabel = new QLabel(data.title);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #333;");

    QLabel *memoLabel = new QLabel(data.memo);
    memoLabel->setStyleSheet("color: #666; font-size: 12px;");

    textLayout->addWidget(timeLabel);
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(memoLabel);
    layout->addLayout(textLayout);

    layout->addStretch();

    // 호버 효과를 위한 스타일시트
    this->setStyleSheet("QWidget#ScheduleSearchResultItem { background-color: white; border: 1px solid #eee; border-radius: 15px; } "
                        "QWidget#ScheduleSearchResultItem:hover { border: 1px solid orange; }");
}