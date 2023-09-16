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

    // |
    // v вот это юзать для use_event_code (по возможности)
    //ui->widget->hide();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onLogInRequest(QNetworkReply*)));
}

LogInWindow::~LogInWindow()
{
    delete request;
    delete manager;
    delete ui;        
}

void LogInWindow::onLogInRequest(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit loginSuccess();
    } else if (reply->error() == 401) {
        ui->loginErrorLine->setText(QString("Login error: unknown user"));
    }
}


void LogInWindow::on_sign_in_button_clicked()
{
    QString login = ui->login_line->text();
    QString pswd = ui->password_line->text();
    login = login.trimmed(), pswd = pswd.trimmed();
    QByteArray auth = (login + ":" + pswd).toLocal8Bit().toBase64();
    QString data = "Basic" + auth;
    request->setRawHeader("Authorization", data.toLocal8Bit());

    QUrl log_url = get_host() + ""; // api to login
    request->setUrl(log_url);
    manager->get(*request);
}


