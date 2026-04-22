#include <QLayout>
#include <QLayoutItem>
#include <QVBoxLayout> // 레이아웃 생성을 위해 추가
#include <QPainter>
#include <QLabel>
#include "daycellwidget.h"

DayCellWidget::DayCellWidget(const QDate &date, bool isToday, QWidget *parent)
    : QWidget(parent), m_date(date), m_isToday(isToday), m_isSelected(false)
{
    // 레이아웃 생성 및 설정
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 그려진 날짜 숫자(위쪽)와 겹치지 않도록 위쪽 여백(Top Margin)을 크게 줌
    // (좌, 상, 우, 하 여백)
    layout->setContentsMargins(5, 25, 5, 5);
    layout->setSpacing(2); // 태그들 사이의 간격
    layout->setAlignment(Qt::AlignTop); // 위젯들이 위에서부터 차곡차곡 쌓이도록 설정

    this->setLayout(layout);
}

void DayCellWidget::setSelected(bool selected) {
    m_isSelected = selected;
    update(); // 상태가 바뀌면 다시 그리기(paintEvent) 호출
}

QDate DayCellWidget::getDate() const {
    return m_date;
}

void DayCellWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 여백을 약간 준 사각형 영역 설정
    QRect r = rect().adjusted(2, 2, -2, -2);

    // 배경 초기화 (잔상 방지)
    painter.fillRect(rect(), Qt::white);

    // 선택된 날짜 (주황색 둥근 배경)
    if (m_isSelected) {
        painter.setBrush(QColor("#FF7E33")); // 주황색
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(r, 10, 10);
        painter.setPen(Qt::white); // 글자색 흰색
    }
    // 오늘 날짜 (주황색 테두리)
    else if (m_isToday) {
        painter.setPen(QPen(QColor("#FF7E33"), 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(r, 10, 10);
        painter.setPen(Qt::black); // 글자색 검정
    }
    // 일반 날짜
    else {
        painter.setPen(Qt::black); // 글자색 검정
    }

    // 날짜 숫자 그리기 (좌상단 정렬, 약간의 여백)
    painter.drawText(rect().adjusted(10, 10, 0, 0), Qt::AlignTop | Qt::AlignLeft, QString::number(m_date.day()));
}

void DayCellWidget::clearSchedules() {
    QLayout *layout = this->layout();
    if (!layout) return;

    QLayoutItem *child;
    // 날짜 숫자는 레이아웃이 아니라 paintEvent로 표현한 상태
    // 현재 레이아웃 안에는 '일정 태그'들만 존재. 따라서, index 0부터 전부 삭제
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }
}

void DayCellWidget::addScheduleTag(const ScheduleData &data) {
    QLayout *layout = this->layout();
    if (!layout) return;

    QLabel *tag = new QLabel(data.title, this);

    // 두 번째 사진처럼 텍스트와 배경색 지정)
    QColor bgColor = data.color;
    bgColor.setAlpha(50); // 투명도 50

    QString style = QString("QLabel { "
                            "background-color: %1; "
                            "color: %2; "
                            "border-radius: 4px; "
                            "padding: 2px; "
                            "font-size: 10px; "
                            "font-weight: bold; }")
                        .arg(bgColor.name(QColor::HexArgb)) // 연한 배경
                        .arg(data.color.name());            // 진한 글씨

    tag->setStyleSheet(style);

    // 태그가 셀 너비에 맞게 설정
    tag->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(tag);
}