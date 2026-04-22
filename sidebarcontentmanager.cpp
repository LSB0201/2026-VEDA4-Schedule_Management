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

    // 기존 레이아웃 가져오기 또는 생성
    QLayout *layout = contents->layout();
    if (!layout) {
        layout = new QVBoxLayout(contents);
        contents->setLayout(layout);
    } else {
        // 기존 위젯들 삭제
        clearLayout(layout);
    }

    // 리스트가 새로 로드되면 기존 선택된 아이템 초기화
    m_selectedItem = nullptr;

    // JSON에서 불러온 데이터 삽입
    for (const ScheduleData &data : schedules) {
        ScheduleItem *item = new ScheduleItem(contents);

        // ScheduleItem에 실제 데이터 세팅
        item->setScheduleData(data);

        // 아이템 클릭 / 더블 클릭 시그널 연결
        connect(item, &ScheduleItem::itemClicked, this, &SidebarContentManager::handleItemClicked);
        connect(item, &ScheduleItem::itemDoubleClicked, this, &SidebarContentManager::scheduleItemDoubleClicked);

        layout->addWidget(item);
    }
    // 위젯들을 위쪽으로 정렬하기 위한 빈 공간 추가
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

// 리스트에서 아이템을 클릭했을 때 선택 상태(배경색)를 바꿔주는 함수
void SidebarContentManager::handleItemClicked(ScheduleItem *item) {
    // 1. 이전에 선택되어 있던 아이템의 색상을 원래대로 되돌림
    if (m_selectedItem) {
        m_selectedItem->setSelectedStyle(false);
    }

    // 방금 클릭한 새로운 아이템을 기억
    m_selectedItem = item;

    // 새로 선택된 아이템의 배경색을 회색으로 변경
    if (m_selectedItem) {
        m_selectedItem->setSelectedStyle(true);
    }
}