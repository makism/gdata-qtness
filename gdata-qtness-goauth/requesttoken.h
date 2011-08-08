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
    ~RequestToken(void);

    void setScope(GoogleScope::ScopeType &_scope);
    void setScope(QList<GoogleScope::ScopeType> &_scope);
    void setScope(const QString &_scope);

    void clearScope(void);

    void setVersion(Version _version);

    void setPreferredMethod(HttpMethod _method);

    void setDisplayName(const QString &_name);

    QString getOAuthToken() const;
    QString getOAuthTokenSecret() const;

    void request(void)
    {
        QString tempScope;
        foreach(QString scope, mScope)
            tempScope.append(scope + " ");
        mGoogleParameters.insert("scope", tempScope.trimmed());
        mParameters.insert("oauth_timestamp", QByteArray::number(QDateTime::currentDateTime().toTime_t()));

        generateHeaderData();
        generateSignatureBaseString();
        generateSignature();


        mNetManager = new QNetworkAccessManager();

        if (mRequestMethod==GET)
            mRequestTokenUrl.addQueryItem("scope", mGoogleParameters["scope"]);

        mRequest.setUrl(mRequestTokenUrl);

        mHeaderData.append(",oauth_signature=\"" + mSignature + "\"");
        mHeaderData.append(",realm=\"\"");
        mHeaderData.prepend("OAuth ");

        mRequest.setRawHeader("Authorization", mHeaderData.toUtf8());

        if(mRequestMethod==GET)
        {
            mReply = mNetManager->get(mRequest);
        }
        else
        {
            mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            QByteArray postScope("scope=");
            postScope.append(mGoogleParameters["scope"]);

            mReply = mNetManager->post(mRequest, postScope);
        }

        connect(mReply, SIGNAL(readyRead()),
                this, SLOT(readyRead()));
        connect(mReply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(error(QNetworkReply::NetworkError)));
    }

signals:
    void tokenReceived(void);
    void requestError(ErrorCode errorCode);

public slots:
    void readyRead(void)
    {
        QString result(mReply->readAll());

        QStringList list_result = result.split("&");
        foreach(QString token, list_result)
        {
            QStringList split_token = token.split("=");
            mTokensReceived.insert(split_token[0], split_token[1]);
        }

        emit(tokenReceived());
    }

    void error(QNetworkReply::NetworkError error)
    {
        qDebug() << "Error\t" << error;
    }


private:
    void generateHeaderData(void);
    void generateSignatureBaseString(void);
    void generateSignature(void);


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

    QNetworkReply *mReply;
    QNetworkAccessManager *mNetManager;
    QNetworkRequest mRequest;
};

}
}

#endif // REQUESTTOKEN_H
