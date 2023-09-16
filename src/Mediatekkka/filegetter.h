#ifndef FILEGETTER_H
#define FILEGETTER_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "utility.h"

class fileGetter
{
public:
    QNetworkReply* reply;

    fileGetter();
    ~fileGetter();
    void getMiniature(QString source);
    QNetworkAccessManager* get_manager();

private:
    QNetworkAccessManager *manager;
    QString host;
    QNetworkRequest request;
};

#endif // FILEGETTER_H
