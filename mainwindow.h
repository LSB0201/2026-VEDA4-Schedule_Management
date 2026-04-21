#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "sidebaropenclose.h"
#include "sidebarcontentmanager.h"

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
    void generateCalendar(int year, int month);
    SidebarOpenClose *m_sidebarController;
    SidebarContentManager *m_contentManager;
};
#endif // MAINWINDOW_H
