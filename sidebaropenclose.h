#ifndef SIDEBAROPENCLOSE_H
#define SIDEBAROPENCLOSE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class SidebarOpenClose : public QObject {
    Q_OBJECT
public:
    explicit SidebarOpenClose(QWidget *sidebar, QPushButton *closeBtn, QWidget *parentWindow, QObject *parent = nullptr);

    void openSidebar();
    void closeSidebar();

signals:
    void sidebarClosed(); // 닫혔을 때 MainWindow에 알림을 주기 위한 시그널

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget *m_sidebar;
    QPushButton *m_closeBtn;
    QWidget *m_parentWindow;
};

#endif // SIDEBAROPENCLOSE_H