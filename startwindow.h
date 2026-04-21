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

private slots:
    void onLoginPageRequested();
    void onSignUpPageRequested();
    void onLoginRequested();

    void onSignUpNextBtnClicked();
    void onProfilePageRequested();

    void onProfileCreateBtnClicked();
};

#endif // STARTWINDOW_H
