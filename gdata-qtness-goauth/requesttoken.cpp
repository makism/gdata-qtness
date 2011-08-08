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
    mReply->deleteLater();
    mNetManager->deleteLater();

    mReply = 0;
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

void GOAuth::RequestToken::generateSignature(void)
{
    QByteArray key(mHashKey.toUtf8());
    QCA::MessageAuthenticationCode hmac("hmac(sha1)", QCA::SymmetricKey(key));
    QCA::SecureArray array(mSignatureBaseString);
    hmac.update(array);
    QCA::SecureArray resultArray = hmac.final();
    QByteArray digest = resultArray.toByteArray().toBase64();

    mSignature = digest.toPercentEncoding();
}

void GOAuth::RequestToken::generateSignatureBaseString(void)
{
    mSignatureBaseString.append(mRequestMethodStr);
    mSignatureBaseString.append("&");
    mSignatureBaseString.append(mRequestTokenUrl.toString().toUtf8().toPercentEncoding());
    mSignatureBaseString.append("&");
    mSignatureBaseString.append(mNormalizedHeader.toUtf8().toPercentEncoding());
}

void GOAuth::RequestToken::generateHeaderData(void)
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

QString GDataQtness::GOAuth::RequestToken::getOAuthToken() const
{
}

QString GDataQtness::GOAuth::RequestToken::getOAuthTokenSecret() const
{
}

}
