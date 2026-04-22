#include "authmanager.h"
#include <QJsonArray>

AuthManager::AuthManager(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

// 공통 응답 처리 함수 (코드 중복 방지를 위해 내부적으로 사용)
void AuthManager::handleResponse(QNetworkReply *reply, std::function<void(const QJsonObject&, bool)> callback) {
    connect(reply, &QNetworkReply::finished, [reply, callback]() {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        if (reply->error() == QNetworkReply::NoError) {
            // 성공 (HTTP 200)
            callback(obj, true);
        } else {
            // 서버 에러 (HTTP 400, 401 등) 혹은 네트워크 장애
            if (!data.isEmpty() && !obj.isEmpty()) {
                // 서버가 JSON으로 에러 메시지를 보낸 경우 (아이디 중복, 비번 틀림 등)
                callback(obj, false);
            } else {
                // 아예 서버에 접속을 못 한 경우
                QJsonObject errorObj;
                errorObj["message"] = "서버와 연결할 수 없습니다. (네트워크 오류)";
                callback(errorObj, false);
            }
        }
        reply->deleteLater();
    });
}

void AuthManager::checkId(const QString &id) {
    QNetworkRequest request(QUrl(baseUrl + "/check-id"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    handleResponse(reply, [this](const QJsonObject& obj, bool success) {
        emit idCheckFinished(success, obj["message"].toString());
    });
}

void AuthManager::registerUser(const QString &id, const QString &pw, const QString &name) {
    QNetworkRequest request(QUrl(baseUrl + "/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;
    json["password"] = pw;
    json["name"] = name;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    handleResponse(reply, [this](const QJsonObject& obj, bool success) {
        emit registerFinished(success, obj["message"].toString());
    });
}

void AuthManager::login(const QString &id, const QString &pw) {
    QNetworkRequest request(QUrl(baseUrl + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;
    json["password"] = pw;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    handleResponse(reply, [this](const QJsonObject& obj, bool success) {
        QString userName = "";
        if (success && obj.contains("user")) {
            userName = obj["user"].toObject()["name"].toString();
        }
        emit loginFinished(success, obj["message"].toString(), userName);
    });
}