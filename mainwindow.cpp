#include <QHeaderView>
#include <QDate> // 날짜 처리를 위해 추가
#include <QMessageBox> // 알림/경고창을 띄우기 위해 추가

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "daycellwidget.h"
#include "sidebaropenclose.h"
#include "sidebarcontentmanager.h"
#include "scheduleinputview.h"
#include "schedulesearchview.h"
#include "scheduleitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pageStack->setCurrentIndex(0);// 나중에 삭제

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

    // 기본 선택 표시 완전히 끄기
    ui->calendarTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->calendarTable->setFocusPolicy(Qt::NoFocus);

    // 상단 년/월 네비게이션 초기화 및 버튼 연결
    QDate today = QDate::currentDate();
    m_currentYear = today.year();
    m_currentMonth = today.month();
    updateMonthLabel(); // 라벨에 현재 달 표시

    // 이전 달 버튼(<) 클릭 시
    connect(ui->prevMonthBtn, &QPushButton::clicked, this, [=](){
        m_currentMonth--;
        if(m_currentMonth < 1) {
            m_currentMonth = 12;
            m_currentYear--;
        }
        updateMonthLabel();
        generateCalendar(m_currentYear, m_currentMonth); // 달력 다시 그리기
    });

    // 다음 달 버튼(>) 클릭 시
    connect(ui->nextMonthBtn, &QPushButton::clicked, this, [=](){
        m_currentMonth++;
        if(m_currentMonth > 12) {
            m_currentMonth = 1;
            m_currentYear++;
        }
        updateMonthLabel();
        generateCalendar(m_currentYear, m_currentMonth); // 달력 다시 그리기
    });

    // 사이드바가 닫힐 때 달력 선택을 해제
    connect(m_sidebarController, &SidebarOpenClose::sidebarClosed, this, [=](){
        for(int r = 0; r < 6; ++r) {
            for(int c = 0; c < 7; ++c) {
                DayCellWidget *cell = qobject_cast<DayCellWidget*>(ui->calendarTable->cellWidget(r, c));
                if(cell) cell->setSelected(false);
            }
        }
    });

    // 2. 셀 클릭 이벤트 연결
    connect(ui->calendarTable, &QTableWidget::cellClicked, this, [=](int row, int col){
        // 모든 셀을 순회하며 선택 해제
        for(int r = 0; r < 6; ++r) {
            for(int c = 0; c < 7; ++c) {
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

            // 매니저에게 실제 데이터 리스트를 넘겨주어 사이드바에 표시
            QList<ScheduleData> dailySchedules = m_scheduleSave->getSchedulesForDate(selectedDate);
            m_contentManager->loadSchedules(dailySchedules);

            // 사이드바 열기
            m_sidebarController->openSidebar();
        }
    });

    // Add Schedule 버튼 클릭 시 (새 일정 추가)
    connect(ui->addScheduleButton, &QPushButton::clicked, this, &MainWindow::showScheduleInput);


    // 기존 일정 '더블 클릭' 시 수정 모드로 창 띄우기
    connect(m_contentManager, &SidebarContentManager::scheduleItemDoubleClicked, this, [=](const ScheduleData& data){
        ScheduleInputView *inputView = new ScheduleInputView(this);
        inputView->setAttribute(Qt::WA_DeleteOnClose);

        // 기존 데이터를 입력창에 채워줌 (수정 모드 활성화)
        inputView->setEditData(data);

        // Save 버튼을 눌렀을 때, 새 일정이 아니라 '수정' 로직이 실행되도록 연결
        connect(inputView, &ScheduleInputView::editRequested, m_scheduleSave, &ScheduleSave::updateSchedule);

        // 저장이 완료되면 화면 갱신
        connect(m_scheduleSave, &ScheduleSave::scheduleSavedSuccessfully, this, [=](){
            generateCalendar(m_currentYear, m_currentMonth);
            if (ui->frame_2->isVisible()) {
                QDate currentSelected = QDate::fromString(ui->todayLabel->text(), "yyyy. M. d");
                if (currentSelected.isValid()) {
                    m_contentManager->loadSchedules(m_scheduleSave->getSchedulesForDate(currentSelected));
                }
            }
        });

        inputView->showNextTo(ui->frame_2);
    });

    // 'Delete Schedule' 버튼 클릭 시 선택된 일정 삭제
    connect(ui->deleteScheduleButton, &QPushButton::clicked, this, [=](){
        ScheduleItem *selectedItem = m_contentManager->getSelectedItem();

        if (selectedItem) {
            // 사용자에게 한 번 더 물어보는 경고창
            int ret = QMessageBox::question(this, "일정 삭제", "선택한 일정을 삭제하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                // ScheduleSave 매니저에게 삭제 요청
                m_scheduleSave->deleteSchedule(selectedItem->getScheduleData());
            }
        } else {
            // 아무것도 선택하지 않고 삭제를 눌렀을 때의 경고창
            QMessageBox::warning(this, "알림", "삭제할 일정을 먼저 한 번 클릭하여 선택해주세요.");
        }
    });

    // 좌측 프레임 버튼 클릭 이벤트 연결
    connect(ui->leftFrameBtnHome, &QPushButton::clicked, this, &MainWindow::onLeftFrameHomeButtonClicked);
    connect(ui->leftFrameBtnCalendar, &QPushButton::clicked, this, &MainWindow::onLeftFrameCalendarButtonClicked);
    connect(ui->leftFrameBtnSearch, &QPushButton::clicked, this, &MainWindow::onLeftFrameSearchButtonClicked);
    connect(ui->leftFrameBtnProfile, &QPushButton::clicked, this, &MainWindow::onLeftFrameProfileButtonClicked);
    connect(ui->leftFrameBtnLogout, &QPushButton::clicked, this, &MainWindow::onLeftFrameLogoutButtonClicked);

    // 프로그램 시작 시 최초 달력 그리기
    generateCalendar(m_currentYear, m_currentMonth);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 상단 라벨 텍스트 갱신
void MainWindow::updateMonthLabel() {
    ui->currentMonthLabel->setText(QString("%1. %2월").arg(m_currentYear).arg(m_currentMonth));
}

void MainWindow::generateCalendar(int year, int month) {
    ui->calendarTable->clear(); // 기존 셀 초기화 (이전 달/다음 달 이동 시 필요)

    QDate firstDay(year, month, 1);
    int daysInMonth = firstDay.daysInMonth();

    // Qt에서 요일: 월요일=1, 화요일=2 ... 일요일=7
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

        // 해당 날짜의 일정을 불러와서 셀에 태그로 그려줌
        QList<ScheduleData> dailySchedules = m_scheduleSave->getSchedulesForDate(currentDate);
        for(const ScheduleData &data : dailySchedules) {
            cell->addScheduleTag(data);
        }

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


    // 5단계 핵심 3: 새 일정 추가 시 사이드바 상단의 날짜를 기본값으로
    QDate selectedDate = QDate::fromString(ui->todayLabel->text(), "yyyy. M. d");
    if (selectedDate.isValid()) {
        inputView->setDefaultDate(selectedDate);
    }

    // InputView에서 저장을 요청 -> ScheduleSave가 처리
    connect(inputView, &ScheduleInputView::saveRequested, m_scheduleSave, &ScheduleSave::saveSchedule);

    // ScheduleSave가 저장을 완료 -> 화면 전체 새로고침
    connect(m_scheduleSave, &ScheduleSave::scheduleSavedSuccessfully, this, [=](){
        // 달력 새로고침 (태그 다시 그리기)
        generateCalendar(m_currentYear, m_currentMonth);

        // 사이드바가 열려있다면 사이드바 목록도 즉시 갱신
        if (ui->frame_2->isVisible()) {
            QDate currentSelected = QDate::fromString(ui->todayLabel->text(), "yyyy. M. d");
            if (currentSelected.isValid()) {
                m_contentManager->loadSchedules(m_scheduleSave->getSchedulesForDate(currentSelected));
            }
        }
    });

    // ScheduleInputView 스스로 사이드바(ui->frame_2) 옆에 뜨도록 명령
    inputView->showNextTo(ui->frame_2);
}

// slots
void MainWindow::onLeftFrameHomeButtonClicked(){
    ui->pageStack->setCurrentWidget(ui->pageCalendar);
}

void MainWindow::onLeftFrameCalendarButtonClicked(){
    ui->pageStack->setCurrentWidget(ui->pageCalendar);
}

// stackedwidget이 없어서 주석처리함
void MainWindow::onLeftFrameSearchButtonClicked() {
    // ScheduleSearchView *searchView = new ScheduleSearchView(this);

    // // 팀원이 제공할 JSON 데이터를 가져와서 전달
    // QJsonArray dummyData = loadJsonFromFile("data.json");
    // searchView->setScheduleData(dummyData);

    ui->pageStack->setCurrentWidget(ui->pageSearch);
}

void MainWindow::onLeftFrameProfileButtonClicked(){
    ui->pageStack->setCurrentWidget(ui->pageProfile);
}

void MainWindow::onLeftFrameLogoutButtonClicked(){
    qDebug() << "로그아웃 버튼 누름";
    // TODO : 로그아웃 구현 (개인정보로 이동)
}