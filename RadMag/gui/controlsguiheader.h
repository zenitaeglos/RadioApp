#ifndef CONTROLSGUIHEADER_H
#define CONTROLSGUIHEADER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QSlider>


/*
 *header widget. Mainly for search bar.
 */

class ControlsGuiHeader : public QWidget
{
    Q_OBJECT
public:
    explicit ControlsGuiHeader(QWidget *parent = nullptr);

    QPushButton* getSearchStationsButton() const;
    QLineEdit* getSearchLineEdit() const;
    QSlider* getVolumeSlider() const;

    void keyPressEvent(QKeyEvent* event);

private:
    void setupUI();
    QHBoxLayout* guiHeaderLayout;
    QPushButton* searchStationsButton;
    QLineEdit* searchLineEdit;
    QSlider* volumeSlider;
};

#endif // CONTROLSGUIHEADER_H
