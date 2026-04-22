#ifndef SCHEDULESAVE_H
#define SCHEDULESAVE_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
#include <QColor>
#include <QJsonObject>
#include <QList>

class JsonFileManager;

// UI와 Manager 사이에서 데이터를 주고받을 구조체
struct ScheduleData {
    QString title;
    QColor color;
    QDate startDate;
    QTime startTime;
    QDate endDate;
    QTime endTime;
    QString memo;

    // JSON 직렬화/역직렬화 함수 선언
    QJsonObject toJson() const;
    static ScheduleData fromJson(const QJsonObject &json);
};

class ScheduleSave : public QObject {
    Q_OBJECT
public:
    explicit ScheduleSave(QObject *parent = nullptr);
    ~ScheduleSave();

    // 일정 저장 함수
    bool saveSchedule(const ScheduleData &data);

private:
    QList<ScheduleData> m_schedules; // 메모리에 유지할 일정 리스트
    JsonFileManager *m_fileManager;  // 파일 저장 매니저

signals:
    // 저장이 성공적으로 완료되었음을 UI 갱신을 위해 알리는 시그널
    void scheduleSavedSuccessfully();
};

#endif // SCHEDULESAVE_H