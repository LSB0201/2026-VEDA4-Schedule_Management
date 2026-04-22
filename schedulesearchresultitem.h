#include <QWidget>
#include "schedulesave.h"

class ScheduleSearchResultItem : public QWidget {
    Q_OBJECT
public:
    explicit ScheduleSearchResultItem(const ScheduleData &data, QWidget *parent = nullptr);
};