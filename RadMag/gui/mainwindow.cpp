#include "mainwindow.h"
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    requestsModel(new RequestsModel(this)),
    manager(new QNetworkAccessManager(this)),
    player(new QMediaPlayer(this)),
    playList(new QMediaPlaylist(this)),
    delegate(new RequestDelegate(this))
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
    radioResultsTableView->setItemDelegate(delegate);
    radioResultsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //connects
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchClicked);
    connect(this, &MainWindow::searchClicked, this, &MainWindow::fetch);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::fillResultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::play);

    //TODO: Refactor everything. FillResultsFromReuqest, play. It needs to stop, double click options.
}

void MainWindow::fetch()
{
    downloadType = JsonFetch;
    QString lineEditText(controlsGuiHeader->getSearchLineEdit()->text());
    QString str("http://www.radio-browser.info/webservice/json/stations/byname/");
    manager->get(QNetworkRequest(QUrl(str + lineEditText)));

}

void MainWindow::fillResultsFromRequest(QNetworkReply *networkReply)
{
    QByteArray data = networkReply->readAll();
    switch (downloadType) {
    case JsonFetch: {
        QJsonDocument document = QJsonDocument::fromJson(data);

        QJsonArray array = document.array();
        QList<RequestsData*> dataForModel;

        //TODO add favicon to the list.
        //add link to access the webpage

        for (int i = 0; i < array.size(); i++) {
            RequestsData* data = new RequestsData(array.at(i).toObject());
            dataForModel.append(data);
        }
        requestsModel->setRequestedData(dataForModel);
        break;
    }
    case PlayListFetch:{
        QList<QByteArray> listByte = data.split('\n');
        for (QByteArray byteArray : listByte) {
            playList->addMedia(QUrl(byteArray));
        }
        player->setPlaylist(playList);
        player->setVolume(50);
        player->play();

        break;
    }
    }

}

void MainWindow::play()
{
    playList->clear();
    radioResultsTableView->currentIndex();
    if (player->state() == QMediaPlayer::PlayingState) {
        player->stop();
        return;
    }

    QModelIndex radioSelectedIndex = radioResultsTableView->selectionModel()->currentIndex();
    if (radioSelectedIndex.row() >= 0) {
        RequestsData* data = requestsModel->dataInstance(radioSelectedIndex.row());
        QFileInfo info = data->getValue(RequestsData::Url);

        if (!info.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive)) {
            downloadType = PlayListFetch;
            manager->get(QNetworkRequest(QUrl(QString(data->getValue(RequestsData::Url)))));
        }
        else {
            playList->addMedia(QUrl(data->getValue(RequestsData::Url)));
            player->setPlaylist(playList);
            player->setVolume(50);
            player->play();
        }
    }
}

void MainWindow::setupUI()
{
    //TODO add a widget on the side of the tableview to show more information in case an element is
    //selected
    mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addWidget(radioResultsTableView);
    mainLayout->addWidget(controlsGuiBottom);

    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(400, 600);
}
