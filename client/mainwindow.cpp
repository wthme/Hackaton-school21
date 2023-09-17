#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    login_window = new LogInWindow();

    querier = new Querier;

    // login

    // login done

    //
    ui->uploadButton->setIcon(QIcon(":/img/download_icon.png"));
    ui->uploadButton->setIconSize(ui->uploadButton->size());
    //
    this->aDirList = new QFileInfoList();

    this->model = new QListViewExplorerModel();

    this->currentFolder = QDir(QDir::current());
    this->model->getFolderList(this->currentFolder.absolutePath(), this->aDirList);

    this->ui->listView->setModel(model);

    this->ui->lineEditPath->setText(QDir::currentPath());
    //
    this->ui->iconsListWidget->setViewMode(QListWidget::IconMode);
    this->ui->iconsListWidget->setResizeMode(QListWidget::Adjust);

    this->ui->iconsListWidget->setIconSize(QSize(150, 150));

    QDir::setCurrent("");

    connect(querier->get_manager(), SIGNAL(finished(QNetworkReply *)), this, SLOT(onReply(QNetworkReply *)));

    connect(login_window, SIGNAL(loginSuccess()), this, SLOT(logInConf()));

    //connect(querier->get_manager(), SIGNAL(finished(QNetworkReply *)), this, SLOT(first_get(QNetworkReply *)));

    logInConf();

    /*
    centralWidget()->setLayout(new QVBoxLayout());

    QLabel *label = new QLabel("");
    label->setPixmap(QPixmap(currentFolder.absolutePath() + "/bmw.jpg"));
    centralWidget()->layout()->addWidget(label);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete querier;
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (this->aDirList->at(index.row()).isDir()) {
        QString temp = this->aDirList->at(index.row()).absoluteFilePath();
        model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(), this->aDirList);
        this->ui->lineEditPath->setText(temp);
    } else {
        QDesktopServices::openUrl(QUrl(this->aDirList->at(index.row()).absoluteFilePath()));
    }
}

void MainWindow::onReply(QNetworkReply *reply) {
    qDebug() << reply->error();
    QPixmap img;
    img.loadFromData(reply->readAll());
    this->ui->iconsListWidget->addItem(new QListWidgetItem(QIcon(img), "cat"));
}

LogInWindow* MainWindow::getLogInWindow() {
    return login_window;
}


void MainWindow::on_uploadButton_clicked()
{
    QStringList file_names;
    file_names = QFileDialog::getOpenFileNames(this, "Выберете файлы");

    /*
    QHttpMultiPart *multi_part_query = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    for (auto i : file_names) {

    }
    */
}


void MainWindow::logInConf() {
   //login_window->hide();
   //this->show();

   querier->get_file("event1/котик.jpeg");
}

//получает файлы после логина
void MainWindow::first_get(QNetworkReply *reply) {
    qDebug() << reply->error();
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json_obj = doc.object();
    QJsonArray events = json_obj["events"].toArray();
    foreach(const QJsonValue & value, events) {
        event_names.append(value.toString());
    }
}

