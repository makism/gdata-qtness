#include "authorizetoken.h"

namespace GDataQtness {

GOAuth::AuthorizeToken::AuthorizeToken(QObject *parent) :
    QObject(parent)
{
    mGoogleParameters.insert("hd", "default");
    mGoogleParameters.insert("hl", "en");
}

GOAuth::AuthorizeToken::~AuthorizeToken()
{

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
}

}
