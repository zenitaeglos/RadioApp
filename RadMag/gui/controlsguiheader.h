#ifndef CONTROLSGUIHEADER_H
#define CONTROLSGUIHEADER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

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

private:
    QHBoxLayout* guiHeaderLayout;
    QPushButton* searchStationsButton;
    QLineEdit* searchLineEdit;
};

#endif // CONTROLSGUIHEADER_H
