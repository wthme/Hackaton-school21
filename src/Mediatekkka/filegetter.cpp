#include "filegetter.h"

fileGetter::fileGetter()
{
    host = get_host();
    manager = new QNetworkAccessManager;
}

fileGetter::~fileGetter() {
    delete manager;
}

void fileGetter::getMiniature(QString source) {
    //url must be API for getting one exact miniature
    QUrl url = QUrl(host + source);
    request.setUrl(url);
    reply = manager->get(request);
}

QNetworkAccessManager* fileGetter::get_manager() {
    return manager;
}
