#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QTime>
#include <QDebug>
#include "usbmusictester.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    new UsbMusicTester();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
