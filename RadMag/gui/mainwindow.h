#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "controlsguibottom.h"
#include "controlsguiheader.h"
#include "models/requestsmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void searchClicked();

private slots:
    void fetch();
    void fillResultsFromRequest(QNetworkReply *networkReply);

private:
    void setupUI();
    QVBoxLayout* mainLayout;
    QTableView* radioResultsTableView;
    QWidget* mainWidget;
    ControlsGuiBottom* controlsGuiBottom;
    ControlsGuiHeader* controlsGuiHeader;
    requestsmodel* requestsModel;
    QNetworkAccessManager* manager;

};

#endif // MAINWINDOW_H
