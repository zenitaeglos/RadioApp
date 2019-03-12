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
    //function to create the UI
    setupUI();

    //set the model values and set the model of the table view
    requestsModel->setRequestedData(QList<RequestsData*>());
    radioResultsTableView->setModel(requestsModel);

    //TODO set header style
    radioResultsTableView->horizontalHeader()->setStretchLastSection(true);
    radioResultsTableView->setStyleSheet("QHeaderView::section {color: white; background-color: #232326; height: 40px;"
                                         "font-size: 20px}");


    //connects
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchClicked);
    connect(this, &MainWindow::searchClicked, this, &MainWindow::fetch);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::fillResultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::play);
}

void MainWindow::fetch()
{
    QString lineEditText(controlsGuiHeader->getSearchLineEdit()->text());
    QString str("http://www.radio-browser.info/webservice/json/stations/byname/");
    manager->get(QNetworkRequest(QUrl(str + lineEditText)));

}

void MainWindow::fillResultsFromRequest(QNetworkReply *networkReply)
{
    QByteArray data = networkReply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);

    QJsonArray array = document.array();
    QList<RequestsData*> dataForModel;

    //TODO add favicon to the list.
    //add link to access the webpage

    for (int i = 0; i < array.size(); i++) {
        RequestsData* data = new RequestsData;
        data->setName(array.at(i)["name"].toString());
        dataForModel.append(data);
        data->setUrlName(array.at(i)["url"].toString());
    }
    requestsModel->setRequestedData(dataForModel);
}

void MainWindow::play()
{
    qDebug() << "play the music";
    //TODO call the QMultimedia to be able to play the url
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
