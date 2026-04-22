#include "ScheduleSearchResultItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDate>

ScheduleSearchResultItem::ScheduleSearchResultItem(const QJsonObject &data, QWidget *parent) : QWidget(parent) {
    // 카드 배경 역할을 할 컨테이너 (QSS 대신 팔레트 혹은 페인트 이벤트가 정석이나, 편의상 프레임 활용)
    this->setFixedHeight(100);
    this->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(15, 10, 15, 10);
    layout->setSpacing(20);

    // 1. Date Badge (왼쪽 사각형 영역)
    QWidget *dateBadge = new QWidget(this);
    dateBadge->setFixedSize(60, 70);
    dateBadge->setStyleSheet(QString("background-color: #fcece0; border-radius: 12px;")); // 연한 배경

    QVBoxLayout *dateLayout = new QVBoxLayout(dateBadge);
    dateLayout->setContentsMargins(0, 5, 0, 5);

    QDate sDate = QDate::fromString(data.value("startDate").toString(), "yyyy-MM-dd");
    QLabel *monthLabel = new QLabel(sDate.toString("MMM").toUpper());
    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setStyleSheet("color: #ef6c00; font-weight: bold; font-size: 11px;");

    QLabel *dayLabel = new QLabel(QString::number(sDate.day()));
    dayLabel->setAlignment(Qt::AlignCenter);
    dayLabel->setStyleSheet("color: #ef6c00; font-weight: bold; font-size: 18px;");

    dateLayout->addWidget(monthLabel);
    dateLayout->addWidget(dayLabel);
    layout->addWidget(dateBadge);

    // 2. Text Info (오른쪽 영역)
    QVBoxLayout *textLayout = new QVBoxLayout();

    QString timeStr = QString("%1 • %2")
                          .arg(data.value("startDate").toString())
                          .arg(data.value("startTime").toString());
    QLabel *timeLabel = new QLabel(timeStr);
    timeLabel->setStyleSheet("color: #888; font-size: 11px;");

    QLabel *titleLabel = new QLabel(data.value("title").toString());
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #333;");

    QLabel *memoLabel = new QLabel(data.value("memo").toString());
    memoLabel->setStyleSheet("color: #666; font-size: 12px;");
    memoLabel->setWordWrap(false);

    textLayout->addWidget(timeLabel);
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(memoLabel);

    layout->addLayout(textLayout);
    layout->addStretch();

    // 전체 카드 테두리 및 배경 (set函数 대용 스타일)
    this->setStyleSheet("QWidget#ScheduleSearchResultItem { background-color: white; border: 1px solid #eee; border-radius: 15px; } "
                        "QWidget#ScheduleSearchResultItem:hover { background-color: #fafafa; border: 1px solid #ef6c00; }");
    this->setObjectName("ScheduleSearchResultItem");
}