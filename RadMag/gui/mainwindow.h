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
#include "models/requestsmodel.h"
#include "models/requestdelegate.h"
#include "models/favouritesmodel.h"
#include "models/favouritesdelegate.h"
#include "logic/radioplayer.h"

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
    void playRadioStation();
    //void printMediaMetaInfo();
    void play();
    void stop();
    void setVolume(int value);
    void addRadioToFavourite();
    void removeRadioFromFavourite();

private:
    void fillDataModel(QByteArray data);
    void setPlaylistToPlay(QByteArray data);
    void setupUI();
    QVBoxLayout* mainLayout;
    QTableView* radioResultsTableView;
    QWidget* mainWidget;
    ControlsGuiBottom* controlsGuiBottom;
    ControlsGuiHeader* controlsGuiHeader;
    RequestsModel* requestsModel;
    QNetworkAccessManager* manager;
    DownloadType downloadType;
    RequestDelegate* delegate;
    QTableView* favouritesTableView;
    QHBoxLayout* tablesHLayout;
    FavouritesModel* favouritesModel;
    RadioPlayer* radioPlayer;
    QPushButton* addToFavouritesButton;
    QPushButton* removeFromFavouritesButton;
    QHBoxLayout* addDeleteButtonsHorizontalLayout;
    QVBoxLayout* favouritesLayout;

};

#endif // MAINWINDOW_H
