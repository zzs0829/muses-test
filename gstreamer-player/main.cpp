#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QTime>
#include <QDebug>

#include <Multimedia/multimediaplayer.h>
#include <Multimedia/multimediaserviceproviderplugin.h>
#include <Multimedia/mediaplayercontroller.h>
#include <Multimedia/mediaplaylistcontroller.h>
#include <Multimedia/mediaplayer.h>

#include "id3tag.h"

HS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QTime time;
    time.start();

//    QNetworkRequest request(QUrl("http://fdfs.xmcdn.com/group26/M04/E8/AD/wKgJWFkJeqKQOUuUABCc7HPtKOA084.mp3"));
    QNetworkRequest request(QUrl("file:///home/dev/Music/444.mp3"));
//    QNetworkRequest request(QUrl("file:///home/root/777.mp3"));
    MediaContent media(request);
    MediaPlayer *player = new MediaPlayer("USB_MUSIC");

    player->setMedia(media);
    player->setPosition(200000);
    player->play();

#if 0
    qDebug() << "Read to load :" << time.elapsed();
    QPluginLoader loader("mediaservice/libgstmediaplayer");
    qDebug() << "Start to load :" << time.elapsed();
    if (loader.load()) {
        qDebug() << "Plugin load success."<< time.elapsed();
        QObject *obj = loader.instance();
        if(obj) {
            qDebug() << "Plugin instance success." << obj;
            MultimediaServiceProviderInterface *plugin = qobject_cast<MultimediaServiceProviderInterface*>(obj);
            if(plugin) {
                qDebug() << "Get instance success." << time.elapsed();
                MultimediaService *service = plugin->create(MEDIASERVICE_MEDIAPLAYER);
                if(service) {
                    MediaPlayerController * control = service->requestController<MediaPlayerController *>();
                    QNetworkRequest request(QUrl("file:///home/root/777.mp3"));
                    MediaContent media(request);
                    control->setMedia(media);
                    control->play();
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
#endif
    QQmlApplicationEngine engine;
    qmlRegisterType<ID3Tag>("MusesTest", 1, 0, "ID3Tag");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
