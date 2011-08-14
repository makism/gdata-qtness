#ifndef AUTHORIZETOKEN_H
#define AUTHORIZETOKEN_H

#include <QObject>
#include <QMap>

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

    void setToken(const QString &_token);
    void setDomain(const QString &_domain);
    void setCountryCode(const QString &_countryCode);
    void forceMobileVersion(bool _mobile);

signals:

public slots:

private:
    QMap<QString, QString> mGoogleParameters;
};

}
}

#endif // AUTHORIZETOKEN_H
