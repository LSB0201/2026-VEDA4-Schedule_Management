#include <QHeaderView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "daycellwidget.h" // 커스텀 위젯 헤더 포함
#include "sidebaropenclose.h"
#include "sidebarcontentmanager.h"
#include "scheduleinputview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->frame_2->setVisible(false); // 사이드바 초기 숨김

    // 객체 생성
    m_sidebarController = new SidebarOpenClose(ui->frame_2, ui->closeSideBar, this, this);
    m_contentManager = new SidebarContentManager(ui->scrollArea, this);
    m_scheduleSave = new ScheduleSave(this);

    // QTableWidget 기본 형태 세팅
    ui->calendarTable->setRowCount(6);    // 최대 6주
    ui->calendarTable->setColumnCount(7); // 일~토 7일
    ui->calendarTable->horizontalHeader()->hide(); // 가로 헤더 숨김
    ui->calendarTable->verticalHeader()->hide();   // 세로 헤더 숨김
    ui->calendarTable->setShowGrid(false);         // 기본 격자선 숨김

    // 칸 크기를 창 크기에 맞춰 균등하게 늘림
    ui->calendarTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->calendarTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 기본 선택 표시(파란색 배경 등)를 완전히 끄기
    ui->calendarTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->calendarTable->setFocusPolicy(Qt::NoFocus);

    // 사이드바가 닫힐 때 달력 선택을 해제
    connect(m_sidebarController, &SidebarOpenClose::sidebarClosed, this, [=](){
        for(int r = 0; r < 6; ++r) {
            for(int c = 0; c < 7; ++c) {
                DayCellWidget *cell = qobject_cast<DayCellWidget*>(ui->calendarTable->cellWidget(r, c));
                if(cell) cell->setSelected(false);
            }
        }
    });

    // 셀 클릭 이벤트 연결
    connect(ui->calendarTable, &QTableWidget::cellClicked, this, [=](int row, int col){
        // 모든 셀을 순회하며 선택 해제
        for(int r = 0; r < 6; ++r) {
            for(int c = 0; c < 7; ++c) {
                // TableWidget에 넣은 위젯을 원래 자료형으로 캐스팅
                DayCellWidget *cell = qobject_cast<DayCellWidget*>(ui->calendarTable->cellWidget(r, c));
                if(cell) {
                    cell->setSelected(false);
                }
            }
        }
        // 클릭된 셀 처리
        DayCellWidget *clickedCell = qobject_cast<DayCellWidget*>(ui->calendarTable->cellWidget(row, col));
        if(clickedCell) {
            clickedCell->setSelected(true);
            QDate selectedDate = clickedCell->getDate();

            // 상단 날짜 라벨 텍스트 변경
            ui->todayLabel->setText(selectedDate.toString("yyyy. M. d"));

            // 사이드바에 일정 채우기
            m_contentManager->loadSchedulesForDate(selectedDate);

            // 사이드바 열기
            m_sidebarController->openSidebar();
        }
    });

    // Add Schedule; 버튼 클릭 시 입력 창 출력
    connect(ui->addScheduleButton, &QPushButton::clicked, this, &MainWindow::showScheduleInput);
    // 기존 일정 클릭 시 입력 창 띄우기(메니저의 시그널 사용)
    connect(m_contentManager, &SidebarContentManager::scheduleItemClicked, this, &MainWindow::showScheduleInput);

    // 달력 그리기 실행
    generateCalendar(2026, 4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateCalendar(int year, int month) {
    ui->calendarTable->clear(); // 기존 셀 초기화 (이전 달/다음 달 이동 시 필요)

    QDate firstDay(year, month, 1);
    int daysInMonth = firstDay.daysInMonth();

    // Qt에서 요일: 월요일=1, 화요일=2 ... 일요일=7
    // 일요일(첫 번째 열, index 0) 시작 달력을 만들기 위한 변환 연산
    int startDayOfWeek = firstDay.dayOfWeek();
    int startColIndex = (startDayOfWeek == 7) ? 0 : startDayOfWeek;

    int row = 0;
    int col = startColIndex;

    // 1일부터 말일까지 순회하며 위젯 삽입
    for (int day = 1; day <= daysInMonth; ++day) {
        QDate currentDate(year, month, day);
        bool isToday = (currentDate == QDate::currentDate());

        // 커스텀 위젯 생성
        DayCellWidget *cell = new DayCellWidget(currentDate, isToday, this);

        // 테이블의 (row, col) 위치에 위젯 삽입
        ui->calendarTable->setCellWidget(row, col, cell);

        col++;
        // 토요일(인덱스 6)을 넘어가면 다음 줄(일요일)로 이동
        if (col > 6) {
            col = 0;
            row++;
        }
    }
}

void MainWindow::showScheduleInput() {
    // 객체 생성
    ScheduleInputView *inputView = new ScheduleInputView(this);

    // 입력창 종료시 메모리에서 자동 해제
    inputView->setAttribute(Qt::WA_DeleteOnClose);

    // InputView에서 저장을 요청 -> ScheduleSave가 처리
    connect(inputView, &ScheduleInputView::saveRequested, m_scheduleSave, &ScheduleSave::saveSchedule);

    // ScheduleSave가 저장을 완료 -> 스크롤뷰나 달력을 갱신하도록 연결
    connect(m_scheduleSave, &ScheduleSave::scheduleSavedSuccessfully, this, [=](){
        // 현재 선택된 날짜의 일정을 다시 불러오는 로직
        // m_contentManager->loadSchedulesForDate(...);
    });

    // ScheduleInputView 스스로 사이드바(ui->frame_2) 옆에 뜨도록 명령
    inputView->showNextTo(ui->frame_2);
}