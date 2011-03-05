#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>


#include "documentslist.h"

class ClientLogin: public QObject
{
    Q_OBJECT

    enum AuthenticationErrorResponse
    {
        BadAuthentication,
        NotVerified,
        TermsNotAgreed,
        CapthaRequired,
        Unknown,
        AccountDeleted,
        AccountDisabled,
        ServiceDisabled,
        ServiceUnavailable
    };

    enum AutheticationIncompleteRequest
    {
        MissingCredentials,
        NoServiceSpecified
    };


public:
    ClientLogin(QObject *parent=0);
    ClientLogin(const QString &username, const QString &password, const DocumentsList &service, QObject *parent = 0);
    virtual ~ClientLogin(void);

    void authenticate(void);

    QString getAuthCookie(void);
    QString getSIDCookie(void);
    QString getLSIDCookie(void);

private slots:
    void readAuthData(void);
    void readAuthDataFinished(void);
    void readAuthDataError(QNetworkReply::NetworkError);

signals:
    void authenticationIncompleteRequest(AutheticationIncompleteRequest);
    void authenticationError(QString);
    void authenticationError(AuthenticationErrorResponse);
    void authenticationSuccess(void);
    void authenticationNetworkError(QNetworkReply::NetworkError);

private:
    void init(void);

    QNetworkRequest m_request;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    QString m_authData;
    bool m_authSucceded;
    QString m_username;
    QString m_password;
    QString m_service;
    QHash<QString, QString> m_responseData;
};

#endif
