#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtMultimedia>
#include <QMediaMetaData>
#include <QDebug>
#include <QFileInfo>
#include "controlsguibottom.h"
#include "controlsguiheader.h"
#include "models/radiostationsmodel.h"
#include "models/radiostationdelegate.h"
#include "models/favouritesmodel.h"
#include "models/favouritesdelegate.h"
#include "logic/radioplayer.h"
#include "logic/favouritesjson.h"
#include "logic/comparemodels.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum DownloadType {
        JsonFetch,
        PlayListFetch,
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void playClicked();

private slots:
    void searchStation();
    void fetch(QString stringToSearch);
    void resultsFromRequest(QNetworkReply *networkReply);
    void updateMediaInfo(QString title);
    void play();
    void stop();
    void setVolume(int value);
    void addRadioToFavourite();
    void removeRadioFromFavourite();
    void playFromRequest();
    void playFromFavourites();

    // update both tableviews depending on whether the star gives a favorite or not
    void updateRadioStationFavorite(int position, bool favorite);

private:
    void playRadioStation(RadioStation* data);
    void fillDataModel(QByteArray data);
    void setPlaylistToPlay(QByteArray data);
    void setupUI();
    QVBoxLayout* mainLayout;
    QTableView* radioResultsTableView;
    QWidget* mainWidget;
    ControlsGuiBottom* controlsGuiBottom;
    ControlsGuiHeader* controlsGuiHeader;
    RadioStationsModel* radiostationsModel;
    QNetworkAccessManager* manager;
    DownloadType downloadType;
    RadioStationDelegate* radioStationDelegate;
    QTableView* favouritesTableView;
    QHBoxLayout* tablesHLayout;
    FavouritesModel* favouritesModel;
    RadioPlayer* radioPlayer;
    QPushButton* addToFavouritesButton;
    QPushButton* removeFromFavouritesButton;
    QHBoxLayout* addDeleteButtonsHorizontalLayout;
    QVBoxLayout* resultsAndBottomLayout;
    FavouritesDelegate* favouritesDelegate;
    FavouritesJson* favouritesJsonFile;

};

#endif // MAINWINDOW_H
