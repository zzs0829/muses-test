#ifndef USBMUSICTESTER_H
#define USBMUSICTESTER_H

#include <QObject>
#include <Multimedia/mediaplaylistsession.h>

class UsbMusicTester : public QObject
{
    Q_OBJECT
public:
    explicit UsbMusicTester(QObject *parent = 0);

signals:

public slots:
    void onMediaChanged(int start, int end);

private:
    MediaPlaylistSession *m_session;
};

#endif // USBMUSICTESTER_H
