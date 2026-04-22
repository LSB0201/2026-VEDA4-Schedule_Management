#include "sidebarcontentmanager.h"
#include "scheduleitem.h" // 커스텀 일정 위젯
#include <QVBoxLayout>
#include <QSpacerItem>

SidebarContentManager::SidebarContentManager(QScrollArea *scrollArea, QObject *parent)
    : QObject(parent), m_scrollArea(scrollArea)
{
}

void SidebarContentManager::loadSchedules(const QList<ScheduleData> &schedules) {
    QWidget *contents = m_scrollArea->widget();
    if (!contents) return;

    // 1. 기존 레이아웃 가져오기 또는 생성
    QLayout *layout = contents->layout();
    if (!layout) {
        layout = new QVBoxLayout(contents);
        contents->setLayout(layout);
    } else {
        // 2. 기존 위젯들 삭제
        clearLayout(layout);
    }

    // 3. 실제 데이터(JSON에서 불러온 데이터) 삽입
    for (const ScheduleData &data : schedules) {
        ScheduleItem *item = new ScheduleItem(contents);

        // ScheduleItem에 실제 데이터 세팅 (시간, 제목, 내용, 색상 반영)
        item->setScheduleData(data);

        // 아이템이 클릭되면 매니저의 시그널도 같이 발생하도록 연결
        connect(item, &ScheduleItem::itemClicked, this, &SidebarContentManager::scheduleItemClicked);

        layout->addWidget(item);
    }

    // 4. 위젯들을 위쪽으로 정렬하기 위한 빈 공간(스페이서) 추가
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

// 메모리 릭 방지를 위한 레이아웃 초기화 함수
void SidebarContentManager::clearLayout(QLayout *layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }
}