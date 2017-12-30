#include "id3tag.h"
#include <QDebug>
#include <QImage>
#include <QTemporaryFile>
#include <QTextCodec>

#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <audioproperties.h>

#ifndef FALSE
#define FALSE 0
#endif

using namespace TagLib;

ID3Tag::ID3Tag():
    m_duration(0),
    m_year(0)
{

}

QString fromTagLibString(String str)
{
    if(str.isLatin1()) {
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        return codec->toUnicode(str.toCString());
    }else{
        return QString::fromStdWString(str.toWString());
    }
}

void ID3Tag::setPath(const QString &path)
{
    if(path == m_path)
        return;

    m_path = path;
    emit pathChanged();

    MPEG::File f(path.toUtf8());
    if(ID3v2::Tag *id3v2tag = f.ID3v2Tag()) {
        m_title = fromTagLibString(id3v2tag->title());
        m_artist = fromTagLibString(id3v2tag->artist());
        m_album = fromTagLibString(id3v2tag->album());
        m_year = id3v2tag->year();
        m_duration = f.audioProperties()->length();
        m_albumUrl.clear(); // reset

        ID3v2::FrameList::ConstIterator it = id3v2tag->frameList().begin();
        for(; it != id3v2tag->frameList().end(); it++) {
            const ID3v2::AttachedPictureFrame *frame = dynamic_cast<ID3v2::AttachedPictureFrame *>(*it);
           if(frame) {
               QImage img;
               img.loadFromData((const uchar *)frame->picture().data(), frame->picture().size());
               QTemporaryFile *file = new QTemporaryFile(this);
               file->setFileTemplate(file->fileTemplate() + ".jpg");
               file->open();
               img.save(file, "JPG");
               file->close();
               m_albumUrl = QUrl::fromLocalFile(file->fileName());

           }
        }
        emit tagChanged();
    }

    qDebug() << m_title;
    qDebug() << m_artist;
    qDebug() << m_album;
    qDebug() << m_year;
    qDebug() << m_albumUrl;
    qDebug() << m_duration;

}
