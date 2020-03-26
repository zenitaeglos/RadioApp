#include "controlsguiheader.h"
#include <QDebug>

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    guiHeaderLayout(new QHBoxLayout),
    searchStationsButton(new RadioAppButton(DataSource::resource(DataSource::Search), "Search", this)),
    searchLineEdit(new QLineEdit(this)),
    volumeSlider(new QSlider(Qt::Horizontal, this)),
    completer(new QCompleter(DataSource::completionList(), this)),
    networkDataManager(new NetworkDataManager(this))
{
    networkDataManager->setDelegate(this);
    setupUI();

    searchLineEdit->setCompleter(completer);

    // connections
    connect(searchStationsButton, &QPushButton::clicked, this, &ControlsGuiHeader::fetchRadioStations);

}

RadioAppButton* ControlsGuiHeader::getSearchStationsButton() const
{
    return searchStationsButton;
}

QLineEdit *ControlsGuiHeader::getSearchLineEdit() const
{
    return searchLineEdit;
}

QSlider *ControlsGuiHeader::getVolumeSlider() const
{
    return volumeSlider;
}

void ControlsGuiHeader::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        searchStationsButton->clicked();
    }
}

void ControlsGuiHeader::didReceiveData(QByteArray byteArrayReceived)
{
    emit dataRecevied(byteArrayReceived);
}

void ControlsGuiHeader::didNotReceiveData(QString error)
{
    // if no data is given back by the server, show alert to the user

    QMessageBox errorMessageBox;
    errorMessageBox.setWindowTitle("Search failed");
    errorMessageBox.setText(error);
    errorMessageBox.exec();
    return;
}

void ControlsGuiHeader::fetchRadioStations(bool checked)
{
    Q_UNUSED(checked);
    QString lineEditText = searchLineEdit->text();
    int filterIndex = lineEditText.indexOf(":");
    QString baseUrl;

    // check for filtering options
    if (filterIndex > 0) {
        QString filterName(lineEditText.right(lineEditText.length() - filterIndex - 1));
        QString filterOption = lineEditText.left(filterIndex);
        baseUrl = DataSource::radioFiltered(DataSource::typeOfFilter(filterOption));
        networkDataManager->fetchData(baseUrl + filterName);
        //fetch(str + filterName);
    }
    else {
        baseUrl = DataSource::radioFiltered();
        networkDataManager->fetchData(baseUrl + lineEditText);
    }
}

void ControlsGuiHeader::setupUI()
{
    searchLineEdit->setPlaceholderText(tr("Search Radio"));
    searchLineEdit->setToolTip(tr("Search radio station"));

    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    volumeSlider->setMaximumWidth(80);
    volumeSlider->setToolTip(tr("Change volume"));

    searchStationsButton->setMaximumHeight(searchLineEdit->height());

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

    guiHeaderLayout->addWidget(volumeSlider);
    guiHeaderLayout->setMargin(0);
    guiHeaderLayout->setSpacing(2);

    setLayout(guiHeaderLayout);
}
