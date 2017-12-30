#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QTime>
#include <QDebug>

#include <Multimedia/multimediaserviceproviderplugin.h>
#include <Multimedia/mediaplaylistcontroller.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QTime time;
    time.start();
    qDebug() << "Read to load :" << time.elapsed();
    QPluginLoader loader("mediaservice/libnativeplaylist");
    qDebug() << "Start to load :" << time.elapsed();
    if (loader.load()) {
        qDebug() << "Plugin load success."<< time.elapsed();
        QObject *obj = loader.instance();
        if(obj) {
            qDebug() << "Plugin instance success." << obj;
            MultimediaServiceProviderInterface *plugin = qobject_cast<MultimediaServiceProviderInterface*>(obj);
            if(plugin) {
                qDebug() << "Get instance success." << time.elapsed();
                MultimediaService *service = plugin->create("USB_VIDEO");
                if(service) {
                    MediaPlaylistController * control = service->requestController<MediaPlaylistController *>();
                    control->currentIndex();
                }
            }else{
                qDebug() << "Get instance failure.";
                return -1;
            }
        }else{
            qDebug() << "Plugin instance failure.";
            return -1;
        }
    }else{
        qDebug() << "Plugin load failure.";
        return -1;
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
