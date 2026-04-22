#ifndef DAYCELLWIDGET_H
#define DAYCELLWIDGET_H

#include <QWidget>
#include <QDate>
#include <QPainter>
#include "schedulesave.h"

class DayCellWidget : public QWidget {
    Q_OBJECT
public:
    explicit DayCellWidget(const QDate &date, bool isToday = false, QWidget *parent = nullptr);

    void setSelected(bool selected);
    QDate getDate() const;

    void addScheduleTag(const ScheduleData &data);
    void clearSchedules(); // 기존 태그 지우기

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QDate m_date;
    bool m_isToday;
    bool m_isSelected;
};

#endif // DAYCELLWIDGET_H