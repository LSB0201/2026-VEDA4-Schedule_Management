#include "ScheduleSearchView.h"
#include "ScheduleSearchResultItem.h"
#include <QLabel>
#include <QScrollArea>

ScheduleSearchView::ScheduleSearchView(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void ScheduleSearchView::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 20, 40, 20);
    mainLayout->setSpacing(0);

    // 1. Title Label (Find Your Flow)
    QLabel *titleLabel = new QLabel("Find Your Flow.", this);
    QFont titleFont("Roboto", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setContentsMargins(0, 0, 0, 20);
    mainLayout->addWidget(titleLabel);

    // 2. QtMaterialAutoComplete (Search Bar)
    m_searchBar = new QtMaterialAutoComplete(this);
    m_searchBar->setPlaceholderText("Search schedules by title...");
    m_searchBar->setInkColor(QColor("#ef6c00")); // 오렌지 포인트 컬러
    mainLayout->addWidget(m_searchBar);
    mainLayout->addSpacing(40);

    // 3. Result Area
    QLabel *recentLabel = new QLabel("Recent Schedule Matches", this);
    recentLabel->setStyleSheet("font-weight: bold; color: #555;");
    mainLayout->addWidget(recentLabel);
    mainLayout->addSpacing(15);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background-color: transparent;");

    QWidget *scrollContainer = new QWidget();
    scrollContainer->setStyleSheet("background-color: transparent;");
    m_resultsLayout = new QVBoxLayout(scrollContainer);
    m_resultsLayout->setAlignment(Qt::AlignTop);
    m_resultsLayout->setSpacing(15);
    m_resultsLayout->setContentsMargins(5, 5, 5, 5);
    scrollArea->setWidget(scrollContainer);
    mainLayout->addWidget(scrollArea);

    connect(m_searchBar, &QLineEdit::textChanged, this, &ScheduleSearchView::onSearchTextChanged);
}

void ScheduleSearchView::setScheduleData(const QList<ScheduleData> &data) {
    m_allSchedules = data;
    QStringList titles;
    for(const auto &s : data) {
        titles << s.title;
    }
    m_searchBar->setDataSource(titles); // 오토컴플리트 데이터 소스 설정
    updateSearchResults(""); // 초기 로드
}

void ScheduleSearchView::onSearchTextChanged(const QString &text) {
    updateSearchResults(text);
}

void ScheduleSearchView::updateSearchResults(const QString &filter) {
    // 기존 아이템 삭제
    QLayoutItem *item;
    while ((item = m_resultsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (const auto &data : m_allSchedules) {
        if (filter.isEmpty() || data.title.contains(filter, Qt::CaseInsensitive)) {
            ScheduleSearchResultItem *resultWidget = new ScheduleSearchResultItem(data, this);
            m_resultsLayout->addWidget(resultWidget);
        }
    }
}