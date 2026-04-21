#ifndef DAYCELLWIDGET_H
#define DAYCELLWIDGET_H

#include <QWidget>
#include <QDate>
#include <QPainter>

class DayCellWidget : public QWidget {
    Q_OBJECT
public:
    explicit DayCellWidget(const QDate &date, bool isToday = false, QWidget *parent = nullptr);

    void setSelected(bool selected);
    QDate getDate() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QDate m_date;
    bool m_isToday;
    bool m_isSelected;
};

#endif // DAYCELLWIDGET_H