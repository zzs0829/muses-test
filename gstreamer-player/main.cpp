#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QTime>
#include <QDebug>

#include <Multimedia/multimediaplayer.h>
#include <Multimedia/multimediaserviceproviderplugin.h>
#include <Multimedia/mediaplayercontroller.h>
#include <Multimedia/mediaplaylistcontroller.h>

#include "id3tag.h"

HS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QTime time;
    time.start();
    qDebug() << "Read to app :" << time.elapsed();
    qDebug() << "Start to app :" << time.elapsed();


    qDebug() << MultimediaPlayer::PlayingState;
    qDebug() << MultimediaPlayer::StoppedState;
    qDebug() << MultimediaPlayer::PausedState;
    qDebug() << MultimediaPlayer::NoError;

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
#else
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
                MultimediaService *service = plugin->create("USB_MUSIC");
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
#endif

    QQmlApplicationEngine engine;
    qmlRegisterType<ID3Tag>("MusesTest", 1, 0, "ID3Tag");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
