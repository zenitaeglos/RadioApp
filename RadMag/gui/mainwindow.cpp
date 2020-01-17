#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    radiostationsModel(new RadioStationsModel(this)),
    manager(new QNetworkAccessManager(this)),
    radioStationDelegate(new RadioStationDelegate(this)),
    favouritesTableView(new QTableView),
    tablesHLayout(new QHBoxLayout),
    favouritesModel(new FavouritesModel(this)),
    radioPlayer(new RadioPlayer()),
    addDeleteButtonsHorizontalLayout(new QHBoxLayout),
    resultsAndBottomLayout(new QVBoxLayout),
    favouritesDelegate(new FavouritesDelegate(this)),
    favouritesJsonFile(new FavouritesJson)
{
    //function to create the UI
    setupUI();

    //set the model values and set the model of the table view
    radiostationsModel->setRequestedData(QList<RadioStation*>());
    radioResultsTableView->setModel(radiostationsModel);

    //set the model for the playlists that are saved. This has to be used
    //with json file to save the data
    favouritesModel->setFavourites(QList<RadioStation*>());
    favouritesTableView->setModel(favouritesModel);

    radioPlayer->setVolume(controlsGuiHeader->getVolumeSlider()->value());

    //load json file with favourites;
    QList<RadioStation*> dataFromJsonFile = favouritesJsonFile->jsonLoadElements();
    if (dataFromJsonFile.size() > 0) {
        favouritesModel->setFavourites(dataFromJsonFile);
    }

    //connects
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchStation);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::resultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::playFromRequest);
    connect(this, &MainWindow::playClicked, this, &MainWindow::play);

    connect(radioPlayer, &RadioPlayer::mediaStatusChanged, this, &MainWindow::updateMediaInfo);

    connect(controlsGuiHeader->getVolumeSlider(), &QSlider::valueChanged, this, &MainWindow::setVolume);


    connect(favouritesTableView, &QTableView::doubleClicked, this, &MainWindow::playFromFavourites);

    connect(radioStationDelegate, &RadioStationDelegate::starClicked, this, &MainWindow::updateRadioStationFavorite);

    connect(favouritesDelegate, &FavouritesDelegate::removeClicked, this, &MainWindow::removeRadioFromFavourite);
    connect(favouritesDelegate, &FavouritesDelegate::playFavoriteClicked, this, &MainWindow::playFromFavourites);
    connect(favouritesDelegate, &FavouritesDelegate::currentIndexChanged, this, &MainWindow::currentIndexFavorite);

    connect(radioStationDelegate, &RadioStationDelegate::currentIndexChanged, this, &MainWindow::currentIndexRadioStation);
    connect(radioStationDelegate, &RadioStationDelegate::doubleClickPressed, this, &MainWindow::playFromRequest);
}

MainWindow::~MainWindow()
{
    delete radioPlayer;
    delete favouritesJsonFile;
}

void MainWindow::searchStation()
{
    downloadType = JsonFetch;
    QString lineEditText(controlsGuiHeader->getSearchLineEdit()->text());
    int filterIndex = lineEditText.indexOf(":");
    QString str;

    // check for filtering options
    if (filterIndex > 0) {
        QString filterName(lineEditText.right(lineEditText.length() - filterIndex - 1));
        QString filterOption = lineEditText.left(filterIndex);
        str = DataSource::radioFiltered(DataSource::typeOfFilter(filterOption));
        fetch(str + filterName);
    }
    else {
        str = DataSource::radioFiltered();
        fetch(str + lineEditText);
    }
}

void MainWindow::fetch(QString stringToSearch)
{   
    manager->get(QNetworkRequest(QUrl(stringToSearch)));
}

void MainWindow::resultsFromRequest(QNetworkReply *networkReply)
{
    QByteArray data = networkReply->readAll();


    // if no data is given back by the server, show alert to the user
    if (data.isEmpty()) {
        QMessageBox box;
        box.setText("You either have no Internet connection or the server is currently down");
        box.exec();
        return;
    }
    else if (data == "[]") {
        QMessageBox box;
        box.setText("There is no results for that search");
        box.exec();
        return;
    }
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

void MainWindow::playRadioStation(RadioStation *data)
{
    radioPlayer->clearPlayList();

    QFileInfo info = data->getValue(RadioStation::Url);

    if (!info.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive)) {
        downloadType = PlayListFetch;
        fetch(QString(data->getValue(RadioStation::Url)));
    }
    else {
        radioPlayer->addMedia(QUrl(data->getValue(RadioStation::Url)));
        emit playClicked();
    }
}


void MainWindow::updateMediaInfo(QString title) {
    controlsGuiBottom->setRadioName(title);
}

void MainWindow::play()
{
    //set play and stop buttons enable to press and disable
    controlsGuiBottom->getPlayButton()->setIcon(QIcon(DataSource::resource(DataSource::Stop)));
    controlsGuiBottom->getPlayButton()->setToolTip("Stop");
    radioPlayer->play();

}

void MainWindow::stop()
{
    //set play and stop buttons enable to press and disable
    controlsGuiBottom->getPlayButton()->setIcon(QIcon(DataSource::resource(DataSource::Play)));
    controlsGuiBottom->getPlayButton()->setToolTip("Play");
    radioPlayer->stop();
    controlsGuiBottom->setRadioName("");
}

void MainWindow::setVolume(int value)
{
    radioPlayer->setVolume(value);
}

void MainWindow::removeRadioFromFavourite()
{
    QModelIndex index = favouritesTableView->currentIndex();
    if (index.row() >= 0) {
        RadioStation* radio = favouritesModel->dataInstance(index.row());
        int position = CompareModels::findRadioStationInModel(radio, radiostationsModel);
        if (position > -1) {
            RadioStation* radioStarToRemove = radiostationsModel->dataInstance(position);
            QJsonObject jsonObject = radioStarToRemove->getObject();
            radiostationsModel->updateModelFavorite(position, !jsonObject[RadioStation::getType(RadioStation::IsFavorite)].toBool());
        }
        favouritesModel->removeFavourite(index.row());
        favouritesJsonFile->removeJsonObjectFromFile(index.row());
    }
}

void MainWindow::playFromRequest()
{
    if (radioPlayer->player()->state() == QMediaPlayer::StoppedState) {
        QModelIndex radioSelectedIndex = radioResultsTableView->selectionModel()->currentIndex();
        if (radioSelectedIndex.row() >= 0) {
            RadioStation* data = radiostationsModel->dataInstance(radioSelectedIndex.row());
            playRadioStation(data);
            controlsGuiBottom->setRadioName("playing " + data->getObject()[RadioStation::getType(RadioStation::Name)].toString());
        }
    }
    else if (radioPlayer->player()->state() == QMediaPlayer::PlayingState)
        stop();

}

void MainWindow::playFromFavourites()
{
    QModelIndex radioSelectedIndex = favouritesTableView->selectionModel()->currentIndex();
    if (radioSelectedIndex.row() >= 0) {
        RadioStation* data = favouritesModel->dataInstance(radioSelectedIndex.row());
        playRadioStation(data);
        controlsGuiBottom->setRadioName("playing " + data->getObject()[RadioStation::getType(RadioStation::Name)].toString());
    }
}

void MainWindow::updateRadioStationFavorite(int position, bool favorite)
{
    radiostationsModel->updateModelFavorite(position, favorite);
    RadioStation* radio = radiostationsModel->dataInstance(position);
    if (favorite) {
        if (CompareModels::findRadioStationInModel(radio, favouritesModel) == -1) {
            favouritesModel->addFavourite(radiostationsModel->rowCount(QModelIndex()), radio);
            favouritesJsonFile->addJsonObjectToFile(radio->getObject(), 0);
        }

    }
    else {
        int radioPositionToDelete = CompareModels::removeRadioFromModel(radio, favouritesModel);
        favouritesJsonFile->removeJsonObjectFromFile(radioPositionToDelete);
    }
}

void MainWindow::removeRadioStationFromFavorite(int position)
{
    favouritesModel->removeFavourite(position);
    favouritesJsonFile->removeJsonObjectFromFile(position);
}

void MainWindow::currentIndexFavorite(int index)
{
    QModelIndex favoriteIndex = favouritesModel->index(index, 0);
    favouritesTableView->setCurrentIndex(favoriteIndex);
}

void MainWindow::currentIndexRadioStation(int index)
{
    QModelIndex radioStationIndex = radiostationsModel->index(index, 0);
    radioResultsTableView->setCurrentIndex(radioStationIndex);
}

void MainWindow::fillDataModel(QByteArray data)
{
    //obtain the data to fill the list of json objects
    //and send it to the model
    QJsonDocument document = QJsonDocument::fromJson(data);

    QJsonArray array = document.array();
    QList<RadioStation*> dataForModel;

    //add link to access the webpage

    //check if radio station is already added into the favorites
    //change type of star depending on if it is true or false
    for (int i = 0; i < array.size(); i++) {
        RadioStation* radio = new RadioStation(array.at(i).toObject());
        for (int i = 0; i < favouritesModel->rowCount(QModelIndex()); i++) {
            RadioStation* favoriteRadio = favouritesModel->dataInstance(i);
            if (radio->getValue(RadioStation::StationuuID) == favoriteRadio->getValue(RadioStation::StationuuID)) {
                radio->setFavorite(true);
                break;
            }
        }
        dataForModel.append(radio);
    }
    radiostationsModel->setRequestedData(dataForModel);
}

void MainWindow::setPlaylistToPlay(QByteArray data)
{
    radioPlayer->addMedia(data);
    emit playClicked();
}

void MainWindow::setupUI()
{
    radioResultsTableView->setItemDelegate(radioStationDelegate);

    radioResultsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    radioResultsTableView->horizontalHeader()->setStretchLastSection(true);

    resultsAndBottomLayout->addWidget(radioResultsTableView);
    resultsAndBottomLayout->addWidget(controlsGuiBottom);


    favouritesTableView->setMaximumWidth(this->width() / 3);
    favouritesTableView->horizontalHeader()->setStretchLastSection(true);
    favouritesTableView->setItemDelegate(favouritesDelegate);

    tablesHLayout->addWidget(favouritesTableView);
    tablesHLayout->addLayout(resultsAndBottomLayout);

    mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addLayout(tablesHLayout);

    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(600, 600);
}
