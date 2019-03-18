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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "controlsguibottom.h"
#include "controlsguiheader.h"
#include "models/requestsmodel.h"
#include "models/requestdelegate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum DownloadType {
        JsonFetch,
        PlayListFetch,
    };

    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void searchClicked();

private slots:
    void fetch();
    void fillResultsFromRequest(QNetworkReply *networkReply);
    void play();

private:
    void setupUI();
    QVBoxLayout* mainLayout;
    QTableView* radioResultsTableView;
    QWidget* mainWidget;
    ControlsGuiBottom* controlsGuiBottom;
    ControlsGuiHeader* controlsGuiHeader;
    RequestsModel* requestsModel;
    QNetworkAccessManager* manager;
    DownloadType downloadType;
    QMediaPlayer* player;
    QMediaPlaylist* playList;
    RequestDelegate* delegate;

};

#endif // MAINWINDOW_H
