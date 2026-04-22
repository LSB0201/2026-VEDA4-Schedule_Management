#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>
#include "schedulesave.h"

namespace Ui {
class ScheduleItem;
}

class ScheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleItem(QWidget *parent = nullptr);
    ~ScheduleItem();

    void setScheduleData(const ScheduleData &data);

    void setSelectedStyle(bool selected); // 선택 시 배경색 변경용
    ScheduleData getScheduleData() const { return m_data; } // 데이터 반환용

private:
    Ui::ScheduleItem *ui;
    ScheduleData m_data; //자기 데이터를 가지고 있도록 설정

signals:
    void itemClicked(ScheduleItem *item); // 자기 자신을 보냄
    void itemDoubleClicked(const ScheduleData &data); // 더블 클릭 시그널

protected:
    void mousePressEvent(QMouseEvent *event) override; // 마우스 이벤트 오버라이드
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // SCHEDULEITEM_H
