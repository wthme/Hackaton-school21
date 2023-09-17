#ifndef QUERIER_H
#define QUERIER_H


#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QHttpMultiPart>
#include <QVariant>

class Querier
{
public:    
    Querier();
    ~Querier();

    QNetworkReply* reply;

    void getMiniature(QString source);
    QNetworkAccessManager* get_manager();
    void load_files(QStringList file_names);

private:
    QNetworkAccessManager *manager;
    QString host;
    QNetworkRequest request;
};


#endif // QUERIER_H
