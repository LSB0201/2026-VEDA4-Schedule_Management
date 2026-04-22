#include <QWidget>
#include <QJsonObject>

class ScheduleSearchResultItem : public QWidget {
    Q_OBJECT
public:
    explicit ScheduleSearchResultItem(const QJsonObject &data, QWidget *parent = nullptr);
};