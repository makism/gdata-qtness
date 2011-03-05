#include <QtNetwork>

#include "clientlogin.h"


ClientLogin::ClientLogin(QObject *parent)
    : QObject(parent),
      m_manager(0),
      m_reply(0)
{
    init();
}

ClientLogin::ClientLogin(const QString &username, const QString &password, const DocumentsList &service, QObject *parent)
    : QObject(parent),
      m_manager(0),
      m_reply(0),
      m_username(username),
      m_password(password)
{
    m_service = service.getServiceName();

    init();
}

ClientLogin::~ClientLogin(void)
{
    m_reply->deleteLater();
    m_manager->deleteLater();

    m_reply = 0;
    m_manager = 0;
}

void ClientLogin::init(void)
{
    QUrl url("https://www.google.com/accounts/ClientLogin");

    m_request.setUrl(url);
    m_request.setRawHeader("Accept-Encoding", "application/x-www-form-urlencoded");

    m_manager = new QNetworkAccessManager();

    m_authData = "accountType=HOSTED_OR_GOOGLE&Email=%1&Passwd=%2&service=%3&v=2&source=makism-gdata-qtness-0.1-sample-documentslist";
}

void ClientLogin::authenticate(void)
{
    if(m_username.isEmpty() || m_password.isEmpty())
    {
        emit authenticationIncompleteRequest(MissingCredentials);
        return;
    }

    if(m_service.isEmpty()){
        emit authenticationIncompleteRequest(NoServiceSpecified);
        return;
    }

    QString request = m_authData.arg(m_username).arg(m_password).arg(m_service);

    m_reply = m_manager->post(m_request, request.toUtf8());

    connect(m_reply, SIGNAL(readyRead()),
            this, SLOT(readAuthData()));
    connect(m_reply, SIGNAL(finished()),
            this, SLOT(readAuthDataFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(readAuthDataError(QNetworkReply::NetworkError)));
}

QString ClientLogin::getAuthCookie(void)
{
    return m_responseData["Auth"];
}

void ClientLogin::readAuthData(void)
{
    QByteArray rawData = m_reply->readAll();
    QString response(rawData);

    QStringList responseLines = response.split('\n');

    foreach(QString line, responseLines)
    {
        if (line!="") {
            QStringList explodeStr = line.split('=');
            m_responseData.insert(explodeStr.at(0), explodeStr.at(1));
        }
    }

    m_authSucceded = !m_responseData.contains("Error");
    if (!m_authSucceded) {
        QString error = m_responseData.value("Error");

        emit authenticationError(error);
    }
}

void ClientLogin::readAuthDataFinished(void)
{
    m_reply->deleteLater();
    m_reply = 0;

    emit authenticationSuccess();
}

void ClientLogin::readAuthDataError(QNetworkReply::NetworkError err)
{
    m_reply->deleteLater();
    m_reply = 0;

    emit authenticationNetworkError(err);
}
