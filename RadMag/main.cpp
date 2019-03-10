#include <QGuiApplication>
#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    /*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
    */

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
