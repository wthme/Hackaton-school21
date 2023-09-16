#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->aDirList = new QFileInfoList();

    this->model = new QListViewExplorerModel();

    this->currentFolder = QDir(QDir::current());
    this->model->getFolderList(this->currentFolder.absolutePath(), this->aDirList);

    this->ui->listView->setModel(model);

    this->ui->lineEditPath->setText(QDir::currentPath());
    //
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
