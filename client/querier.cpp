#include "querier.h"
#include "utility.h"

Querier::Querier()
{
    host = get_host();
    manager = new QNetworkAccessManager;
}

Querier::~Querier() {
    delete manager;
}

void Querier::getMiniature(QString source) {
    //url must be API for getting one exact miniature
    QUrl url = QUrl(host + source);
    request.setUrl(url);
    reply = manager->get(request);
}

QNetworkAccessManager* Querier::get_manager() {
    return manager;
}

void Querier::load_files(QStringList file_names) {
    QUrl url = QUrl(host + ""); //api for loading
    QHttpPart imagePart;
    QFile *f = new QFile;
    for (auto name : file_names){
        QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\""));
        f->setFileName(name);
        f->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(f);
        f->setParent(multi_part);

        multi_part->append(imagePart);

        request.setUrl(url);
        reply = manager->post(request, multi_part);
        multi_part->setParent(reply);
        delete reply;
    }
}

/*
    TODO:
        1) Проверить, сработает такая тема вообще или неи
        2) Проверить файл на открытие
        3) Если reply нигде не нужен (хотя нужен, скорее всего - как минимум reply.code), то удалить, а вместе с ним закрыть f и multi_part
*/
