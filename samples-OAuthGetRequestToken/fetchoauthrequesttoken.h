#ifndef FETCHOAUTHREQUESTTOKEN_H
#define FETCHOAUTHREQUESTTOKEN_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCrypto>
#include <QDebug>
#include <QUrl>


class FetchOAuthRequestToken : public QObject
{
    Q_OBJECT
public:
    explicit FetchOAuthRequestToken(QObject *parent = 0);

signals:

public slots:
    void readyRead(void)
    {
        qDebug() << reply->readAll();
    }

private:
    QNetworkReply *reply;

};

#endif // FETCHOAUTHREQUESTTOKEN_H
