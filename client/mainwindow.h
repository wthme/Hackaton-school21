#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QFileInfoList>
#include <QUrl>
#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug> //test
#include <QVBoxLayout>
#include <QIcon>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "qlistviewexplorermodel.h"
#include "querier.h"
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LogInWindow* getLogInWindow();
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    //
    void onReply(QNetworkReply *reply);
    void first_get(QNetworkReply *reply);

    void logInConf();

    void on_uploadButton_clicked();

private:
    LogInWindow *login_window;

    Ui::MainWindow *ui;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;

    QStringList event_names;
//    QNetworkAccessManager *manager;
    QDir currentFolder;
    //
    Querier *querier;
};
#endif // MAINWINDOW_H
