#include "qlistviewexplorermodel.h"

QListViewExplorerModel::QListViewExplorerModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void QListViewExplorerModel::getFolderList(QString folderPath, QFileInfoList *dirList)
{
    QDir dir = QDir(folderPath);

    *dirList = dir.entryInfoList(QDir::NoDot | QDir::Dirs | QDir::Files | QDir::Drives, QDir::DirsFirst);
    this->beginResetModel();
    this->aDirList = dirList;
    this->endResetModel();
}


int QListViewExplorerModel::rowCount(const QModelIndex &) const
{
    return this->aDirList->count();
}

QVariant QListViewExplorerModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::DecorationRole: //icon
            {
                if (this->aDirList->at(index.row()).isDir()) {
                    QPixmap icon = QPixmap(":/img/folder.png");
                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                if (this->aDirList->at(index.row()).isFile()) {
                    QString fileExt = this->aDirList->at(index.row()).completeSuffix();
                    if (fileExt == "zip" || fileExt == "7z" || fileExt == "rar") {
                        QPixmap icon = QPixmap(":/img/zip.png");
                        QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                        value = tmp;
                        break;
                    }
                    if (fileExt == "jpg" || fileExt == "png" || fileExt == "bmp") {
                        QPixmap icon = QPixmap(":/img/pic.png");
                        QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                        value = tmp;
                        break;
                    }
                    QPixmap icon = QPixmap(":/img/file.png");
                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

//                if (this->aDirList->at(index.row()).is)

                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            default:
                break;
        }

    return value;
}
