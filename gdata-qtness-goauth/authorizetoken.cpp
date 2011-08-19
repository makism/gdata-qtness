#include "authorizetoken.h"

namespace GDataQtness {

GOAuth::AuthorizeToken::AuthorizeToken(QObject *parent) :
    QObject(parent),
    mAuthorizeTokenUrl("https://www.google.com/accounts/OAuthAuthorizeToken")
{
    mGoogleParameters.insert("hd", "default");
    mGoogleParameters.insert("hl", "en");
}

GOAuth::AuthorizeToken::~AuthorizeToken()
{
//    delete mNetReply;
//    delete mNetManager;

//    mNetReply = 0;
//    mNetManager = 0;
}

void GOAuth::AuthorizeToken::setDomain(const QString &_domain)
{
    mGoogleParameters.insert("hd", _domain);
}

void GDataQtness::GOAuth::AuthorizeToken::setCountryCode(const QString &_countryCode)
{
    mGoogleParameters.insert("hl", _countryCode);
}

void GOAuth::AuthorizeToken::forceMobileVersion(bool _mobile)
{
    if (_mobile)
        mGoogleParameters.insert("btml", "mobile");
    else
        mGoogleParameters.remove("btml");
}

void GOAuth::AuthorizeToken::setToken(const QString &_token)
{
    mGoogleParameters.insert("oauth_token", _token);

    request();
}

void GOAuth::AuthorizeToken::request()
{
    QMapIterator<QString, QString> i(mGoogleParameters);
    while (i.hasNext()) {
        i.next();
        mAuthorizeTokenUrl.addQueryItem(i.key(), i.value());
    }

    emit userAuthorizationNeeded(mAuthorizeTokenUrl.toString());

//    mNetManager = new QNetworkAccessManager();

//    mRequest.setUrl(mAuthorizeTokenUrl);
//    mNetReply = mNetManager->get(mRequest);

//    connect(mNetReply, SIGNAL(readyRead()),
//            this, SLOT(readReady()));
}


void GOAuth::AuthorizeToken::readReady()
{
//    QString result(mNetReply->readAll());
//    emit(authorizePageReceived(result));
}

}
