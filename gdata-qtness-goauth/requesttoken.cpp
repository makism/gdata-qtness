#include "requesttoken.h"

namespace GDataQtness {

GOAuth::RequestToken::RequestToken(QObject *parent)
    : QObject(parent),
      mHashKey("anonymous&"),
      mRequestTokenUrl("https://www.google.com/accounts/OAuthGetRequestToken")
{
    QCA::init();
    QCA::InitializationVector iv(16);

    setPreferredMethod(GOAuth::GET);
    setVersion(GOAuth::VERSION_1_0);

    mParameters.insert("oauth_callback", "oob");
    mParameters.insert("oauth_signature_method", "HMAC-SHA1");
    mParameters.insert("oauth_consumer_key", "anonymous");
    mParameters.insert("oauth_nonce", iv.toByteArray().toHex());
}

GOAuth::RequestToken::~RequestToken()
{
    delete mNetReply;
    delete mNetManager;

    mNetReply = 0;
    mNetManager = 0;
}

void GOAuth::RequestToken::setScope(GoogleScope::ScopeType &_scope)
{
    setScope(_scope);
}

void GOAuth::RequestToken::setScope(QList<GoogleScope::ScopeType> &_scope)
{
    foreach(GoogleScope::ScopeType sc, _scope)
        setScope(sc);
}

void GOAuth::RequestToken::setScope(const QString &_scope)
{
    if(mScope.contains(_scope)==false)
        mScope.append(_scope);
}

void GOAuth::RequestToken::clearScope()
{
    mScope.clear();
}

void GOAuth::RequestToken::setDisplayName(const QString &_name)
{
    mGoogleParameters.insert("xoauth_displayname", _name);
}

void GOAuth::RequestToken::setVersion(GOAuth::Version _version)
{
    switch(_version) {
    case VERSION_2_0:
        mOAuthVersion = VERSION_2_0;
        mOAuthVersionStr = "2.0";
        break;
    case VERSION_1_0:
    default:
        mOAuthVersion = VERSION_1_0;
        mOAuthVersionStr = "1.0";
        break;
    }

    mParameters.insert("oauth_version", mOAuthVersionStr);
}

void GOAuth::RequestToken::setPreferredMethod(GOAuth::HttpMethod _method)
{
    switch(_method) {
    case POST:
        mRequestMethod = POST;
        mRequestMethodStr = "POST";
        break;
    case GET:
    default:
        mRequestMethod = GET;
        mRequestMethodStr = "GET";
        break;
    }
}

void GOAuth::RequestToken::request()
{
    //    if (mScope.size()==0)
    //        emit(requestError(MissingScope));

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
        mNetReply = mNetManager->get(mRequest);
    }
    else
    {
        mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        QByteArray postScope("scope=");
        postScope.append(mGoogleParameters["scope"]);

        mNetReply = mNetManager->post(mRequest, postScope);
    }


    connect(mNetReply, SIGNAL(readyRead()),
            this, SLOT(readReady()));
    connect(mNetReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(readError(QNetworkReply::NetworkError)));
}

void GOAuth::RequestToken::generateSignature()
{
    QByteArray key(mHashKey.toUtf8());
    QCA::MessageAuthenticationCode hmac("hmac(sha1)", QCA::SymmetricKey(key));
    QCA::SecureArray array(mSignatureBaseString);
    hmac.update(array);
    QCA::SecureArray resultArray = hmac.final();
    QByteArray digest = resultArray.toByteArray().toBase64();

    mSignature = digest.toPercentEncoding();
}

void GOAuth::RequestToken::generateSignatureBaseString()
{
    mSignatureBaseString.append(mRequestMethodStr).append("&");
    mSignatureBaseString.append(mRequestTokenUrl.toString().toUtf8().toPercentEncoding()).append("&");
    mSignatureBaseString.append(mNormalizedHeader.toUtf8().toPercentEncoding());
}

void GOAuth::RequestToken::generateHeaderData()
{
    QMap<QString, QString>::const_iterator i = mParameters.constBegin();
    while (i != mParameters.constEnd()) {
        mHeaderData.append(i.key() + "=\"" + i.value() + "\"");

        if (i + 1 != mParameters.constEnd())
            mHeaderData.append(",");

        ++i;
    }

    mNormalizedHeader = mHeaderData;
    mNormalizedHeader.replace("\"", "");
    mNormalizedHeader.replace(",", "&");

    QString normalizedScope(mGoogleParameters["scope"]);
    mNormalizedHeader.append("&scope=" + normalizedScope.toUtf8().toPercentEncoding());
}

void GOAuth::RequestToken::readReady()
{
    QString result(mNetReply->readAll());
    int statusCode = mNetReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode==200) {
        QStringList list_result = result.split("&");
        foreach(QString token, list_result)
        {
            QStringList split_token = token.split("=");
            QString value(QByteArray::fromPercentEncoding(split_token[1].toUtf8()));

            mTokensReceived.insert(split_token[0], value);
        }

        if (mTokensReceived["oauth_callback_confirmed"]=="true")
            emit(tokenReceived(getOAuthToken()));

    } else {
        emit(requestError(BadRequest));
    }
}

void GOAuth::RequestToken::readError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
}

QString GOAuth::RequestToken::getOAuthToken() const
{
    return mTokensReceived["oauth_token"];
}

QString GOAuth::RequestToken::getOAuthTokenSecret() const
{
    return mTokensReceived["oauth_token_secret"];
}


void GOAuth::RequestToken::setCallback(const QString &_callback)
{
    mParameters.insert("oauth_callback", _callback);
}

}
