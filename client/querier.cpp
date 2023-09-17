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

QNetworkAccessManager* Querier::get_manager() {
    return manager;
}

void Querier::get_file_names() {
    QUrl url = QUrl(host + "/api/v1/content");
    request.setUrl(url);
    manager->get(request);
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

void Querier::get_file(QString filename) {
    QUrl url = QUrl(host + "/api/v1/file");
    QJsonObject json_obj;
    json_obj["path"] = filename;
    QJsonDocument doc(json_obj);
    QByteArray data = doc.toJson();

    request.setUrl(url);
    manager->post(request, data);
}


/*
    TODO:
        1) Проверить, сработает такая тема вообще или неи
        2) Проверить файл на открытие
        3) Если reply нигде не нужен (хотя нужен, скорее всего - как минимум reply.code), то удалить, а вместе с ним закрыть f и multi_part
*/
