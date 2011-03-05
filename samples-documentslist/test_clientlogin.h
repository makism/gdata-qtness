#ifndef TEST_CLIENTLOGIN_H
#define TEST_CLIENTLOGIN_H

#include <QObject>

#include "clientlogin.h"
#include "documentslist.h"


class Test_ClientLogin: public QObject
{
    Q_OBJECT

public:
    Test_ClientLogin(QObject *parent =0);
	~Test_ClientLogin(void);

private slots:
    void authSuccess(void);
    void authError(QString strError);
	
private:
    ClientLogin *cl;
    DocumentsList dl;

};

#endif
