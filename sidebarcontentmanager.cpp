#include "sidebarcontentmanager.h"
#include "scheduleitem.h" // 커스텀 일정 위젯
#include <QVBoxLayout>
#include <QSpacerItem>

SidebarContentManager::SidebarContentManager(QScrollArea *scrollArea, QObject *parent)
    : QObject(parent), m_scrollArea(scrollArea)
{
}

void SidebarContentManager::loadSchedulesForDate(const QDate &date) {
    QWidget *contents = m_scrollArea->widget();
    if (!contents) return;

    // 1. 기존 레이아웃 가져오기 또는 생성
    QLayout *layout = contents->layout();
    if (!layout) {
        layout = new QVBoxLayout(contents);
        contents->setLayout(layout);
    } else {
        clearLayout(layout); // 기존 아이템 모두 삭제
    }

    // 2. 테스트용 데이터 삽입 (선택된 날짜 기반)
    // 추후 이 부분에 DB나 배열에서 date에 해당하는 일정을 검색하는 로직이 들어갑니다.
    for (int i = 0; i < 3; ++i) {
        ScheduleItem *item = new ScheduleItem(contents);

        // 아이템이 클릭되면 매니저의 시그널도 같이 발생하도록 연결
        connect(item, &ScheduleItem::itemClicked, this, &SidebarContentManager::scheduleItemClicked);

        // item->setData("09:00", "프로젝트 회의", "내용..."); // 데이터 입력

        layout->addWidget(item);
    }

    // 3. 위젯들이 위쪽으로 정렬을 위한 하단 여백 추가
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