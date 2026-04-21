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
};

#endif // SCHEDULEITEM_H
