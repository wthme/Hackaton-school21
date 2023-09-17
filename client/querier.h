#ifndef QUERIER_H
#define QUERIER_H


#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QHttpMultiPart>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>

class Querier
{
public:    
    Querier();
    ~Querier();

    QNetworkReply* reply;

    QNetworkAccessManager* get_manager();
    void load_files(QStringList file_names);
    void get_file_names();
    void get_file(QString filename);

private:

    QNetworkAccessManager *manager;
    QString host;
    QNetworkRequest request;
};


#endif // QUERIER_H
