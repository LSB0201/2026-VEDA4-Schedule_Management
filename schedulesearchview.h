#ifndef SCHEDULESEARCHVIEW_H
#define SCHEDULESEARCHVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QVBoxLayout>
#include "qtmaterialautocomplete.h"

class ScheduleSearchView : public QWidget {
    Q_OBJECT
public:
    explicit ScheduleSearchView(QWidget *parent = nullptr);
    void setScheduleData(const QJsonArray &data);

private slots:
    void onSearchTextChanged(const QString &text);

private:
    QtMaterialAutoComplete *m_searchBar;
    QVBoxLayout *m_resultsLayout;
    QJsonArray m_allSchedules;

    void setupUi();
    void updateSearchResults(const QString &filter);
};

#endif