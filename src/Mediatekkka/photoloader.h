#ifndef PHOTOLOADER_H
#define PHOTOLOADER_H

#include <QHttpMultiPart>

class PhotoLoader
{
public:
    PhotoLoader();

    void load_files(QStringList file_names);
};

#endif // PHOTOLOADER_H
