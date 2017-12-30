#ifndef ID3TAG_H
#define ID3TAG_H

#include <QQuickItem>

class ID3Tag : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString title READ title NOTIFY tagChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY tagChanged)
    Q_PROPERTY(QString album READ album NOTIFY tagChanged)
    Q_PROPERTY(QUrl albumUrl READ albumUrl NOTIFY tagChanged)
public:
    ID3Tag();

    QString path() const { return m_path; }
    void setPath(const QString &path);
    QString title() const { return m_title; }
    QString artist() const { return m_artist; }
    QString album() const { return m_album; }
    QUrl albumUrl() const { return m_albumUrl; }


public slots:

signals:
    void pathChanged();
    void tagChanged();

private:
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    qint64 m_duration;
    uint m_year;
    QUrl m_albumUrl;
};

#endif // ID3TAG_H
