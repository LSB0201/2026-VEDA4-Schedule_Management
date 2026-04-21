#ifndef SCHEDULEINPUTVIEW_H
#define SCHEDULEINPUTVIEW_H

#include <QWidget>

namespace Ui {
class ScheduleInputView;
}

class ScheduleInputView : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleInputView(QWidget *parent = nullptr);
    ~ScheduleInputView();

    // 특정 위젯(사이드바) 옆에 나타나게 하는 전용 함수 선언
    void showNextTo(QWidget *targetWidget);

private:
    Ui::ScheduleInputView *ui;
};

#endif // SCHEDULEINPUTVIEW_H
