#ifndef SIDEBARCONTENTMANAGER_H
#define SIDEBARCONTENTMANAGER_H

#include <QObject>
#include <QScrollArea>
#include <QDate>

class SidebarContentManager : public QObject {
    Q_OBJECT
public:
    explicit SidebarContentManager(QScrollArea *scrollArea, QObject *parent = nullptr);

    // 특정 날짜의 일정을 불러와 스크롤 영역에 채우는 함수
    void loadSchedulesForDate(const QDate &date);

private:
    QScrollArea *m_scrollArea;
    void clearLayout(QLayout *layout); // 내부 레이아웃 초기화용 도우미 함수
};

#endif // SIDEBARCONTENTMANAGER_H