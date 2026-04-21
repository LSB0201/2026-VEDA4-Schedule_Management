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

private slots:
    void onLoginPageRequested();
    void onSignUpPageRequested();
    void onLoginRequested();
};

#endif // STARTWINDOW_H
