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

    void setDefaultDate(const QDate &date); // 일정 입력창 날짜 기본값 현재 날짜로 설정
    void setEditData(const ScheduleData &data); // 수정시 기존 일정 내용을 기본값으로 설정

private:
    Ui::ScheduleInputView *ui;
    QColor m_selectedColor = QColor("#FF7E33"); // 기본 색상 (주황)
    QButtonGroup *m_colorGroup;

    bool m_isEditMode = false;
    ScheduleData m_originalData;

signals:
    // Save 버튼을 눌렀을 때 데이터를 실어 보낼 시그널
    void saveRequested(const ScheduleData &data);
    void editRequested(const ScheduleData &oldData, const ScheduleData &newData);

private slots:
    void onSaveClicked();
    void onColorButtonClicked(QAbstractButton *button); // 색상 버튼 클릭 처리
};

#endif // SCHEDULEINPUTVIEW_H
