#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    radiostationsModel(new RadioStationsModel(this)),
    //manager(new QNetworkAccessManager(this)),
    radioStationDelegate(new RadioStationDelegate(this)),
    favouritesTableView(new QTableView),
    tablesHLayout(new QHBoxLayout),
    favouritesModel(new FavouritesModel(this)),
    radioPlayer(new RadioPlayer()),
    addDeleteButtonsHorizontalLayout(new QHBoxLayout),
    resultsAndBottomLayout(new QVBoxLayout),
    favouritesDelegate(new FavouritesDelegate(this)),
    favouritesJsonFile(new FavouritesJson),
    networkDataManager(new NetworkDataManager(this)),
    favoritesWidget(new QWidget(this))
{
    //set network delegate to this class
    networkDataManager->setDelegate(this);
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

    if (favouritesModel->dataInstance(0) == nullptr) {
        favoritesWidget->setMaximumWidth(0);
    }
    else {
        favoritesWidget->setMaximumWidth(this->width() / 4);
    }


    //connects
    //connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchStation);
    //connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::resultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::playFromRequest);
    connect(this, &MainWindow::playClicked, this, &MainWindow::play);

    connect(radioPlayer, &RadioPlayer::mediaStatusChanged, this, &MainWindow::updateMediaInfo);

    connect(controlsGuiHeader->getVolumeSlider(), &QSlider::valueChanged, this, &MainWindow::setVolume);


    connect(favouritesTableView, &QTableView::doubleClicked, this, &MainWindow::playFromFavourites);

    connect(radioStationDelegate, &RadioStationDelegate::starClickedMouse, this, &MainWindow::updateRadioStationFavorite);

    connect(favouritesDelegate, &FavouritesDelegate::removeClicked, this, &MainWindow::removeRadioFromFavourite);
    connect(favouritesDelegate, &FavouritesDelegate::playFavoriteClicked, this, &MainWindow::playFromFavourites);
    connect(favouritesDelegate, &FavouritesDelegate::currentIndexChanged, this, &MainWindow::currentIndexFavorite);

    connect(radioStationDelegate, &RadioStationDelegate::currentIndexChanged, this, &MainWindow::currentIndexRadioStation);
    connect(radioStationDelegate, &RadioStationDelegate::doubleClickPressed, this, &MainWindow::playFromRequest);


    // network delegate from header now takes the json search. When finish it emits signal with the byte array
    connect(controlsGuiHeader, &ControlsGuiHeader::dataRecevied, this, &MainWindow::setPlaylist);
}

MainWindow::~MainWindow()
{
    delete radioPlayer;
    delete favouritesJsonFile;
}

void MainWindow::didReceiveData(QByteArray byteArrayReceived)
{
    /*
    receive the data to set a playlist
    */
    setPlaylistToPlay(byteArrayReceived);
}

void MainWindow::didNotReceiveData(QString error)
{
    // if no data is given back by the server, show alert to the user
    QMessageBox errorMessageBox;
    errorMessageBox.setWindowTitle("Search failed");
    errorMessageBox.setText(error);
    errorMessageBox.exec();
    return;
}

void MainWindow::setPlaylist(QByteArray playListData)
{
    //obtain the data to fill the list of json objects
    //and send it to the model
    QJsonDocument document = QJsonDocument::fromJson(playListData);

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

void MainWindow::playRadioStation(RadioStation *data)
{
    radioPlayer->clearPlayList();

    QFileInfo info = data->getValue(RadioStation::Url);

    // send favicon to controlsguibottom
    if (!data->getValue(RadioStation::Favicon).isEmpty()) {
        controlsGuiBottom->setIconImage(data->getValue(RadioStation::Favicon));
    }

    if (!info.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive)) {
        networkDataManager->fetchData(data->getValue(RadioStation::Url));
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
    controlsGuiBottom->setIconToPlayButton(QIcon(DataSource::resource(DataSource::Stop)), "Stop");
    radioPlayer->play();

}

void MainWindow::stop()
{
    //set play and stop buttons enable to press and disable
    controlsGuiBottom->setIconToPlayButton(QIcon(DataSource::resource(DataSource::Play)), "Play");
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

    if (favouritesModel->rowCount(QModelIndex()) == 0)
        favoritesWidget->hide();
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

void MainWindow::updateRadioStationFavorite(int position, bool favorite, int yMousePosition)
{
    int numberOfStations = favouritesModel->rowCount(QModelIndex());
    radiostationsModel->updateModelFavorite(position, favorite);
    radioAddToFavorites = radiostationsModel->dataInstance(position);
    if (favorite) {
        if (CompareModels::findRadioStationInModel(radioAddToFavorites, favouritesModel) == -1) {

            starWidget = new QWidget(this);
            starWidget->setGeometry(this->width() - 68, yMousePosition + 40, 42, 42);
            starWidget->setStyleSheet("QWidget { background-image: url(://resources/roundwhitestarfilled.png) }");

            starWidget->show();
            QPropertyAnimation* starAnimation = new QPropertyAnimation(starWidget, "geometry");
            starAnimation->setStartValue(QRect(starWidget->x(), starWidget->y(), starWidget->width(), starWidget->height()));
            starAnimation->setEndValue(QRect(50, starWidget->y(), starWidget->width(), starWidget->height()));
            starAnimation->setDuration(1000);
            starAnimation->setEasingCurve(QEasingCurve::InCirc);
            starAnimation->start();
            connect(starAnimation, &QPropertyAnimation::finished, this, &MainWindow::starAnimationEnd);
        }

    }
    else {
        int radioPositionToDelete = CompareModels::removeRadioFromModel(radioAddToFavorites, favouritesModel);
        favouritesJsonFile->removeJsonObjectFromFile(radioPositionToDelete);
    }

    // Animation to make the favorites tableview hide or show
    // if at least one radio is saved
    if (favoritesWidget->isHidden() || numberOfStations == 0) {
        favoritesWidget->setMaximumWidth(0);
        if (favoritesWidget->isHidden())
            favoritesWidget->setVisible(true);
        QPropertyAnimation* favoritesWidthAnimation = new QPropertyAnimation(favoritesWidget, "minimumWidth");
        favoritesWidthAnimation->setStartValue(0);
        favoritesWidthAnimation->setEndValue(this->width() / 4);

        favoritesWidthAnimation->setDuration(500);
        favoritesWidthAnimation->setEasingCurve(QEasingCurve::OutBack);
        favoritesWidthAnimation->start();
    }
    else if (favouritesModel->rowCount(QModelIndex()) == 0)
        favoritesWidget->hide();
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

void MainWindow::starAnimationEnd()
{
    delete starWidget;
    favouritesModel->addFavourite(radiostationsModel->rowCount(QModelIndex()), radioAddToFavorites);
    favouritesJsonFile->addJsonObjectToFile(radioAddToFavorites->getObject(), 0);
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
    radioResultsTableView->setStyleSheet("QTableView { background-image: url(://resources/main_bg.png) }");
    radioResultsTableView->horizontalHeader()->setStyleSheet("QHeaderView { background-color: transparent; color: black }");
    radioResultsTableView->horizontalHeader()->setSectionsClickable(false);
    radioResultsTableView->verticalHeader()->setVisible(false);
    radioResultsTableView->setShowGrid(false);
    radioResultsTableView->horizontalHeader()->setVisible(false);
    radioResultsTableView->setStyleSheet("QTableView { background-color: transparent }");

    resultsAndBottomLayout->addWidget(controlsGuiHeader);
    resultsAndBottomLayout->addWidget(radioResultsTableView);
    resultsAndBottomLayout->setContentsMargins(0, 0, 0, 0);
    //resultsAndBottomLayout->addWidget(controlsGuiBottom);

    controlsGuiBottom->setMaximumHeight(60);
    controlsGuiBottom->setMinimumHeight(60);
    //controlsGuiBottom->setStyleSheet("QWidget { background-image: url(://resources/player_bg.png) }");
    //controlsGuiBottom->setStyleSheet("QWidget {background-color: blue }");
    controlsGuiHeader->setMaximumHeight(60);
    controlsGuiHeader->setMinimumHeight(60);

    favouritesTableView->setMaximumWidth(this->width() / 3);
    favouritesTableView->horizontalHeader()->setStretchLastSection(true);
    favouritesTableView->setItemDelegate(favouritesDelegate);

    //favouritesTableView->setStyleSheet("QTableView { background-image: url(://resources/sidebar_bg.png) }");
    favouritesTableView->horizontalHeader()->setStyleSheet("QHeaderView { background-color: transparent; color: white }");
    favouritesTableView->horizontalHeader()->setSectionsClickable(false);
    favouritesTableView->setShowGrid(false);
    favouritesTableView->verticalHeader()->setVisible(false);
    favouritesTableView->horizontalHeader()->setVisible(false);




    QVBoxLayout* favLay = new QVBoxLayout;
    QLabel* label = new QLabel("RADMAG", this);
    label->setStyleSheet("QLabel { color: white }");
    label->setAlignment(Qt::AlignCenter);

    QLabel* favoritesLabel = new QLabel("Favorites", this);
    label->setStyleSheet("QLabel { color: white; padding-bottom: 20px; }");

    favLay->addWidget(label);
    favLay->addWidget(favoritesLabel);
    favLay->addWidget(favouritesTableView);
    favoritesWidget->setLayout(favLay);

    favoritesWidget->setStyleSheet("QWidget { background-image: url(://resources/sidebar_bg.png) }");

    tablesHLayout->addWidget(favoritesWidget);

    tablesHLayout->addLayout(resultsAndBottomLayout);

    //mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addLayout(tablesHLayout);
    mainLayout->addWidget(controlsGuiBottom);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("QWidget { background-image: url(://resources/blue_bg.png); border: 0px; }");

    //setWindowFlags(Qt::FramelessWindowHint);

    setStyleSheet("QMainWindow { background-image: url(://resources/blue_bg.png) }");

    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(600, 600);
}
