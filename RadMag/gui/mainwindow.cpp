#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    requestsModel(new RequestsModel(this)),
    manager(new QNetworkAccessManager(this)),
    delegate(new RequestDelegate(this)),
    favouritesTableView(new QTableView),
    tablesHLayout(new QHBoxLayout),
    favouritesModel(new FavouritesModel(this)),
    radioPlayer(new RadioPlayer())
{
    //function to create the UI
    setupUI();

    //set the model values and set the model of the table view
    requestsModel->setRequestedData(QList<RequestsData*>());
    radioResultsTableView->setModel(requestsModel);

    //set the model for the playlists that are saved. This has to be used
    //with sqlite database to save the data
    favouritesTableView->setModel(favouritesModel);

    radioPlayer->setVolume(controlsGuiHeader->getVolumeSlider()->value());

    //connects
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchStation);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::resultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::playRadioStation);
    connect(controlsGuiBottom->getStopButton(), &QPushButton::clicked, this, &MainWindow::stop);
    connect(this, &MainWindow::playClicked, this, &MainWindow::play);
    connect(radioResultsTableView, &QTableView::doubleClicked, this, &MainWindow::playRadioStation);

    //connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::printMediaMetaInfo);

    connect(controlsGuiHeader->getVolumeSlider(), &QSlider::valueChanged, this, &MainWindow::setVolume);
}

MainWindow::~MainWindow()
{
    delete radioPlayer;
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
    radioPlayer->clearPlayList();
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
            radioPlayer->addMedia(QUrl(data->getValue(RequestsData::Url)));
            emit playClicked();
        }
    }
}
/*
void MainWindow::printMediaMetaInfo() {
    qDebug() << player->metaData(QMediaMetaData::Title).toString();
}
*/
void MainWindow::play()
{
    radioPlayer->play();
}

void MainWindow::stop()
{
    radioPlayer->stop();
}

void MainWindow::setVolume(int value)
{
    radioPlayer->setVolume(value);
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
    radioPlayer->addMedia(data);
    emit playClicked();
}

void MainWindow::setupUI()
{
    //TODO set header style
    radioResultsTableView->horizontalHeader()->setStretchLastSection(true);
    radioResultsTableView->setStyleSheet("QHeaderView::section {color: white; background-color: #232326; height: 40px;"
                                         "font-size: 20px}");
    radioResultsTableView->setItemDelegate(delegate);
    radioResultsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    favouritesTableView->setMaximumWidth(120);
    tablesHLayout->addWidget(favouritesTableView);
    tablesHLayout->addWidget(radioResultsTableView);

    mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addLayout(tablesHLayout);
    mainLayout->addWidget(controlsGuiBottom);

    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(400, 600);
}
