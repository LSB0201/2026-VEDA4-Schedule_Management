#include "daycellwidget.h"

DayCellWidget::DayCellWidget(const QDate &date, bool isToday, QWidget *parent)
    : QWidget(parent), m_date(date), m_isToday(isToday), m_isSelected(false)
{

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

    // 1. 선택된 날짜 (주황색 둥근 배경)
    if (m_isSelected) {
        painter.setBrush(QColor("#FF7E33")); // 주황색
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(r, 10, 10);
        painter.setPen(Qt::white); // 글자색 흰색
    }
    // 2. 오늘 날짜 (주황색 테두리)
    else if (m_isToday) {
        painter.setPen(QPen(QColor("#FF7E33"), 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(r, 10, 10);
        painter.setPen(Qt::black); // 글자색 검정
    }
    // 3. 일반 날짜
    else {
        painter.setPen(Qt::black); // 글자색 검정
    }

    // 날짜 숫자 그리기 (좌상단 정렬, 약간의 여백)
    painter.drawText(rect().adjusted(10, 10, 0, 0), Qt::AlignTop | Qt::AlignLeft, QString::number(m_date.day()));
}