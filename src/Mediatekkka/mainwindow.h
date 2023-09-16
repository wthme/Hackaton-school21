#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QFileInfoList>
#include <QUrl>
#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QVBoxLayout>
#include <QIcon> //
#include <QListWidgetItem>

#include "qlistviewexplorermodel.h"
#include "filegetter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    //
    void onReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;
//    QNetworkAccessManager *manager;
    QDir currentFolder;
    //
    fileGetter *file_getter;
};
#endif // MAINWINDOW_H
