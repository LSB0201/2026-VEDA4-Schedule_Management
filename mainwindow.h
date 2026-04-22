#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "sidebaropenclose.h"
#include "sidebarcontentmanager.h"
#include "schedulesave.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:

private:
    Ui::MainWindow *ui;

    int m_currentYear;
    int m_currentMonth;

    SidebarOpenClose *m_sidebarController; // 사이드바 On/Off에 관한 객체
    SidebarContentManager *m_contentManager; // 사이드바 일정 표시에 관한 겍체
    ScheduleSave *m_scheduleSave; // 일정 저장에 관한 객체

    void showScheduleInput(); // 입력 창 띄우는 함수 선언
    void updateMonthLabel(); // 상단 라벨 텍스트를 갱신하는 함수
    void generateCalendar(int year, int month);

private slots:
    void onSearchButtonClicked();
};
#endif // MAINWINDOW_H