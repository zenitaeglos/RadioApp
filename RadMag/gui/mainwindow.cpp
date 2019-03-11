#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    requestsModel(new requestsmodel(this)),
    manager(new QNetworkAccessManager(this))
{
    setupUI();

    requestsModel->setRequestedData(QList<RequestsData*>());
    radioResultsTableView->setModel(requestsModel);


    connect(controlsGuiHeader->searchStationsButton, &QPushButton::clicked, this, &MainWindow::searchClicked);
    connect(this, &MainWindow::searchClicked, this, &MainWindow::fetch);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::fillResultsFromRequest);
}

void MainWindow::fetch()
{
    QString lineEditText(controlsGuiHeader->searchLineEdit->text());
    QString str("http://www.radio-browser.info/webservice/json/stations/byname/");
    manager->get(QNetworkRequest(QUrl(str + lineEditText)));

}

void MainWindow::fillResultsFromRequest(QNetworkReply *networkReply)
{
    QByteArray data = networkReply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);

    QJsonArray array = document.array();
    QList<RequestsData*> dataForModel;
    for (int i = 0; i < array.size(); i++) {
        RequestsData* data = new RequestsData;
        data->setName(array.at(i)["name"].toString());
        dataForModel.append(data);
    }
    requestsModel->setRequestedData(dataForModel);
}

void MainWindow::setupUI()
{
    mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addWidget(radioResultsTableView);
    mainLayout->addWidget(controlsGuiBottom);

    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(400, 600);
}
