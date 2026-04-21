#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QWidget>

namespace Ui {
class ScheduleItem;
}

class ScheduleItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleItem(QWidget *parent = nullptr);
    ~ScheduleItem();

private:
    Ui::ScheduleItem *ui;

    void setItemColor(const QColor &color); // 사용자가 선택한 색상 반영

signals:
    void itemClicked(); // 클릭 시그널 선언

protected:
    void mousePressEvent(QMouseEvent *event) override; // 마우스 이벤트 오버라이드
};

#endif // SCHEDULEITEM_H
