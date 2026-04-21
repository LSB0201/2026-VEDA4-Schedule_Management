#include "scheduleinputview.h"
#include "ui_scheduleinputview.h"

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
