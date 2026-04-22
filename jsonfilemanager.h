#ifndef JSONFILEMANAGER_H
#define JSONFILEMANAGER_H

#include <QString>
#include <QList>
#include "schedulesave.h" // ScheduleData 구조체 사용

class JsonFileManager {
public:
    explicit JsonFileManager(const QString &filePath);

    // 전체 리스트를 파일에 덮어쓰기
    bool saveAll(const QList<ScheduleData> &schedules);

    // 파일에서 전체 리스트 불러오기
    QList<ScheduleData> loadAll();

private:
    QString m_filePath;
};

#endif // JSONFILEMANAGER_H