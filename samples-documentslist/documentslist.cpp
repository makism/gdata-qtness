#include "documentslist.h"

DocumentsList::DocumentsList(QObject *parent)
    : QObject(parent)
{
    m_serviceName = "writely";
}

void DocumentsList::setAuthToken(const QString &auth)
{
    m_auth = auth;
}

QString DocumentsList::getServiceName(void) const
{
	return m_serviceName;
}

void DocumentsList::listDocuments(void)
{
    QUrl url("https://docs.google.com/feeds/documents/private/full");

    m_request.setUrl(url);
    m_request.setRawHeader("Authorization", QString("GoogleLogin auth=" + m_auth).toUtf8());
    m_request.setRawHeader("GData-Version", "2.0");

    m_manager = new QNetworkAccessManager();
    m_reply = m_manager->get(m_request);

    connect(m_reply, SIGNAL(readyRead()),
           this, SLOT(readData()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(readAuthDataError(QNetworkReply::NetworkError)));
}

void DocumentsList::readData(void)
{
    QByteArray rawData = m_reply->readAll();
    QString response(rawData);

    qDebug() << response;
}

void DocumentsList::readAuthDataError(QNetworkReply::NetworkError err)
{
   qDebug() << err;

    m_reply->deleteLater();
    m_reply = 0;
}
