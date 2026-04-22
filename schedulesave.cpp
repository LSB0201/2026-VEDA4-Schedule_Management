#include "schedulesave.h"
#include "jsonfilemanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

ScheduleSave::ScheduleSave(QObject *parent) : QObject(parent) {
    // 실행 파일 위치에서 출발
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp(); // 상위 폴더로 2번 이동
    dir.cdUp();

    // 표 폴더 경로 설정
    QString targetFolder = "resources/user_data";

    // 해당 폴더가 없다면 자동으로 생성
    if (!dir.exists(targetFolder)) {
        dir.mkpath(targetFolder);
    }
    QString savePath = dir.filePath(targetFolder + "/schedules.json");

    // 완성된 상대 경로로 파일 매니저 생성
    m_fileManager = new JsonFileManager(savePath);

    // 프로그램 시작 시 기존 데이터 불러와서 m_schedules에 저장
    m_schedules = m_fileManager->loadAll();
}

ScheduleSave::~ScheduleSave() {
    delete m_fileManager; // 동적 할당한 매니저 해제
}

// 제목 검사: 비어있으면 기본값 "새로운 일정" 할당
bool ScheduleSave::saveSchedule(const ScheduleData &data) {

    // const 파라미터를 수정하기 위한 finalData 생성
    ScheduleData finalData = data;

    if (finalData.title.trimmed().isEmpty()) {
        finalData.title = "새로운 일정";
        qDebug() << "제목이 입력되지 않아 '새로운 일정'으로 자동 저장됩니다.";
    }

    // 메모리 리스트에 수정한 새 일정 추가
    m_schedules.append(finalData);

    // 파일 매니저에게 리스트 전체를 JSON 파일로 덮어쓰라고 명령
    if (m_fileManager->saveAll(m_schedules)) {
        qDebug() << "일정 저장 완료! 제목:" << finalData.title;
        emit scheduleSavedSuccessfully(); // MainWindow 갱신을 위한 시그널 발송
        return true;
    }
    return false;
}

QJsonObject ScheduleData::toJson() const {
    QJsonObject json;
    json["title"] = title;
    json["color"] = color.name(); // "#FF7E33" 형식의 문자열로 저장
    json["startDate"] = startDate.toString(Qt::ISODate); // "yyyy-MM-dd"
    json["startTime"] = startTime.toString(Qt::ISODate); // "HH:mm:ss"
    json["endDate"] = endDate.toString(Qt::ISODate);
    json["endTime"] = endTime.toString(Qt::ISODate);
    json["memo"] = memo;
    return json;
}

ScheduleData ScheduleData::fromJson(const QJsonObject &json) {
    ScheduleData data;
    data.title = json["title"].toString();
    data.color = QColor(json["color"].toString());
    data.startDate = QDate::fromString(json["startDate"].toString(), Qt::ISODate);
    data.startTime = QTime::fromString(json["startTime"].toString(), Qt::ISODate);
    data.endDate = QDate::fromString(json["endDate"].toString(), Qt::ISODate);
    data.endTime = QTime::fromString(json["endTime"].toString(), Qt::ISODate);
    data.memo = json["memo"].toString();
    return data;
}

QList<ScheduleData> ScheduleSave::getSchedulesForDate(const QDate &date) const {
    QList<ScheduleData> result;
    for (const ScheduleData &data : m_schedules) {
        // 일정이 시작 날짜와 종료 날짜 사이에 포함되는지 확인
        if (date >= data.startDate && date <= data.endDate) {
            result.append(data);
        }
    }
    return result;
}