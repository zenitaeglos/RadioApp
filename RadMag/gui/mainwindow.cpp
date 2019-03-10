#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();


    setCentralWidget(mainWidget);
    //gui geometry
    resize(900, 600);
    setMinimumSize(400, 600);
}

void MainWindow::setupUI()
{
    searchRadioLineEdit = new QLineEdit(this);
    mainLayout = new QVBoxLayout;
    radioResultsTableView = new QTableView(this);

    mainWidget = new QWidget(this);
    controlsGuiBottom = new ControlsGuiBottom(this);


    mainLayout->addWidget(searchRadioLineEdit);
    mainLayout->addWidget(radioResultsTableView);
    mainLayout->addWidget(controlsGuiBottom);

    mainWidget->setLayout(mainLayout);
}
