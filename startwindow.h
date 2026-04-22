#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

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
    bool valid_chk();
    void onLoginFinished(bool success, QString message);

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

    // p3. Profile
    void onProfileCreateBtnClicked();
};

#endif // STARTWINDOW_H
