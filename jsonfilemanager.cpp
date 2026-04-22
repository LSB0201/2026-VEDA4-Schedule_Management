#include "jsonfilemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

JsonFileManager::JsonFileManager(const QString &filePath)
    : m_filePath(filePath) {}

bool JsonFileManager::saveAll(const QList<ScheduleData> &schedules) {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "파일 열기 실패:" << m_filePath;
        return false;
    }

    QJsonArray jsonArray;
    for (const ScheduleData &data : schedules) {
        jsonArray.append(data.toJson());
    }

    QJsonDocument doc(jsonArray);
    file.write(doc.toJson(QJsonDocument::Indented)); // 들여쓰기 저장
    file.close();
    return true;
}

QList<ScheduleData> JsonFileManager::loadAll() {
    QList<ScheduleData> schedules;
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return schedules; // 파일이 없으면 빈 리스트 반환
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isArray()) {
        QJsonArray jsonArray = doc.array();
        for (const QJsonValue &value : jsonArray) {
            schedules.append(ScheduleData::fromJson(value.toObject()));
        }
    }
    return schedules;
}
