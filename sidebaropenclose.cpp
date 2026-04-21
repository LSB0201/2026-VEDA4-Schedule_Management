#include "sidebaropenclose.h"
#include <QEvent>
#include <QMouseEvent>

SidebarOpenClose::SidebarOpenClose(QWidget *sidebar, QPushButton *closeBtn, QWidget *parentWindow, QObject *parent)
    : QObject(parent), m_sidebar(sidebar), m_closeBtn(closeBtn), m_parentWindow(parentWindow)
{
    // 닫기 버튼 이벤트 연결
    connect(m_closeBtn, &QPushButton::clicked, this, &SidebarOpenClose::closeSidebar);

    // 외부 클릭 감지를 위해 부모 창에 이벤트 필터 설치
    m_parentWindow->installEventFilter(this);
}

void SidebarOpenClose::openSidebar() {
    m_sidebar->setVisible(true);
}

void SidebarOpenClose::closeSidebar() {
    m_sidebar->setVisible(false);
    emit sidebarClosed(); // 달력 선택 해제 등을 위해 시그널 발생
}

// 이벤트 가로채기(외부 클릭 감지)
bool SidebarOpenClose::eventFilter(QObject *watched, QEvent *event) {
    if (watched == m_parentWindow && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // 사이드바가 열려있고, 클릭한 위치가 사이드바 영역 밖이라면 닫기
        if (m_sidebar->isVisible() && !m_sidebar->geometry().contains(mouseEvent->pos())) {
            closeSidebar();
        }
    }
    return QObject::eventFilter(watched, event);
}