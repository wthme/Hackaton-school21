#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "utility.h"

LogInWindow::LogInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    request = new QNetworkRequest;

    ui->sign_up_widg->hide();


    // |
    // v вот это юзать для use_event_code (по возможности)
    //ui->widget->hide();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReply(QNetworkReply*)));
}


LogInWindow::~LogInWindow()
{
    delete request;
    delete manager;
    delete ui;        
}


void LogInWindow::onReply(QNetworkReply* reply) {
    qDebug() << reply->error();
    if (ui->log_in_widg->isVisible()) {
        if (reply->error() == QNetworkReply::NoError) {
            emit loginSuccess();
        } else if (reply->error() == 401) {
            ui->loginErrorLine->setText("Incorrect login/password");
        }
    } else {
        if (reply->error() == QNetworkReply::NoError) {
            ui->sign_up_widg->hide();
            ui->log_in_widg->show();
            ui->loginErrorLine->setText("Signed in successfuly");
        } else if (reply->error() == 401) {
            ui->signUpErrorLine->setText("Internal Error");
        }
    }

}


void LogInWindow::on_sign_in_button_clicked()
{
    QJsonObject json_req;

    QString login = ui->login_line->text();
    QString pswd = ui->password_line->text();
    login = login.trimmed(), pswd = pswd.trimmed();

    json_req["password"] = pswd;
    json_req["username"] = login;

    QJsonDocument doc(json_req);
    QByteArray data = doc.toJson();

    QString url_str = get_host() + "/api/v1/auth/login";
    QUrl log_url = QUrl(url_str);
    request->setUrl(log_url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager->post(*request, data);
}



void LogInWindow::on_to_sign_up_clicked()
{
    ui->log_in_widg->hide();
    ui->sign_up_widg->show();
}


void LogInWindow::on_sign_up_button_clicked()
{
    QString login = ui->login_signup_line->text();
    QString pswd = ui->pswd_signup_line->text();
    QString pswd_conf = ui->pswd_conf_signup_line->text();

    login = login.trimmed(), pswd = pswd.trimmed(), pswd_conf = pswd_conf.trimmed();
    if (pswd == pswd_conf) {
        QJsonObject json_req;
        json_req["email"] = login;
        json_req["password"] = pswd;
        json_req["confirm_password"] = pswd_conf;

        QJsonDocument doc(json_req);
        QByteArray data = doc.toJson();

        QString url_str = get_host() + "/api/v1/auth/signUp";
        QUrl log_url = QUrl(url_str);
        request->setUrl(log_url);
        request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        manager->post(*request, data);
    } else {
        ui->signUpErrorLine->setText("Confirmation Error");
    }
}


void LogInWindow::on_to_log_in_clicked()
{
    ui->log_in_widg->show();
    ui->sign_up_widg->hide();
}

