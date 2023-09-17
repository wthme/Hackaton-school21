#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

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
    void onReply(QNetworkReply* reply);

    void on_to_sign_up_clicked();

    void on_sign_up_button_clicked();

    void on_to_log_in_clicked();

private:
    Ui::LogInWindow *ui;
    QNetworkAccessManager* manager;
    QNetworkRequest *request;
};

#endif // LOGINWINDOW_H
