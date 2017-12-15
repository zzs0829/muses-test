#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QTime>

#include <Multimedia/multimediaplayer.h>
#include <Multimedia/multimediaserviceproviderplugin.h>
#include <Multimedia/mediaplayercontroller.h>

HS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QTime time;
    time.start();
    qDebug() << "Read to app :" << time.elapsed();
    QGuiApplication app(argc, argv);
    qDebug() << "Start to app :" << time.elapsed();


    qDebug() << MultimediaPlayer::PlayingState;
    qDebug() << MultimediaPlayer::StoppedState;
    qDebug() << MultimediaPlayer::PausedState;
    qDebug() << MultimediaPlayer::NoError;

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
                    QNetworkRequest request(QUrl("file:///home/dev/Music/333.mp4"));
                    MediaContent media(request);
                    control->setMedia(media);
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
