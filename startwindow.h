#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include "authmanager.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private:
    Ui::StartWindow *ui;
    QString id;
    QString pw;
    QString pwc;
    QString nickname;
    AuthManager* authManager = new AuthManager(this);
    bool valid_chk();
    void onLoginFinished(bool success, QString message, QString userName);

private slots:
    // p1. Login
    void onLoginPageRequested();
    void onSignUpPageRequested();
    void onLoginRequested();

    // p2. Sign Up
    void onSignUpNextBtnClicked();
    void onProfilePageRequested();
    void onSignUpCheckBoxPWClicked();
    void onSignUpCheckBoxPWCClicked();
    void onIdCheckFinished(bool available, QString message);

    // p3. Profile
    void onProfileCreateBtnClicked();
    void onRegisterFinished(bool success, QString message);
};

#endif // STARTWINDOW_H
