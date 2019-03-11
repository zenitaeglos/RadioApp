#ifndef CONTROLSGUIHEADER_H
#define CONTROLSGUIHEADER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>


class ControlsGuiHeader : public QWidget
{
    Q_OBJECT
public:
    explicit ControlsGuiHeader(QWidget *parent = nullptr);

    QPushButton* searchStationsButton;
    QLineEdit* searchLineEdit;

private:
    QHBoxLayout* guiHeaderLayout;
};

#endif // CONTROLSGUIHEADER_H
