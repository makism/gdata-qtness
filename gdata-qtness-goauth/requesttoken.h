#ifndef REQUESTTOKEN_H
#define REQUESTTOKEN_H

#include <QObject>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCrypto>
#include <QUrl>
#include <QMap>


#include "gdata-qtness-goauth_global.h"
#include "gdata-qtness-goauth_namespace.h"


namespace GDataQtness {
namespace GOAuth {

class GDATAQTNESSGOAUTHSHARED_EXPORT RequestToken : public QObject
{
    Q_OBJECT

public:
    explicit RequestToken(QObject *parent = 0);
    ~RequestToken();

    void setScope(GoogleScope::ScopeType &_scope);
    void setScope(QList<GoogleScope::ScopeType> &_scope);
    void setScope(const QString &_scope);
    void clearScope();

    void setCallback(const QString &_callback);

    void setVersion(Version _version);

    void setPreferredMethod(HttpMethod _method);

    void setDisplayName(const QString &_name);

    QString getOAuthToken() const;
    QString getOAuthTokenSecret() const;

    void request();

signals:
    void tokenReceived(const QString &);
    void requestError(ErrorCode errorCode);

private slots:
    void readReady();
    void readError(QNetworkReply::NetworkError error);

private:
    void generateHeaderData();
    void generateSignatureBaseString();
    void generateSignature();

private:
    HttpMethod mRequestMethod;
    QString mRequestMethodStr;

    Version mOAuthVersion;
    QString mOAuthVersionStr;

    QString mHashKey;
    QUrl mRequestTokenUrl;
    QByteArray mSignatureBaseString;
    QString mHeaderData;
    QString mNormalizedHeader;
    QString mSignature;
    QList<QString> mScope;
    QMap<QString, QString> mParameters;
    QMap<QString, QString> mGoogleParameters;
    QMap<QString, QString> mTokensReceived;

    QNetworkReply *mNetReply;
    QNetworkAccessManager *mNetManager;
    QNetworkRequest mRequest;
};

}
}

#endif // REQUESTTOKEN_H
