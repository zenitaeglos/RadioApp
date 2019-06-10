#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    mainLayout(new QVBoxLayout),
    radioResultsTableView(new QTableView(this)),
    mainWidget(new QWidget(this)),
    controlsGuiBottom(new ControlsGuiBottom(this)),
    controlsGuiHeader(new ControlsGuiHeader(this)),
    radiostationsModel(new RadioStationsModel(this)),
    manager(new QNetworkAccessManager(this)),
    delegate(new RequestDelegate(this)),
    favouritesTableView(new QTableView),
    tablesHLayout(new QHBoxLayout),
    favouritesModel(new FavouritesModel(this)),
    radioPlayer(new RadioPlayer()),
    //addToFavouritesButton(new QPushButton(this)),
    //removeFromFavouritesButton(new QPushButton(this)),
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
    controlsGuiBottom->getStopButton()->setDisabled(true);

    //load json file with favourites;
    QList<RadioStation*> dataFromJsonFile = favouritesJsonFile->jsonLoadElements();
    if (dataFromJsonFile.size() > 0) {
        favouritesModel->setFavourites(dataFromJsonFile);
    }

    //connects
    connect(controlsGuiHeader->getSearchStationsButton(), &QPushButton::clicked, this, &MainWindow::searchStation);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::resultsFromRequest);
    connect(controlsGuiBottom->getPlayButton(), &QPushButton::clicked, this, &MainWindow::playFromRequest);
    connect(controlsGuiBottom->getStopButton(), &QPushButton::clicked, this, &MainWindow::stop);
    connect(this, &MainWindow::playClicked, this, &MainWindow::play);
    connect(radioResultsTableView, &QTableView::doubleClicked, this, &MainWindow::playFromRequest);

    connect(radioPlayer, &RadioPlayer::mediaStatusChanged, this, &MainWindow::updateMediaInfo);

    connect(controlsGuiHeader->getVolumeSlider(), &QSlider::valueChanged, this, &MainWindow::setVolume);

    //connect(addToFavouritesButton, &QPushButton::clicked, this, &MainWindow::addRadioToFavourite);
    //connect(removeFromFavouritesButton, &QPushButton::clicked, this, &MainWindow::removeRadioFromFavourite);
    connect(favouritesTableView, &QTableView::doubleClicked, this, &MainWindow::playFromFavourites);
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
    controlsGuiBottom->getPlayButton()->setDisabled(true);
    controlsGuiBottom->getStopButton()->setDisabled(false);
    radioPlayer->play();
}

void MainWindow::stop()
{
    //set play and stop buttons enable to press and disable
    controlsGuiBottom->getPlayButton()->setDisabled(false);
    controlsGuiBottom->getStopButton()->setDisabled(true);
    radioPlayer->stop();
    controlsGuiBottom->setRadioName("");
}

void MainWindow::setVolume(int value)
{
    radioPlayer->setVolume(value);
}

void MainWindow::addRadioToFavourite()
{
    QModelIndex indexRadio = radioResultsTableView->currentIndex();
    if (indexRadio.row() >= 0) {
        QModelIndex indexFavourite = favouritesTableView->currentIndex();
        if (indexFavourite.row() >= 0) {
            favouritesModel->addFavourite(indexFavourite.row() + 1, radiostationsModel->dataInstance(indexRadio.row()));
        }
        else {
            favouritesModel->addFavourite(favouritesModel->rowCount(QModelIndex()), radiostationsModel->dataInstance(indexRadio.row()));
        }
        favouritesJsonFile->addJsonObjectToFile(radiostationsModel->dataInstance(indexRadio.row())->getObject(), 0);
    }
}

void MainWindow::removeRadioFromFavourite()
{
    QModelIndex index = favouritesTableView->currentIndex();
    if (index.row() >= 0) {
        favouritesModel->removeFavourite(index.row());
        favouritesJsonFile->removeJsonObjectFromFile(index.row());
    }
}

void MainWindow::playFromRequest()
{
    QModelIndex radioSelectedIndex = radioResultsTableView->selectionModel()->currentIndex();
    if (radioSelectedIndex.row() >= 0) {
        RadioStation* data = radiostationsModel->dataInstance(radioSelectedIndex.row());
        playRadioStation(data);
        controlsGuiBottom->setRadioName("playing " + data->getObject()["name"].toString());
    }

}

void MainWindow::playFromFavourites()
{
    QModelIndex radioSelectedIndex = favouritesTableView->selectionModel()->currentIndex();
    if (radioSelectedIndex.row() >= 0) {
        RadioStation* data = favouritesModel->dataInstance(radioSelectedIndex.row());
        playRadioStation(data);
        qDebug() << data->getObject()["name"].toString();
        controlsGuiBottom->setRadioName("playing " + data->getObject()["name"].toString());
    }
}

void MainWindow::fillDataModel(QByteArray data)
{
    //obtain the data to fill the list of json objects
    //and send it to the model
    QJsonDocument document = QJsonDocument::fromJson(data);

    QJsonArray array = document.array();
    QList<RadioStation*> dataForModel;

    //add link to access the webpage

    for (int i = 0; i < array.size(); i++) {
        RadioStation* data = new RadioStation(array.at(i).toObject());
        dataForModel.append(data);
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
    //TODO set header style

    //radioResultsTableView->setStyleSheet("QHeaderView::section {color: white; background-color: #232326; height: 40px;"
    //                                     "font-size: 20px}");
    radioResultsTableView->setItemDelegate(delegate);

    radioResultsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    radioResultsTableView->horizontalHeader()->setStretchLastSection(true);
    //radioResultsTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //radioResultsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //radioResultsTableView->setColumnWidth(0, 300);
    //radioResultsTableView->setColumnWidth(1, 10);


    //radioResultsTableView->setStyleSheet("background-image: url(://resources/background-cement-concrete-242236-2.jpg)");
    /*
    radioResultsTableView->setStyleSheet("background-color: transparent;"
                                         "QHeaderView::section {background-color: transparent;}"
                                         "QHeaderView {background-color: transparent;}"
                                         "QTableCornerButton::section {background-color: transparent;}");
    */
    //addToFavouritesButton->setText("+");
    //addToFavouritesButton->setToolTip("Add playlist to favourites");

    //removeFromFavouritesButton->setText("-");
    //removeFromFavouritesButton->setToolTip("Remove playlist from favourites");

    //addDeleteButtonsHorizontalLayout->addWidget(addToFavouritesButton);
    //addDeleteButtonsHorizontalLayout->addWidget(removeFromFavouritesButton);

    //favouritesLayout->addLayout(addDeleteButtonsHorizontalLayout);
    //favouritesLayout->addWidget(favouritesTableView);
    //favouritesTableView->setStyleSheet("background-color:transparent");

    resultsAndBottomLayout->addWidget(radioResultsTableView);
    resultsAndBottomLayout->addWidget(controlsGuiBottom);


    favouritesTableView->setMaximumWidth(this->width() / 3);
    favouritesTableView->horizontalHeader()->setStretchLastSection(true);
    favouritesTableView->setItemDelegate(favouritesDelegate);

    tablesHLayout->addWidget(favouritesTableView);
    //tablesHLayout->addWidget(radioResultsTableView);
    tablesHLayout->addLayout(resultsAndBottomLayout);

    mainLayout->addWidget(controlsGuiHeader);
    mainLayout->addLayout(tablesHLayout);
    //mainLayout->addWidget(controlsGuiBottom);

    mainWidget->setLayout(mainLayout);


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(600, 600);
}
