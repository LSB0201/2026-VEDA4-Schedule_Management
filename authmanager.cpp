#include "authmanager.h"

AuthManager::AuthManager(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void AuthManager::checkId(const QString &id) {
    QNetworkRequest request(QUrl(baseUrl + "/check-id"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
            emit idCheckFinished(res.object()["success"].toBool(), res.object()["message"].toString());
        } else {
            emit idCheckFinished(false, "서버 연결 실패");
        }
        reply->deleteLater();
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

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
            emit registerFinished(res.object()["success"].toBool(), res.object()["message"].toString());
        } else {
            emit registerFinished(false, "회원가입 실패");
        }
        reply->deleteLater();
    });
}