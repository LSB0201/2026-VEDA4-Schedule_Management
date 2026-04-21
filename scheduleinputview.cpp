#include "scheduleinputview.h"
#include "ui_ScheduleInputView.h"

ScheduleInputView::ScheduleInputView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleInputView)
{
    ui->setupUi(this);
}

ScheduleInputView::~ScheduleInputView()
{
    delete ui;
}

void ScheduleInputView::showNextTo(QWidget *targetWidget) {
    // 1. 자신의 창 속성 설정
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);

    // 2. 타겟 위젯(사이드바)의 위치를 바탕으로 내 위치 계산
    QPoint targetGlobalPos = targetWidget->mapToGlobal(QPoint(0, 0));
    int targetX = targetGlobalPos.x() - this->width();
    int targetY = targetGlobalPos.y();

    // 3. 이동 및 출력
    this->move(targetX, targetY);
    this->show();
}
