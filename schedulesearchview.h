#ifndef SCHEDULESEARCHVIEW_H
#define SCHEDULESEARCHVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QList>
#include "schedulesave.h"
#include "qtmaterialautocomplete.h"

class ScheduleSearchView : public QWidget {
    Q_OBJECT
public:
    explicit ScheduleSearchView(QWidget *parent = nullptr);
    void setScheduleData(const QList<ScheduleData> &data);

private slots:
    void onSearchTextChanged(const QString &text);

private:
    QtMaterialAutoComplete *m_searchBar;
    QVBoxLayout *m_resultsLayout;
    QList<ScheduleData> m_allSchedules;

    void setupUi();
    void updateSearchResults(const QString &filter);
};

#endif