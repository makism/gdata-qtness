#ifndef AUTHORIZETOKEN_H
#define AUTHORIZETOKEN_H

#include <QObject>


namespace GDataQtness {
namespace GOAuth {

class AuthorizeToken : public QObject
{
    Q_OBJECT
public:
    explicit AuthorizeToken(QObject *parent = 0);
    ~AuthorizeToken();

signals:

public slots:

};

}
}

#endif // AUTHORIZETOKEN_H
