#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class LogInWindow;
};

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();

signals:
    void loginSuccess();

private slots:
    void on_sign_in_button_clicked();
    void onLogInRequest(QNetworkReply* reply);

private:
    Ui::LogInWindow *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest *request;
};

#endif // LOGINWINDOW_H
