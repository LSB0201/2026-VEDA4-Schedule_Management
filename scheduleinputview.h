#ifndef SCHEDULEINPUTVIEW_H
#define SCHEDULEINPUTVIEW_H

#include <QWidget>
#include "schedulesave.h"
#include <QButtonGroup>

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
    QColor m_selectedColor = QColor("#FF7E33"); // 기본 색상 (주황)
    QButtonGroup *m_colorGroup;

signals:
    // Save 버튼을 눌렀을 때 데이터를 실어 보낼 시그널
    void saveRequested(const ScheduleData &data);

private slots:
    void onSaveClicked();
    void onColorButtonClicked(QAbstractButton *button); // 색상 버튼 클릭 처리
};

#endif // SCHEDULEINPUTVIEW_H
