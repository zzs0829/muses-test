#include "usbmusictester.h"
#include <QPluginLoader>
#include <QDebug>
#include <Multimedia/multimediaserviceproviderplugin.h>

UsbMusicTester::UsbMusicTester(QObject *parent) : QObject(parent),
    m_session(0)
{
    QPluginLoader loader("medialist/libnativeplaylist");
    if (loader.load()) {
        QObject *obj = loader.instance();
        if(obj) {
            MultimediaServiceProviderInterface *plugin = qobject_cast<MultimediaServiceProviderInterface*>(obj);
            if(plugin) {
                MultimediaService *service = plugin->create(MEDIASERVICE_PLAYLIST);
                if(service) {
                    m_session = qobject_cast<MediaPlaylistSession*>(
                                service->requestSession("USB_MUSIC"));
                    connect(m_session, SIGNAL(mediaChanged(int,int)), SLOT(onMediaChanged(int,int)));
                }
            }
        }
    }
}

void UsbMusicTester::onMediaChanged(int start, int end)
{
    qDebug() << "Finded:" << start << end << m_session->mediaCount();
    for(int i=start;i<=end;++i) {
         qDebug() << m_session->media(i).url();
    }
}
