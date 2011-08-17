#ifndef AUTHORIZETOKEN_H
#define AUTHORIZETOKEN_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "gdata-qtness-goauth_global.h"
#include "gdata-qtness-goauth_namespace.h"


namespace GDataQtness {
namespace GOAuth {

class GDATAQTNESSGOAUTHSHARED_EXPORT AuthorizeToken : public QObject
{
    Q_OBJECT
public:
    explicit AuthorizeToken(QObject *parent = 0);
    ~AuthorizeToken();

    void setDomain(const QString &_domain);
    void setCountryCode(const QString &_countryCode);
    void forceMobileVersion(bool _mobile);

    void request();

signals:
    void authorizePageReceived(const QString &_page);

public slots:
    void setToken(const QString &_token);
    void readReady();

private:
    QMap<QString, QString> mGoogleParameters;

    QUrl mAuthorizeTokenUrl;
    QNetworkReply *mNetReply;
    QNetworkAccessManager *mNetManager;
    QNetworkRequest mRequest;
};

}
}

#endif // AUTHORIZETOKEN_H
