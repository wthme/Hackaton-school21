#include "utility.h"

QString get_host() {
    QFile f(":/config"); // надо редактировать путь
    QString host = "";
    f.open(QFile::ReadOnly);
    if (f.isOpen()){
        host = QString(f.readLine());
        host = host.trimmed();
        f.close();
    }

    return host;
}
