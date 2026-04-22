#ifndef SIDEBARCONTENTMANAGER_H
#define SIDEBARCONTENTMANAGER_H

#include <QObject>
#include <QScrollArea>
#include <QVBoxLayout>
#include "schedulesave.h"

// 전방 선언(Forward Declaration)
class ScheduleItem;

class SidebarContentManager : public QObject {
    Q_OBJECT
public:
    explicit SidebarContentManager(QScrollArea *scrollArea, QObject *parent = nullptr);

    // 특정 날짜의 일정을 불러와 스크롤 영역에 채우는 함수
    void loadSchedules(const QList<ScheduleData> &schedules);

    // 현재 선택된 아이템을 반환하는 함수
    ScheduleItem* getSelectedItem() const { return m_selectedItem; }

public slots:
    // 아이템 클릭을 처리하는 슬롯
    void handleItemClicked(ScheduleItem *item);

signals:
    void scheduleItemClicked();
    void scheduleItemDoubleClicked(const ScheduleData &data);

private:
    QScrollArea *m_scrollArea;
    ScheduleItem *m_selectedItem = nullptr; // 현재 선택된 아이템 추적
    void clearLayout(QLayout *layout); // 내부 레이아웃 초기화용 도우미 함수
};

#endif // SIDEBARCONTENTMANAGER_H