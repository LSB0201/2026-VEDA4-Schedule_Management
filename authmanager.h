#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

class AuthManager : public QObject {
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

    // ID 중복 체크
    void checkId(const QString &id);
    // 회원가입 (ID, PW, Name)
    void registerUser(const QString &id, const QString &pw, const QString &name);
    // 로그인
    void login(const QString &id, const QString &pw);

signals:
    void idCheckFinished(bool available, QString message);
    void registerFinished(bool success, QString message);
    void loginFinished(bool success, QString message, QString userName);

private:
    QNetworkAccessManager *manager;
    QString baseUrl = "https://dev.vlolet.com/api";
    void handleResponse(QNetworkReply *reply, std::function<void(const QJsonObject&, bool)> callback);
};

#endif