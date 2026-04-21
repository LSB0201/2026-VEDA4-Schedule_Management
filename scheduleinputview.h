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

private:
    Ui::ScheduleInputView *ui;
};

#endif // SCHEDULEINPUTVIEW_H
