#include "utility.h"

QString get_host() {
    QFile f("Z:\\school_21\\hack_2\\Hackaton-school21-myeshask\\src\\Mediatekkka\\.config"); // надо редактировать путь
    QString host = "";
    f.open(QFile::ReadOnly);
    if (f.isOpen()){
        host = QString(f.readLine());
        host = host.trimmed();
        f.close();
    }

    return host;
}
