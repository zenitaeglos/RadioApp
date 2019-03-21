#include "mainwindow.h"

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
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchStation);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::resultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::playRadioStation);
    connect(controlsGuiBottom->getStopButton(), &QPushButton::clicked, this, &MainWindow::stop);
    connect(this, &MainWindow::playClicked, this, &MainWindow::play);
    connect(radioResultsTableView, &QTableView::doubleClicked, this, &MainWindow::playRadioStation);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::printMediaMetaInfo);

    //TODO: Refactor everything. FillResultsFromReuqest, play. It needs to stop, double click options.
}

void MainWindow::searchStation()
{
    downloadType = JsonFetch;
    QString lineEditText(controlsGuiHeader->getSearchLineEdit()->text());
    QString str("http://www.radio-browser.info/webservice/json/stations/byname/");
    fetch(str + lineEditText);
}

void MainWindow::fetch(QString stringToSearch)
{   
    manager->get(QNetworkRequest(QUrl(stringToSearch)));
}

void MainWindow::resultsFromRequest(QNetworkReply *networkReply)
{
    QByteArray data = networkReply->readAll();
    switch (downloadType) {
        case JsonFetch: {
            fillDataModel(data);
            break;
        }
        case PlayListFetch:{
            setPlaylistToPlay(data);
            break;
        }
    }
}

void MainWindow::playRadioStation()
{
    playList->clear();
    radioResultsTableView->currentIndex();

    QModelIndex radioSelectedIndex = radioResultsTableView->selectionModel()->currentIndex();
    if (radioSelectedIndex.row() >= 0) {
        RequestsData* data = requestsModel->dataInstance(radioSelectedIndex.row());
        QFileInfo info = data->getValue(RequestsData::Url);

        if (!info.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive)) {
            downloadType = PlayListFetch;
            fetch(QString(data->getValue(RequestsData::Url)));
        }
        else {
            playList->addMedia(QUrl(data->getValue(RequestsData::Url)));
            emit playClicked();
        }
    }
}

void MainWindow::printMediaMetaInfo() {
    qDebug() << player->metaData(QMediaMetaData::Title).toString();
}

void MainWindow::play()
{
    player->setPlaylist(playList);
    player->setVolume(50);
    player->play();
}

void MainWindow::stop()
{
    player->stop();
}

void MainWindow::fillDataModel(QByteArray data)
{
    //obtain the data to fill the list of json objects
    //and send it to the model
    QJsonDocument document = QJsonDocument::fromJson(data);

    QJsonArray array = document.array();
    QList<RequestsData*> dataForModel;

    //add link to access the webpage

    for (int i = 0; i < array.size(); i++) {
        RequestsData* data = new RequestsData(array.at(i).toObject());
        dataForModel.append(data);
    }
    requestsModel->setRequestedData(dataForModel);
}

void MainWindow::setPlaylistToPlay(QByteArray data)
{
    //get the bitrate for the playlist and emit
    //signal to play it
    QList<QByteArray> listByte = data.split('\n');
    for (QByteArray byteArray : listByte) {
        playList->addMedia(QUrl(byteArray));
    }
    emit playClicked();
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
