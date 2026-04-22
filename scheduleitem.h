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

private:
    Ui::ScheduleItem *ui;

signals:
    void itemClicked(); // 클릭 시그널 선언

protected:
    void mousePressEvent(QMouseEvent *event) override; // 마우스 이벤트 오버라이드
};

#endif // SCHEDULEITEM_H
