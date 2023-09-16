#include "filegetter.h"

fileGetter::fileGetter()
{
    QFile f("/home/sidharta/projects/hackatone/Hackaton-school21/src/Mediatekkka/.config"); // надо редактировать путь
    f.open(QFile::ReadOnly);
    if (f.isOpen()){
        host = QString(f.readLine());
        host = host.trimmed();
        f.close();
    }

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
